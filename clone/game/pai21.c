// pai21.c 21����
// make by è��è(Catyboy)

#include <ansi.h>
#define MAX_PAI  52

inherit ITEM;

int has_start;
mapping player;			// ���ID
mapping player_data;

// ����
int game_start;			// 1���Ƿ�ʼ?
string who_play;		// ���ڳ��Ƶ���

// ������
int remain;				// ��ʣ��������
mixed pai_on_desk;		// ����ʹ�õ���		
mapping player_hand;	// ������ϵ���

// ������
mapping counter = ([]);

string *suit_str = ({  WHT"����"NOR , HIB"÷��"NOR ,HIR"����"NOR , HBWHT BLK"����"NOR});
string *suit_char = ({ "D","C","H","S"});
string *rank_str = ({ "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" });

int pai_number(int pai);
int pai_color(int pai);
object get_player(string id);
int is_playing(object ob);
int sizeof_pai(mixed* p);
void restore_player_data();
int pick_out();
int pick_in(string to, int card);
string id_to_pai(int id);
int do_pass(string arg);
int do_nextone(string arg);
string view_pai(string which);
void finish_21();
int auto_order();

void msg(object me,object who,string msg)
{
	if(me)
		message_vision(msg,me,who);
	else
		tell_room(environment(this_object()),msg,0);
}

int c21(mixed* inv)
{
	int i,j,sum,temp;

	sum = 0;
	temp = 0;
	for(i=0;i<inv[0];i++)
	{
		j = pai_number(inv[i+1]);
		if(j == 14)
		{
			temp ++;
			j = 11;
		}
		else
			j = (j>10?10:j);
		sum+=j;
	}
			
	for(;sum>21&&temp>0;temp--)
		sum -= 10;

	return sum;
}

void reset_pai()
{
	// �����ƣ��ƺУ���ҵ���)
	int i;
	string* key;
	
	for(i=0;i<MAX_PAI;i++)
		pai_on_desk[i]=i;
	remain=MAX_PAI;

	key = keys(player);
	for(i=0;i<sizeof(key);i++)
		player_hand[key[i]]=allocate(MAX_PAI);

	who_play = 0;
}

int reset_all()
{
	// ����������Ϸ
	int i;

	has_start = 0;
	if(sizeof(player)!=0)
		msg(this_player(),0,"$N���������ˡ�\n");
	
	player = ([]);
	player_hand = ([]);

	pai_on_desk = allocate(MAX_PAI);
	reset_pai();
	counter = ([]);

	return 1;
}

