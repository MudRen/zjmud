//Room: duchang.c

#include <ansi.h>

inherit ROOM;

int room_status = 0;
int *big = allocate(2);
int *res = allocate(2);

int random2 (int i)
{
	return (random(i)+uptime()) % i;
}

mapping gutous = ([ 
	"tc" : "ͷ��",
	"sd" : "˫��",
	"qx" : "����",
	"sx" : "ɢ��",
 ]); 

void create()
{
	set("short", "�ĳ�");
	set("long", @LONG
������������СС�Ķ�����ֻҪ��˵�����Ķľߣ����ﶼ�С���
�����������������ľ�����Ů�ǳԳԵ�Ц���������ǵĴ�ţ����������
������������㼸���Ϳ��������������в���ص�������ǽ�Ϲ���һ
���ң�������
LONG);
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"qixiang3",
	]));
	set("item_desc", ([
		"sign": @TEXT
�����ӷ���:
bet <kind> <amount> <money> 

ֻ���������Ų���Ƿ��

kind:
    ͷ�� <tc>��������ÿ�ο���ǰȷ����      ��һӮ��ʮ��
    ˫�� <sd>����������ͬ����Ϊż����      ��һӮʮ
    ���� <qx>������֮��Ϊ�ߣ�	      ��һӮ��
    ɢ�� <sx>������֮��Ϊ�����壬�ţ�ʮһ����һӮ��
TEXT
	]));

	set("objects", ([
		__DIR__"npc/zhuangjia" : 1,
	]));

	set("no_fight", 1);
	setup();
}
void init()
{
	if (! interactive(this_player()))
		return;

	add_action("do_bet", "bet");

	if (room_status > 0)
		return;

	remove_call_out("gamble_prepare");
	remove_call_out("gamble_start");
	remove_call_out("gamble_perform");
	remove_call_out("gamble_finish");
	call_out ("gamble_prepare", 2);
	room_status = 1;
}

int do_bet(string arg)
{
	object me = this_player();
	string what;
	int amount;
	string money;
	object ob;
	object zj;

	if (! objectp(zj = present("zhuang jia", this_object())))
		return notify_fail("ׯ�Ҷ�û�У���Ҫ��˭�ģ�\n");

	if (! living(zj))
		return notify_fail("�㻹�ǵ�ׯ��������˵�ɣ�\n");

	if (! arg || sscanf (arg,"%s %d %s", what, amount, money) != 3)
		return notify_fail("��ʹ�ã� bet <Ѻ������> <��Ŀ> <����>\n");

	if (what != "tc" &&
	    what != "sd" &&
	    what != "qx" &&
	    what != "sx")
		return notify_fail("��ҪѺ��һ������\n");

	ob = present(money + "_money", me);
	if (! ob)
		return notify_fail("������û������Ǯ��\n");

	if (amount < 1)
		return notify_fail("���ѺһЩǮ��\n");

	if (amount > ob->query_amount())
		return notify_fail("�����ϵ�Ǯ����Ѻ��\n");

	if (amount > 1000)
		return notify_fail("ׯ�Һ�������ô�����������ô�ࣿ"
				   "������Ʊ������ע��\n");

	if (ob->query("base_value") * amount > 10000000)
		return notify_fail("��ע���һǧ���ƽ�\n");

	if (me->query_temp("gamble_bet/amount") > 0)
		return notify_fail("���Ѿ�Ѻ���ˡ�\n");

	if (room_status > 1)
		return notify_fail("�������ڶ��أ��Ե�Ƭ�̡�\n");

	me->set_temp("gamble_bet/kind", what);
	me->set_temp("gamble_bet/amount", amount);
	me->set_temp("gamble_bet/money", money);
	message_vision(sprintf("$N�ó�%s%s%s��Ѻ��%s�ϡ�\n",
			       chinese_number(amount),
			       ob->query("base_unit"),
			       ob->query("name"),
			       gutous[what]),
			       me);
	if (amount == ob->query_amount())
		destruct (ob);
	else
		ob->add_amount(-amount);

	if (! arrayp(query_temp("better")))
		set_temp("better", ({ me }));
	else
		add_temp("better", ({ me }));

	return 1;
}

int valid_leave(object me, string dir)
{
	if (dir == "south")
	{
		if (me->query_temp ("gamble_bet/amount") > 0) 
		message_vision ("$N����Ѻ����Ǯ����Ҫ�ˡ�\n",me);
		me->delete_temp("gamble_bet");
	}
	return ::valid_leave(me,dir);
}

