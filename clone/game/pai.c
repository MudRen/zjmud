// pai.c ��
// make by è��è(Catyboy)

#include <ansi.h>
#define DESK  "desk"
#define DESK2 "desk2"
#define PAIS  55

inherit ITEM;

int has_start;
mapping player;			// ���ID
mapping player_data;	// ������� 21��

// ģʽ
string mode;			// 8,21,D2
string mode2;			// auto,man
int game_start;			// 1���Ƿ�ʼ?
int player_counter;		// ������ 8
string who_play;		// ���ڳ��Ƶ��� 21
string last_play;		// ���һ�����Ƶ���
mixed last_pai;			// ��������


// ������
mixed expai;				// ��ʹ�õĵ��� id = desk
mixed allpai;				// ʹ�õ���		id = desk2
mapping pai_hand;			// ������ϵ���	id = playerid+" hand"
mapping pai_out;			// ��ҳ�����	id = playerid+" out"
mapping pai_save;			// ��ұ������ id = playerid+" save"
mapping pai_hide;			// ������ص��� id = playerid+" hide"

// ������
mapping counter = ([]);

string *suit_str = ({  WHT"����"NOR , HIB"÷��"NOR ,HIR"����"NOR , HBWHT BLK"����"NOR});
string *suit_char = ({ "D","C","H","S"});
string *rank_str = ({ "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" });

void save_player_data();
void restore_player_data();
void finish_21();
int pai_number(int pai);
int pai_color(int pai);
int do_reset(string arg);
int do_shunxu(string arg);
int do_nextone(string arg);
int do_xipai(string arg);
int do_paipai(string arg);
int do_pass(string arg);
int pick_out(string from, int id);
int pick_out2(string from, int id);
int pick_in(string to,int card);
string id_to_name(string id);
mixed* get_pais(string id);
object get_player(string id);
int is_playing(object ob);
int move_pai(string pid,string from,string to);
int sizeof_pai(mixed* p);
string view_pai(object who,string which);
int do_movepai(string arg);
string id_to_pai(int id);
int pai_to_id(string id);
void msg(string msg);

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

string mode_name()
{
	if(mode=="8")
		return "8��";
	if(mode=="21")
		return "21��";
	return "����ģʽ";
}

void reset_pai()
{
	int i;
	string* key;
	
	for(i=0;i<54;i++)
		allpai[i+1]=i;
	allpai[0]=54;

	for(i=0;i<expai[0];i++)
		pick_out("desk",expai[i+1]);

	key = keys(player);
	for(i=0;i<sizeof(key);i++)
	{
		pai_hand[key[i]]=allocate(PAIS);
		pai_out[key[i]]=allocate(PAIS);
		pai_save[key[i]]=allocate(PAIS);
		pai_hide[key[i]]=allocate(PAIS);
	}

	who_play = 0;
	last_play = 0;
	last_pai = ( {-1,-1,-1,-1,-1} );
}

int reset_all()
{
	int i;

	has_start = 0;
	if(sizeof(player)!=0)
		msg(this_player()->name()+"���������ˡ�\n");
	
	player = ([]);
	player_data = ([]);
	pai_hand = ([]);
	pai_out = ([]);
	pai_save = ([]);
	pai_hide = ([]);

	allpai = allocate(PAIS);
	expai = allocate(PAIS);
	expai[0]=0;

	reset_pai();

	// reset mode
	mode = 0;
	mode2 = 0;

	return 1;	
}