void create()
{
	set_name("21������", ({"card desk","pai","pai21"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ�����ӣ��������һЩ�ƣ�ʹ�÷�����ʹ��(helppai)���\n");
		set("unit", "��");
		set("value", 1);
	}
	player = ([]);
	reset_all();
}

void init()
{
	// ����
	add_action("do_help", "helppai");

	// ����ָ��
    add_action("do_reset", "reset");		// ����������Ϸ
	add_action("do_restart", "restart");	// ������Ϸ
	add_action("do_join", "join");			// �����ƾ�
	add_action("do_start", "start");		// ��ʼ��Ϸ
	
	add_action("do_xipai", "xipai");		// ϴ��
	add_action("do_view", "view");			// ����
		
	add_action("do_nextone", "next");		// �ߴ���һ��
	add_action("do_pass", "pass");			// ��Ҫ��
	
	// ��չָ��
	add_action("do_chupai", "play");		// ��
	add_action("do_daopai", "daopai");		// ����

	// ������
	add_action("do_showc", "showc");		// ��ʾ������
}

int do_reset(string arg)
{
	if(arg == "counter")
	{
		if(!is_playing(this_player()))
			return notify_fail("�㶼�����ư���\n");

		msg(this_player(),0,"$N��λ�������ˡ�\n");
		counter = ([]);
		return 1;
	}
	if(!this_object()->id(arg))
		return 0;
		
	return reset_all();
}

int do_restart(string arg)
{
	int i;
	string* key;

	if(!is_playing(this_player()))
		return notify_fail("�㶼���棬��ʼʲô����\n");

	if(!has_start)
		return notify_fail("��Ϸ��û�п�ʼ��\n");

	if(sizeof(player)!=0)
		msg(this_player(),0,"$N��ʼ�µ�һ���ƾ��ˡ�\n\n");

	reset_pai();
	restore_player_data();
	msg(0,0,"�ڿ�ʼ��Ϸ֮ǰ(play)�����λϴ��(xipai)��\n");
	return 1;
}

int do_join(string arg)
{
	object me;

	me = this_player();
	if(has_start)
		return notify_fail("�ƾ��Ѿ���ʼ�����ܼ����ˡ�\n");
	if(is_playing(me))
		return notify_fail("���Ѿ��μ��ˡ�\n");
	
	// add player
	player[me->query("id")]="yes";
	player_hand[me->query("id")]=allocate(MAX_PAI);
	msg(me,0,"$N�����ƾ��ˡ�\n");
	return 1;
}

int do_start(string arg)
{
	if(!is_playing(this_player()))
		return notify_fail("�㶼���棬��ʼʲô����\n");
	
	if(has_start)
		return notify_fail("�ƾ��Ѿ���ʼ�ˡ�\n");

	has_start = 1;
	msg(this_player(),0,"$N��ʼ���ƾ֡�\n\n");
	auto_order();
	msg(0,0,"�ڿ�ʼ��Ϸ֮ǰ(play)�����λϴ��(xipai)��\n");
	return 1;
}

int do_xipai(string arg)
{
	int i,sum,rand,which,temp;
	mixed* pai;

	if(!is_playing(this_player()))
		return notify_fail("�㶼���棬ϴʲô�ư���\n");
	
	pai = pai_on_desk;
	sum = remain;
	rand = sum;
	
	for(i=0;i<sum;i++)
	{
		which = random(rand);
		temp = pai[rand-1];
		pai[rand-1] = pai[which];
		pai[which] = temp;
		rand --;
	}
	msg(this_player(),0,"$Nϴ��ϴ������ơ�\n");
	return 1;
}

int do_chupai(string arg)
{
	int i,sum,j,done,temp,id;
	mixed* inv;
	string cmd;
	object ob;
		
	if(!is_playing(this_player()))
		return notify_fail("�㶼���氡��\n");

	if(who_play==0)
		who_play = this_player()->query("id");

	if(who_play!=this_player()->query("id"))
		return notify_fail("��û���ֵ����㰡��\n");

	done = 0;
		
	if((id = pick_out())==-1)
		return 0;

	if(!pick_in(this_player()->query("id"),id))
		return 0;

	msg(this_player(),0,"$N����һ��"+id_to_pai(id)+"��\n");

	done = 1;

	// check is over 21,if over pass
	inv = player_hand[this_player()->query("id")];
	sum = c21(inv);
			
	msg(this_player(),0,"$N������"HIY+sum+"��"NOR"�ˡ�\n");
	if(sum>21)
	{
		do_pass(HIR"���ˣ�����"NOR"\n");
		return 1;
	}
	
	ob = get_player(player[who_play]);
	if(ob)
	{
		who_play = player[who_play];
		do_nextone("");
	}
	return 1;
}

int do_view(string arg)
{
	mixed* pai;
	string hand_name;

	if(arg==""||arg==0)
		arg = this_player()->query("id");
	else
		hand_name = arg;
	
	pai = player_hand[arg];
	if(pai==0)
		return notify_fail("�ƾ�û�������ҡ�\n");
	
	if(hand_name)
		write(hand_name+"��");
	write(view_pai(arg)+"\n");
	return 1;
}

string extra_long()
{
	object me,who;
	string r,key;
	mixed *idx;
	int i;

	me = this_player();
	idx = keys(player);
	
	r = sprintf("�ƺ�������%d����\n",remain);
	
	if(sizeof(player)>0)
	{
		r+="******************************************\n";
		for(i=0;i<sizeof(idx);i++)
		{
			key = idx[i];
			who = get_player(key);
			if(who)
				r = r + key + "��"+view_pai(key)+"\n";
		}
		r = r + "******************************************\n";
	}
	return r;
}

int pick_out()
{
	int s,id;
		
	if(remain>0)
	{
		remain--;
		s = remain;
		id = pai_on_desk[s];
		pai_on_desk[s]=-1;
		return id;
	}
	else
	{
		msg(0,0,"û������");
		return -1;
	}
}

int pick_in(string to, int card)
{
	int s;
	mixed* pai;
		
	pai = player_hand[to];
	s = pai[0];
	s++;
	pai[s]=card;
	pai[0]++;
	return 1;
}

object get_player(string id)
{
	if(stringp(player[id]))
		return find_player(id);
	return 0;
}

int is_playing(object ob)
{
	int i;
	string id;
	id = ob->query("id");
	if(stringp(player[id]))
		return 1;
	return 0;
}

int sizeof_pai(mixed* p)
{	
	return p==0?0:p[0];
}

string view_pai(string which)
{
	mixed* pai;
	int show_all,i,j;
	string s,p;

	pai = player_hand[which];

	if(pai==0)
		return 0;
 
	if(sizeof_pai(pai)==0)
		return "û����";

	s = "";
	for(i=0;i<pai[0];i++)
	{
		p = id_to_pai(pai[i+1]);
		s+= p +" ";
	}
	return sprintf("%s��%d��",s,c21(pai));
}

int do_nextone(string arg)
{
	object ob;
	string id;

	if(!is_playing(this_player()))
		return notify_fail("�㶼�����ư���\n");

	if(who_play==0)
		return notify_fail("������˭���ư���\n");

	id = who_play;
	ob = get_player(id);
	
	if(ob==0)
		return msg(0,0,"�����ȱ���ˣ������¿�ʼ��Ϸ(reset pai)��\n");

	if(this_player()->query("id")!=id)
		msg(this_player(),ob,"$N��$n˵���������ˡ�\n");
	else
		msg(this_player(),0,"���Լ�˵������������\n");
	return 1;
}

int do_pass(string arg)
{
	string old,str;
	string* key;
	mixed* inv;
	int i,temp;

	if(!is_playing(this_player()))
		return notify_fail("�㶼�����ư���\n");

	if(who_play!=this_player()->query("id"))
		return notify_fail("��û�е��㰡��\n");

	if(!arg)
		arg = "�У��ӣӣ���";
	msg(this_player(),0,"$N˵����"+arg+"\n");
	old = who_play;
	who_play = player[who_play];

	key = keys(player);

	for(i=0;i<sizeof(key);i++)
		if(player[key[i]]==old)
			player[key[i]] = player[old];
	player[old] = "";
				
	if(player[who_play] == "")
	{
		msg(0,0,"��Ҷ���Ҫ�ˡ�\n");
		finish_21();
		return 1;
	}
	do_nextone("");
	return 1;
}

string id_to_pai(int id)
{
	int i,j;
	if(id <0)
		return HIR"???"NOR;
	if(id == 52)
		return HIY"С��"NOR + "JS";
	if(id>=53)
		return HIY"���"NOR + "JB";
	i = id/13;
	j = id-i*13;
	return suit_str[i] + suit_char[i] + rank_str[j];
}

int pai_to_id(string id)
{
	int ic1=-1,ic2=-1;
	string c1,c2;
	c1 = id[0..0];
	c2 = id[1..sizeof(id)-1];

	if(c1=="J")return c2=="S"?52:53;
	if(c1==suit_char[0]) ic1=0;
	if(c1==suit_char[1]) ic1=1;
	if(c1==suit_char[2]) ic1=2;
	if(c1==suit_char[3]) ic1=3;
	if(ic1==-1)return -1;

	if(sscanf(c2,"%d",ic2)!=1)
	{
		if(c2 == "J") ic2 = 11;
		if(c2 == "Q") ic2 = 12;
		if(c2 == "K") ic2 = 13;
		if(c2 == "A") ic2 = 14;
		if(ic2==-1) return -2;
	}
	ic2 -=2;
	return ic1*13+ic2;
}

int auto_order()
{
	int i;
	string* key;
	string who,start_one;

	key = keys(player);

	start_one = key[0];
	who = "";
	for(i=0;i<sizeof(key);i++)
	{
		if(get_player(key[i]))
		{
			if(who =="")
				who = key[i];
			else
			{
				player[who] = key[i];
				who = key[i];
			}
		}
	}
	player[who] = start_one;
	return 1;
}

int do_showc(string arg)
{
	string r;
	mixed *idx;
	int i;

	idx = keys(counter);
	
	r = "������(Scoreboard)\n����������������������������������\nID��������������������\n����������������������������������\n";
	for(i=0;i<sizeof(idx);i++)
		r = sprintf("%s%-14s%10d\n", r,idx[i],counter[idx[i]]);
	r += "����������������������������������\n";

	msg(0,0,r);
	return 1;
}

void press_counter(string id,int num)
{
	counter[id]=counter[id]+num;
}

int do_daopai(string arg)
{
	int i,id;
	
	if(!is_playing(this_player()))
		return notify_fail("�㶼���棬��ʲô����\n");

	if(!has_start)
		return notify_fail("��Ϸ��û�п�ʼ��\n");

	if(remain>0)
	{
		id = pai_on_desk[0];
		for(i=1;i<remain;i++)
			pai_on_desk[i-1] = pai_on_desk[i];
		pai_on_desk[remain-1] = id;
		msg(this_player(),0,"$N����һ���ơ�\n");
		return 1;
	}
	else
		return notify_fail("û�����ˡ�\n");
}

int pai_number(int pai)
{
	if(pai==52)
		return 15;
	if(pai==53)
		return 16;
	return pai-pai/13*13+2;
}

int pai_color(int pai)
{
	if(pai>=52)
		return 5;
	return pai/13+1;
}

void save_player_data()
{
	string* inv;
	int i;
	inv = keys(player);
	player_data = ([]);
	for(i=0;i<sizeof(inv);i++)
		player_data[inv[i]] = player[inv[i]];
}

void restore_player_data()
{
	int i;
	string* key;

	if(!player_data)
		return;

	key = keys(player_data);
	for(i=0;i<sizeof(key);i++)
		player[key[i]] = player_data[key[i]];
}

int sort_21(string str1, string str2)
{
	int c1,c2;
	string temp;

	sscanf(str1,"%s:%d",temp,c1);
	sscanf(str2,"%s:%d",temp,c2);
	
	if(c1==c2)
		return 0;

	if(c1>21&&c2>21)
		return (c1<c2)?-1:1;

	if(c1>21)
		c1 = -1;
	if(c2>21)
		c2 = -1;
	return (c1>c2)?-1:1;
}

void finish_21()
{
	string* key;
	mixed* inv2;
	mixed* inv;
	string str,r,id;
	int i,maxn,fen,k,lpoint;

	key = keys(player);
	inv2 = allocate(sizeof(player));
	for(i=0;i<sizeof(key);i++)
	{
		str = key[i];
		inv2[i] = str + ":" + c21(player_hand[str]);
	}
		
	inv = sort_array(inv2,"sort_21",this_object());
	
	lpoint = -1;
	r = "���\n����������������������������������\nID��������������������       �÷�\n����������������������������������\n";
	for(i=0;i<sizeof(inv);i++)
	{
		sscanf(inv[i],"%s:%d",id,k);
		if(k != lpoint)
		{
			fen = sizeof(inv) - i - 1;
			lpoint = k;
		}
		if(i==0)maxn=k;
		if(k==maxn)r+=HIY;
		if(k>21)
		{
			r+=HIR;
			fen = 0;
		}
		r = sprintf("%s%-14s%5d%12d\n", r,id,k,fen);
		r+=NOR;

		press_counter(id,fen);
	}
	r += "����������������������������������\n\n";
	msg(0,0,r);
	
	reset_pai();
	restore_player_data();
	msg(0,0,"���λ����ϴ��(xipai)��ʼ�µ�һ�֡�\n");
}

int do_help(string arg)
{
	this_player()->start_more( @HELP
��21������ʹ�÷���:
����[��ʼ��Ϸ]������������������������������
�������helppai
�������join����������������Ϸ
��ʼ���start ����������ʼ�Ժ����ټ���
�������reset pai ����������Ϸ

����[��Ϸ����]������������������������������
������Ϸ��restart
�������ƣ�play����������������Ϸ
����Ҫ��: pass

����[��������]������������������������������
ϴ�����xipai
�������view [���ID] �۲�������ϵ���
�ߴ����next�����������ߴ����ڳ��Ƶ���

����[������ʹ��]����������������������������
��ʾ: showc
����: reset counter




����[��Ϸ����]������������������������������
��Ϸ��ʼ�Ժ�ÿ����������ֱ������Ϊֹ��
������ÿ�����ϵĵ�������ʤ����
���� > 21 Ϊ�䣬����<21��ʱ���������ʤ��
J��Q��kΪ10�㣬A����Ϊ1�����Ϊ11�㡣

��������������������������������������������
			make by è��è(Catyboy) v1.0
HELP
	);
	return 1;
}

mixed t()
{
	return pai_on_desk;
}
