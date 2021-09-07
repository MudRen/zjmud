// Room: /d/shaolin/hanshui2.c
#include <ansi.h>
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
void reset();
int do_yell(string arg);


void create()
{
	set("short", "��ˮ����");
	set("long", @LONG
��ˮ����Ҳ���൱���֣��Ա����ɿ�������һ����ֱ�Ĺٵ�
ֱͨ�������˵���紾�ӣ�·�Լ��������������������Ҷ���һ
����ġ��ơ���ӭ��Ʈ�εΪ׳�ۡ�Ҳ�в���С����·����
����ѱ棬ȴҲ����ʢ����ȴ��
LONG );

	set("exits", ([
		"north" : __DIR__"nanyang",
	]));

	set("item_desc", ([
		"�����ߡ�" : "��������һҶС�ۣ�Ҳ��(yell)һ�����Ҿ���������\n"
			ZJOBACTS2"�д�:yell boat"ZJSEP"һέ�ɽ�:cross\n",
	]));

	set("objects", ([
		__DIR__"npc/chuanfu2" : 1,
	]));

	set("outdoors", "nanyang");
	set("resource/fish", ({ "/clone/fish/liyu",
				"/clone/fish/jiyu",
				"/clone/fish/qingyu",
				"/clone/fish/caoyu", }));
	setup();
}

/* �ڴ˸�Ǯ�ڶɻ������ */
/*���ȣ��ɴ����˰�������Ǯ������һ��ߺ�ȣ�������һӿ
 * ���룬СС�ɴ�Ƭ�̼��Խ���������εĺ��������ϱ���
 */
void init()
{
	add_action("do_yell", "yell");
	add_action("do_cross", "cross");
}

void check_trigger()
{
	object room;

	if (! query("exits/enter"))
	{
		if (! (room = find_object(__DIR__"duchuan")))
			room = load_object(__DIR__"duchuan");
		if (room = find_object(__DIR__"duchuan"))
		{
			if ((int)room->query("yell_trigger") == 0)
			{
				room->set("yell_trigger", 1);
				set("exits/enter", __DIR__"duchuan");
				room->set("exits/out", __FILE__);
				message("vision", "һҶ���ۻ�����ʻ�˹�����������һ��̤��"
						  "����ϵ̰����Ա�˿����¡�\n", this_object());
				message("vision", "������һ��̤�Ű���ϵ̰����γ�һ������"
						  "�Ľ��ݡ�\n", room);
				remove_call_out("on_board");
				call_out("on_board", 15);
			} else
				message("vision", "ֻ���ý��������������������"
						  "�����æ���š�����\n",this_object());
		} else
			message("vision", "ERROR: boat not found\n", this_object());
	} else 
		message("vision", "����һֻ�ɴ��ϵ�������˵�������������أ������ɡ�\n",
			this_object());
}


void on_board()
{
	object room;

	if (! query("exits/enter")) return;

	message("vision", "������̤�Ű��������������һ�㣬��������ʻȥ��\n",
		this_object() );

	if (room = find_object(__DIR__"duchuan"))
	{
		room->delete("exits/out");
		message("vision", "������̤�Ű���������˵��һ��������ඡ���"
			"���һ�㣬��������ʻȥ��\n", room);
	}
	delete("exits/enter");

	remove_call_out("arrive");
	call_out("arrive", 20);
}

void arrive()
{
	object room;

	if (room = find_object(__DIR__"duchuan"))
	{
		room->set("exits/out", __DIR__"hanshui1");
		message("vision", "����˵���������ϰ��ɡ����漴��һ��̤�Ű�"
			"���ϵ̰���\n", room);
	}
	remove_call_out("close_passage");
	call_out("close_passage", 20);
}

void close_passage()
{
	object room;
	if (room = find_object(__DIR__"duchuan"))
	{
		room->delete("exits/out");
		message("vision","������̤�Ű����������ѱ���ʻ���ġ�\n", room);
		room->delete("yell_trigger"); 
	}
}

int do_yell(string arg)
{
	string dir;

	if (! arg || arg == "") return 0;

	if (arg == "boat") arg = "����";
	if ((int)this_player()->query("age") < 16)
		message_vision("$Nʹ�����̵���������һ������" + arg + "��\n",
			       this_player());
	else
	if ((int)this_player()->query("neili") > 600)
		message_vision("$N���˿�����һ����" + arg + "������������ƽ�͵�ԶԶ��"
			       "�˳�ȥ��\n", this_player());
	else
		message_vision("$N������������Хһ������" + arg + "����\n",
			       this_player());
	if (arg == "����")
	{
		check_trigger();
		return 1;
	} else
		message_vision("������ԶԶ����һ���������" + arg +
			       "��������\n", this_player());
	return 1;
}

int do_cross()
{
	object me;

	me = this_player();
	if (! me->query_skill("shaolin-shenfa", 1))
	{
		tell_object(me, "�����һ�ɣ���ʲô��������ɱô��\n");
		return 1;
	}

	if (me->query_skill("shaolin-shenfa", 1) < 150)
	{
		tell_object(me, "�������һ�£������Լ�һέ"
			    "�ɽ��ľ�����û�������ҡ�\n");
		return 1;
	}

	if (me->query("neili") < 120)
	{
		tell_object(me, "�������������������Ϣһ����˵�ɡ�\n");
		return 1;
	}

	me->add("neili", -90);

	message_sort(HIW "$N" HIW"����һ�Σ���ƮƮ�����뺺ˮ"
		     "��ֻ��$P" HIW"���ˮ�棬������ң����Ȼ"
		     "�Ǵ�Ħ��ʦ���µ����־�����һέ�ɽ�����"
		     "���˲�����̾��$N" HIW "�Ѿ�̤��Զȥ��"NOR"\n", me);
	tell_object(me, "��˳���ĵ����˱˰���\n");
	me->move(__DIR__"hanshui1");
	message("vision", "����ˮ��������ɢ����һ��̤�����ˣ�"
		"��Ȼ��̤���ӹ�������\n", environment(me), ({ me }));
	return 1;
}