void create()
{
	set_name("����", ({"card desk","pai"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ�����ӣ��������һЩ�ƣ�ʹ�÷�����ʹ��(helppai)���\n");
		set("unit", "��");
		set("value", 1);
		set("no_get", 1);
	}
	player = ([]);
	
	reset_all();
}

void init()
{
	// ����
	add_action("do_help", "helppai");
	add_action("do_help2", "helppai2");

	// ����ָ��
    add_action("do_reset", "reset");
	add_action("do_restart", "restart");
	add_action("do_join", "join");
	add_action("do_start", "start");
	add_action("do_xipai", "xipai");
	add_action("do_view", "view");
	add_action("do_sortpai", "sort");
	add_action("do_movepai", "move");
	add_action("do_shunxu", "order");
	add_action("do_now", "now");
	add_action("do_nextone", "next");
	add_action("do_pass", "pass");
	add_action("do_end", "finish");
	add_action("do_setmode", "setmode");

	// ��չָ��
	add_action("do_paipai", "pai");
	add_action("do_paipai2", "paipai");
	add_action("do_mopai", "mopai");
	add_action("do_chupai", "play");
	add_action("do_showpai", "show");
	add_action("do_hidepai", "hide");
	add_action("do_takebackpai", "takeback");
	add_action("do_removej", "removej");
	add_action("do_daopai", "daopai");

	// ������
	add_action("do_press", "press");
	add_action("do_showc", "showc");
	add_action("do_removec", "removec");
}

int do_help(string arg)
{
	this_player()->start_more( read_file(__DIR__ "helppai"));
	write("\n");
	return 1;
}

int do_help2(string arg)
{
	if(!arg)return 0;
	if(file_size(__DIR__ ""+arg+"_hlp")<0)return 0;
	this_player()->start_more( read_file(__DIR__ ""+arg+"_hlp"));
	write("\n");
	return 1;
}

int do_reset(string arg)
{
	if(arg == "counter")
	{
		if(!is_playing(this_player()))
			return notify_fail("�㶼�����ư���\n");

		write("��������λ�ˡ�\n");
		counter = ([]);
		return 1;
	}
	if(!this_object()->id(arg))return 0;
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
		msg("���¿�ʼ�ˡ�\n");
	
	reset_pai();

	if(mode == "8")
	{
		player_counter = 0;
		restore_player_data();
	}

	if(mode == "21")
		restore_player_data();
	
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
	pai_hand[me->query("id")]=allocate(PAIS);
	pai_out[me->query("id")]=allocate(PAIS);
	pai_save[me->query("id")]=allocate(PAIS);
	pai_hide[me->query("id")]=allocate(PAIS);
	msg(me->name()+"�����ƾ��ˡ�\n");
	return 1;
}

int do_start(string arg)
{
	if(!is_playing(this_player()))
		return notify_fail("�㶼���棬��ʼʲô����\n");
	has_start = 1;
	msg(this_player()->name()+"��ʼ���ƾ֡�\n");

	this_player()->start_more( read_file(__DIR__ "startpai"));
	write("\n");
	return 1;
}

int do_xipai(string arg)
{
	int i,sum,rand,which,temp;
	mixed* pai;

	if(!is_playing(this_player()))
		return notify_fail("�㶼���棬ϴʲô�ư���\n");

	if(arg==""||arg==0)
		arg = DESK;
	
	pai = get_pais(arg);
	if(pai==0)
		return notify_fail("û�������ƣ�����İ�����\n");
	
	sum = pai[0];
	rand = sum;
	
	for(i=0;i<sum;i++)
	{
		which = random(rand)+1;
		temp = pai[rand];
		pai[rand] = pai[which];
		pai[which] = temp;
		rand --;
	}
	msg(this_player()->name()+"ϴ��ϴ"+id_to_name(arg)+"���ơ�\n");
	return 1;
}

int do_sortpai(string arg)
{
	int i,sum,which,v=0,j,it;
	int c1,c2;
	string temp;
	mixed* pai;

	if(!is_playing(this_player()))
		return notify_fail("�㶼���棬����ʲô�ư���\n");

	if(arg==""||arg==0)
		arg = this_player()->query("id")+" hand";
	if(arg=="/c")
		arg = this_player()->query("id")+" hand /c";

	if(sscanf(arg,"%s /c",temp)==1)
	{
		v = 1;		// ��ɫ����
		arg = temp;
	}

	pai = get_pais(arg);
	if(pai==0)
		return notify_fail("û�������ƣ�����İ�����\n");
	
	sum = pai[0];
	
	for(i=0;i<sum;i++)
	{
		for(j=0;j<sum;j++)
		{
			if(i==j)continue;
			if(v)
			{
				c1=pai[i+1];
				c2=pai[j+1];
			}
			else
			{
				c1 = pai[i+1]>=52?pai[i+1]:(pai[i+1]-pai[i+1]/13*13)*4+pai[i+1]/13;
				c2 = pai[j+1]>=52?pai[j+1]:(pai[j+1]-pai[j+1]/13*13)*4+pai[j+1]/13;
			}
			
			if(c1<c2)
			{
				it=pai[i+1];
				pai[i+1]=pai[j+1];
				pai[j+1]=it;
			}
		}
	}

	msg(this_player()->name()+"������һ��"+id_to_name(arg)+"���ơ�\n");
	return 1;
}

int do_movepai(string arg)
{
	int i,wi,v = 1,op;
	string* whichs;
	string which,where1,where2,temp,pstr,err;

	if(!is_playing(this_player()))
		return notify_fail("�㶼���氡��\n");

	if(arg==""||arg==0)
		return notify_fail("��ʽ��move which[+which2...] from where1 to where2 [/h]\n");

	if(sscanf(arg,"%s from %s to %s",which,where1,where2)!=3)
		return notify_fail("��ʽ��move which from where1 to where2 [/h]\n");

	if(sscanf(where2,"%s /h",temp)==1)
	{
		where2 = temp;
		v = 0;
	}

	if(where1=="hand"||
		where1=="out"||
		where1=="save"||
		where1=="hide")
		where1 = this_player()->query("id")+" "+where1;
	if(where2=="hand"||
		where2=="out"||
		where2=="save"||
		where2=="hide")
		where2 = this_player()->query("id")+" "+where2;
	
	if(get_pais(where2)==0)
		return notify_fail("Ŀ�Ĵ�������İ�����\n");

	whichs = explode(which,"+");
	pstr = "";
	op = 0;
	err = "";
	for(i=0;i<sizeof(whichs);i++)
	{
		temp = whichs[i];
		if(sscanf(temp,"%d",wi)==1)
			wi = pick_out2(where1,wi);
		else
		{
			if(where1=="desk"&&has_start)
				return notify_fail("�Ѿ���ʼ�ˣ������ƶ�ָ�����ơ�\n");
			wi=pick_out(where1,pai_to_id(temp));
		}

		if(wi==-1)
		{
			err = "Դ�����ƺ�/��Ŵ�������İ�����\n";
			continue;
		}

		if(!pick_in(where2,wi))
		{
			err = "�ƶ��ƴ���\n";
			continue;
		}
		if(pstr!="")
			pstr += " ";
		pstr+= id_to_pai(wi);
		op ++;
		// if(i<5)
		//	last_pai[i]=wi;
	}
	
	if(!v)
		pstr =  chinese_number(op) +"����";
	
	if(op>0)
		msg(this_player()->name()+"��"+pstr+"��"+id_to_name(where1)+"�ŵ�"+id_to_name(where2)+"��\n");
	return err==""?1:notify_fail(err);
}

int do_paipai(string arg)
{
	int i,sum,j;
	string* key;
	string cmd;
	

	if(!is_playing(this_player()))
		return notify_fail("�㶼���氡��\n");

	if(!has_start)
		return notify_fail("��û�п�ʼ�����ƣ�\n");
	
	if(arg==0||sscanf(arg,"%d",sum)!=1)
		sum = 100;

	key = keys(player);
	for(i=0;i<sum;i++)
	{
		if(sizeof_pai(allpai)==0)
			return 1;
		for(j=0;j<sizeof(key);j++)
			do_movepai("1 from desk to "+key[j]+" hand /h");
	}
	return 1;
}

int do_mopai(string arg)
{
	int i,sum,j;
	string* key;
	string cmd;
	
	if(!is_playing(this_player()))
		return notify_fail("�㶼���氡��\n");

	return do_movepai("1 from desk to "+this_player()->query("id")+" hand /h");
}

int do_chupai(string arg)
{
	int i,sum,j,done,temp;
	mixed* inv;
	string cmd;
	object ob;
	
	if(!is_playing(this_player()))
		return notify_fail("�㶼���氡��\n");

	if(mode == "21")
	{

	}
	else
	{
		if(arg==0)
			return notify_fail("��ʽ��play which[+which2...]\n");
	}

	if(mode == "8")
		return notify_fail("ʹ��hide�������\n");

	if(who_play==0)
		who_play = this_player()->query("id");

	if(who_play!=this_player()->query("id"))
		return notify_fail("��û���ֵ����㰡��\n");

	done = 0;
		
	if(mode == "21")
		if(do_movepai("1 from desk to out"))
		{
			done = 1;
			// check is over 21,if  over pass
			inv = get_pais(this_player()->query("id")+" out");
			sum = c21(inv);
				
			msg(this_player()->name()+"������"HIY+sum+"��"NOR"�ˡ�\n");
			if(sum>21)
			{
				do_pass(HIR"���ˣ�����"NOR"\n");
				return 1;
			}
		}

	if(done==0)
		done = do_movepai(arg+" from hand to out");
		
	if(done)
	{
		ob = get_player(player[who_play]);
		if(ob)
		{
			who_play = player[who_play];
			do_nextone("");
			// tell_object(ob,"�������:\n"+view_pai(ob,who_play+" hand")+"\n");
		}
	}
	return 1;
}

int do_showpai(string arg)
{
	int i,sum,j;
	string* key;
	string cmd;
	object ob;
	
	if(!is_playing(this_player()))
		return notify_fail("�㶼���氡��\n");

	if(arg==0)
		return notify_fail("��ʽ��show which[+which2...]\n");

	if(who_play==0)
		who_play = this_player()->query("id");

	do_movepai(arg+" from hand to save");
	return 1;
}

int do_hidepai(string arg)
{
	int i,sum,j;
	string* key;
	string cmd;
	object ob;
	
	if(!is_playing(this_player()))
		return notify_fail("�㶼���氡��\n");

	if(arg==0)
		return notify_fail("��ʽ��hide which[+which2...]\n");

	if(who_play==0)
		who_play = this_player()->query("id");

	do_movepai(arg+" from hand to hide /h");
	return 1;
}

int do_takebackpai(string arg)
{
	int i,sum,j;
	string* key;
	string cmd,where;
	object ob;
	
	if(!is_playing(this_player()))
		return notify_fail("�㶼���氡��\n");

	if(arg==0)
		return notify_fail("��ʽ��takeback which[+which2...] [from where]\n");

	if(sscanf(arg,"%s from %s",cmd,where)!=2)
	{
		cmd = arg;
		where = "out";
	}

	do_movepai(cmd+" from "+where+" to hand"+(where=="hide"?" /h":""));
	return 1;
}

int do_view(string arg)
{
	mixed* pai;

	if(arg==""||arg==0)
		arg = this_player()->query("id")+" hand";

	if(arg=="hand"||
		arg=="out"||
		arg=="save"||
		arg=="hide")
		arg= this_player()->query("id")+" "+arg;
	
	pai = get_pais(arg);
	if(pai==0)
		return notify_fail("û�������ƣ�����İ�����\n");
	
	write(id_to_name(arg)+":"+view_pai(this_player(),arg)+"\n");
	return 1;
}

string extra_long()
{
	object me;
	string r,key;
	mixed *idx;
	int i;

	me = this_player();
	idx = keys(player);
	
	r = id_to_name(DESK) + ":" + view_pai(me,DESK)+"\n";
	r = r + id_to_name(DESK2) + ":" + view_pai(me,DESK2)+"\n";

	r+= "****";
	if(mode&&mode!="")
		r+= mode_name();
	r+="******************************************\n";
	for(i=0;i<sizeof(idx);i++)
	{
		key = idx[i];
		r = r + id_to_name(key+" hand") + ":"+view_pai(this_player(),key+" hand")+"\n";
		r = r + id_to_name(key+" out") + ":"+view_pai(this_player(),key+" out")+"\n";
		r = r + id_to_name(key+" save") + ":"+view_pai(this_player(),key+" save")+"\n";
		r = r + id_to_name(key+" hide") + ":"+view_pai(this_player(),key+" hide")+"\n";
		r = r + "**********************************************\n";
	}
	
	return r;
}

int pick_out(string from, int id)
{
	int i,j,s;
	string* p;
	mixed* pai;
		
	pai = get_pais(from);
	if(pai==0)
		return -1;
	
	s = pai[0];

	for(i=0;i<s;i++)
	{
		if(pai[i+1]==id)
		{
			// move all next
			for(j=i+1;j<s;j++)
				pai[j]=pai[j+1];
			pai[s]=-1;
			pai[0]--;
			return id;
		}
	}
	return -1;
}

int pick_out2(string from, int id)
{
	int i,j,s;
	string* p;
	mixed* pai;
		
	pai = get_pais(from);
	if(pai==0)
		return -1;
	
	s = pai[0];

	for(i=0;i<s;i++)
	{
		if(i+1==id)
		{
			id = pai[i+1];
			// move all next
			for(j=i+1;j<s;j++)
				pai[j]=pai[j+1];
			pai[s]=-1;
			pai[0]--;
			return id;
		}
	}
	return -1;
}

int pick_in(string to, int card)
{
	int s;
	mixed* pai;
		
	pai = get_pais(to);
	if(pai==0)
		return 0;
	s = pai[0];
	s++;
	if(s>54)
		return 0;
	pai[s]=card;
	pai[0]++;
	return 1;
}

mixed* get_pais(string id)		// ��ȡָ��ID����
{
	string str;

	if(id == DESK)
		return allpai;
	if(id == DESK2)
		return expai;

	if(sscanf(id,"%s hand",str)==1)
	{
		if(get_player(str))
			return pai_hand[str];
	}

	if(sscanf(id,"%s out",str)==1)
	{
		if(get_player(str))
			return pai_out[str];
	}

	if(sscanf(id,"%s save",str)==1)
	{
		if(get_player(str))
			return pai_save[str];
	}

	if(sscanf(id,"%s hide",str)==1)
	{
		if(get_player(str))
			return pai_hide[str];
	}
	return 0;
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

string id_to_name(string id)
{
	object ob;
	string str;

	if(id == DESK)
		return "�ƺ�";
	if(id == DESK2)
		return "���ƺ�";

	if(sscanf(id,"%s hand",str)==1)
	{
		ob = get_player(str);
		if(ob)
			return ob->name()+"����";
	}

	if(sscanf(id,"%s out",str)==1)
	{
		ob = get_player(str);
		if(ob)
			return ob->name()+"��ǰ";
	}

	if(sscanf(id,"%s save",str)==1)
	{
		ob = get_player(str);
		if(ob)
			return ob->name()+"���";
	}

	if(sscanf(id,"%s hide",str)==1)
	{
		ob = get_player(str);
		if(ob)
			return ob->name()+"����";
	}
	return "???";
}

int sizeof_pai(mixed* p)
{	
	return p==0?0:p[0];
}

int valid_show(object who,string which)
{
	// ���ùۿ�Ȩ�� 0 - hide 1 - show
	string id,temp;
	if(!has_start)
		return 1;

	if(sscanf(which,"%s %s",id,temp)==2)
	{
		if(who->query("id")==id)
			return 1;
		if(temp == "out")
			return 1;
		if(temp == "save")
			return 1;
	}
	return 0;
}

string view_pai(object who,string which)
{
	mixed* pai;
	int show_all,i,j;
	string s,p;

	pai = get_pais(which);

	if(pai==0)
		return 0;
 
	if(sizeof_pai(pai)==0)
		return "û���ơ�";

	if(valid_show(who,which))
	{
		s = "";
		for(i=0;i<pai[0];i++)
		{
			p = id_to_pai(pai[i+1]);
			s+= p +" ";
		}
		return s;
	}
	else
		return sizeof_pai(pai)+"����";
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
		return notify_fail("û�����ú�˳������İ�����\n");
	if(this_player()->query("id")!=id)
		msg(this_player()->name()+"��"+ob->name()+"˵���������ˡ�\n");
	else
		msg(this_player()->name()+"���Լ�˵������������\n");
	return 1;
}

int do_shunxu(string arg)
{
	int i;
	string* p;
	string who;

	if(arg==0)
		return notify_fail("û��ָ�����ˣ�\n");
	p = explode(arg,"->");

	who = "";
	for(i=0;i<sizeof(p);i++)
	{
		if(get_player(p[i]))
		{
			if(who =="")
				who = p[i];
			else
			{
				msg(who+"->"+p[i]+"\n");
				player[who]=p[i];
				who = p[i];
			}
		}
		else
			return notify_fail(p[i]+"û�м����ƾְ���\n");
	}
	return 1;
}

int do_removej(string arg)
{
	if(!is_playing(this_player()))
		return notify_fail("�㶼���氡��\n");

	do_movepai("JB from desk to desk2");
	do_movepai("JS from desk to desk2");
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
	msg(this_player()->name()+"˵����"+arg+"\n");
	old = who_play;
	who_play = player[who_play];

	if(mode == "21")
	{
		key = keys(player);

		for(i=0;i<sizeof(key);i++)
			if(player[key[i]]==old)
				player[key[i]] = player[old];
		player[old] = "";
				
		if(player[who_play] == "")
		{
			msg("��Ҷ���Ҫ�ˡ�\n");
			finish_21();
			return 1;
		}
	}
	
	do_nextone("");
	return 1;
}

int do_now(string arg)
{
	if(!is_playing(this_player()))
		return notify_fail("�㶼�����ư���\n");

	if(!arg)
		return notify_fail("��ʽ��now who\n");

	if(get_player(arg))
		who_play = arg;
	do_nextone("");
	return 1;
}

int do_end(string arg)
{
	mixed* pai;
	string* p;
	int i;
	object ob;

	if(!is_playing(this_player()))
		return notify_fail("�㶼�����ư���\n");

	if(!has_start)
		return notify_fail("��Ϸ��û�п�ʼ����\n");

	if(mode == "21")
		return 1;

	if(mode == "8")
	{
		pai = get_pais(this_player()->query("id")+" hand");

		if(!pai||sizeof_pai(pai)!=0)
			return notify_fail("��û�а��갡��\n");
		
		msg(this_player()->name()+"˵�����������ˣ���\n");
		if(player[this_player()->query("id")]!="F")
		{
			player[this_player()->query("id")]="F";
			player_counter ++;
		}

		if(player_counter==sizeof(player))
		{
			// show all
			p = keys(player);
			for(i=0;i<sizeof(p);i++)
				do_movepai("1+1+1+1+1+1+1+1 from "+p[i]+" hide to "+p[i]+" out");
		}
	}
	else
	{
		msg(this_player()->name()+"˵�����������ˣ���\n");
		who_play = "����";
	}
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

void msg(string msg)
{
	tell_room(environment(this_object()),msg,0);
}

void auto_order()
{
	int i;
	string* key;
	string order;

	key = keys(player);
	order = "";
	for(i=0;i<sizeof(key);i++)
		order+= key[i]+"->";	
	order+=key[0];
	do_shunxu(order);
	msg("���˳�򲻺�����ʹ��order�����������á�\n");
}

int do_setmode(string arg)
{
	int vmode = 0,i;
	mixed* inv;
	
	if(!arg)
		return notify_fail("setmode [ģʽ] ����հ�����\n");

	if(!is_playing(this_player()))
		return notify_fail("�㶼�����ư���\n");

	if(!has_start)
		return notify_fail("��Ϸ��û�п�ʼ����\n");

	if(mode)
	{
		if(mode=="21"&&arg=="auto")
		{
			mode2 = "auto";
			msg("�����Զ�ģʽ��\n");
			return 1;
		}

		if(arg=="man"&&mode=="21")
		{
			mode2 = 0;
			msg("�����ֶ�ģʽ��\n");
			return 1;
		}
		return notify_fail("�Ѿ�������ģʽ����ʹ��reset pai���á�\n");
	}

	mode = arg;
	if(mode=="8")
	{
		vmode = 1;
		msg(HIR"����8��ģʽ��"NOR"\n");
		has_start = 0;
		do_removej("");
		has_start = 1;
	}

	if(mode=="21")
	{
		vmode = 1;
		msg(HIR"����21��ģʽ��"NOR"\n");
		has_start = 0;
		do_removej("");
		has_start = 1;
		auto_order();
		save_player_data();
	}
	
	if(mode == "d2")
	{
		vmode = 1;
		msg(HIR"�������2ģʽ��"NOR"\n");
		has_start = 0;
		do_removej("");
		has_start = 1;
		auto_order();
	}

	if(!vmode)
	{
		mode = 0;
		return notify_fail("���ڲ�֧�ָ�ģʽ\n");
	}
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

	tell_room(environment(this_player()),r,0);
	return 1;
}

void press_counter(string id,int num)
{
	counter[id]=counter[id]+num;
}

int do_press(string arg)
{
	string id;
	int n;
	
	if(!is_playing(this_player()))
		return notify_fail("�㶼�����ư���\n");

	if(sscanf(arg,"%s %d",id,n)!=2)
		return notify_fail("��ʽ��press id number���磺press catyboy 10\n");
	
	press_counter(id,n);
	do_showc("");
	return 1;
}

int do_removec(string arg)
{
	string id;
	
	if(!is_playing(this_player()))
		return notify_fail("�㶼�����ư���\n");

	if(!arg||sscanf(arg,"%s",id)!=1)
		return notify_fail("��ʽ��removec id\n");

	map_delete(counter,id);
	do_showc("");
	return 1;
}

int do_paipai2(string arg)
{
	int i;
	
	if(!is_playing(this_player()))
		return notify_fail("�㶼���氡��\n");

	if(!has_start)
		return notify_fail("��Ϸ��û�п�ʼ��\n");

	if(mode == "8")
		do_paipai("8");
	return 1;
}

int do_daopai(string arg)
{
	int i;
	
	if(!is_playing(this_player()))
		return notify_fail("�㶼���棬��ʼʲô����\n");

	if(!has_start)
		return notify_fail("��Ϸ��û�п�ʼ��\n");

	do_movepai("1 from desk to desk /h");
	return 1;
}

mapping t()
{
	return player;
}

mapping t2()
{
	return player_data;
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
	for(i=0;i<sizeof(inv);i++)
		player_data[inv[i]] = player[inv[i]];
}

void restore_player_data()
{
	int i;
	string* key;
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
		inv2[i] = str + ":" + c21(get_pais(str+" out"));
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

		if(mode2 == "auto")
		{
			press_counter(id,fen);
		}
	}
	r += "����������������������������������\n";
	msg(r);
	who_play = 0;
}