void display_bet(object room, int i)
{
	string str;
	switch (i)
	{
	case 1:
		str = 
"����������\n"+
"����������\n"+
"�����񡡩�\n"+
"����������\n"+
"����������\n";

		break;
	case 2:
		str = 
"����������\n"+
"����������\n"+
"���񡡡�\n"+
"����������\n"+
"����������\n";
		break;
	case 3:
		str =
"����������\n"+
"���񡡡���\n"+
"�����񡡩�\n"+
"��������\n"+
"����������\n";
		break;
	case 4:
		str = 
"����������\n"+
"���񡡡�\n"+
"����������\n"+
"���񡡡�\n"+
"����������\n";
		break;
	case 5:
		str =
"����������\n"+
"���񡡡�\n"+
"�����񡡩�\n"+
"���񡡡�\n"+
"����������\n";
		break;
	case 6:
		str = 
"����������\n"+
"���񡡡�\n"+
"���񡡡�\n"+
"���񡡡�\n"+
"����������\n";
		break;
	}
	tell_room(room,str);
}

int rdm()
{
	return random2(6) + 1;
}

void gamble_prepare()
{
	object room = this_object();
	tell_room (room,"ׯ�ҳ������¿��̣�Ԥ��ͷ�ʣ�\n");
	tell_room (room,"ׯ�ҽ���ö������������һ����\n");
	big[0] = rdm();
	big[1] = rdm();
// keep two numbers different for a probability == 1/36
	while (big[0] == big[1])
	{
		reset_eval_cost();
		big[1] = rdm();
	}
	display_bet(room,big[0]);
	display_bet(room,big[1]);
	tell_room(room,"ׯ�ҽе���ͷ������"+chinese_number(big[0])+
	chinese_number(big[1])+"��\n");
	tell_room(room, "����ׯ��������˳�ֽ������������ջأ����ڿ���ѺǮ��\n");
	room_status = 1;
	call_out("gamble_start",24);
	delete_temp("better");
}
 
void gamble_start()
{
	object room = this_object();
	tell_room (room,"ׯ�Һ���������ͣѺ��\n");
	tell_room (room,"�ֲ���������ͷ��������"+chinese_number(big[0])+
	chinese_number(big[1])+"��\n");
	tell_room (room,"Ȼ����ö�����ӽ��������ѣ�һ�ֳ�һ��ҡ��������\n");
	room_status = 2;
	call_out("gamble_perform", 6, 0);
	call_out("gamble_perform", 12, 1);
	call_out("gamble_finish", 18);
}
void gamble_perform (int i)
{
	object room = this_object();
	tell_room(room, " ���ѵ����������ϣ��������˳�����\n");
	res[i] = rdm();
	display_bet (room,res[i]);
}

void player_wins(object who, int total)
{
	object money = new("/clone/money/" +
			   who->query_temp("gamble_bet/money"));
	int amount = who->query_temp("gamble_bet/amount");
	total = total * amount;
	money->set_amount(total);
	message_vision(sprintf("$NӮ��%s%s%s��\n",
		       chinese_number(total),
		       money->query("base_unit"),
		       money->query("name")),
		       who);
	money->move(who);
}

void player_loses(object who, int total)
{
	object money = new("/clone/money/" +
			   who->query_temp("gamble_bet/money"));
	total = who->query_temp("gamble_bet/amount");
	message_vision(sprintf("ׯ�ҽ�$NѺ�������е�%s%s%s���ߡ�\n",
			       chinese_number(total),
			       money->query("base_unit"),
			       money->query("name")),
			       who);
	destruct(money);
}

void gamble_finish()
{
	string win;
	int total, i;
	object room = this_object();
	object *list;

	if (res[0]==big[0] && res[1]==big[1])
	{
		total = 25;
		win = "tc";
	} else
	if (res[0]==res[1] && (res[0]/2*2 == res[0]))
	{
		total = 10;
		win = "sd";
	} else 
	{
		int r = res[0]+res[1];
		if (r==7)
		{
			total = 5;
			win = "qx";
		} else if (r==3 || r==5 || r==9 || r==11) 
		{
			total = 2;
			win = "sx";
		} else
		{
			total = 0;
			win = "none of them";
		}
	}
	if (total == 0)
		tell_room(room, "ׯ�ҽе���" + chinese_number(res[0])+
				chinese_number(res[1])+"�������̣�\n");
	else
		tell_room(room, "ׯ�ҽе���"+chinese_number(res[0])+
				chinese_number(res[1])+"����" +
					       gutous [win]+"��\n");
	list = query_temp("better");
	i = sizeof(list);
	while (i--)
	{
		if (! objectp(list[i]))
			continue;

		if (environment(list[i]) == room)
		{
			if (list[i]->query_temp("gamble_bet/kind") == win)
				player_wins(list[i],total); else
			if (list[i]->query_temp("gamble_bet/kind"))
				player_loses(list[i],total);
		}

		list[i]->delete_temp("gamble_bet");
	}
	tell_room (room,"\n");
	call_out ("gamble_prepare",5);
}

