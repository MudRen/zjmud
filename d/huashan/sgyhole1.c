// sgyhole1.c
// By Hop, 97.04.30
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "ɽ��");
	set("long", @LONG
ɽ�����п������Ĵ�ʯ����֪�����ж��ٻ�ɽ�ɵ�ǰ���ڴ�˼����
�ڣ���������ʯ�������û��ʯ��(wall)�����š������������
�֣������������̣��ʻ��Ծ������а�硣�����̵ֿþ����Ƿ��������
���书һ��ʮ���˵á�
LONG );
	set("objects", ([
		CLASS_D("huashan")+"/linghu" : 1,
	]));
	set("exits", ([ /* sizeof() == 2 */
	    "out" : __DIR__"siguoya",
	]));
	set("item_desc", ([
	    "wall" : "һ��ܺ��ʯ�ڡ�\n"
	]) );
	setup();
}

void init()
{
	add_action("do_break", "break");
}

int do_break(string arg)
{
	int n;
	object weapon,me=this_player();
	mapping fam;

	if (! objectp(weapon = me->query_temp("weapon")))
		return notify_fail("��һ�ƴ���ʯ�ڣ����ֶ�����Ѫ��\n");

	message_vision(HIC "$N�ߵ�ʯ��ǰ������" + weapon->name() + "��������ʯ�ڴ��˹�ȥ��"NOR"\n", me);

	if (me->query("neili") < 200)
	{
		message_vision(HIC "���ֻ��һ���ƺߣ�$N��ʯ�ڵķ����������ǰһ��...."NOR"\n",
			       me);
		me->set("neili",0);
		me->unconcious();
		return 1;
	}

	message_vision(HIC "$Nֻ��һ�����죬ʯ�ھ�Ȼ��ͱ���ˣ�ԭ��������һ���󶴣�"NOR"\n", me);
	set("exits/enter",__DIR__"sgyhole");
	me->add("neili", -200);
	remove_call_out("close");
	call_out("close", 5, this_object());
	return 1;
}

void close_out()
{
	if (query("exits/enter")) delete("exits/enter");
}

void close(object room)
{
	message("vision","���Ϻ�Ȼ������һ���ʯ�������ڷ��˸�����ʵʵ��\n", room);
	room->delete("exits/enter");
}
