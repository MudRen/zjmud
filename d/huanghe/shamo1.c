// Room: /huanghe/shamo.c
#include <room.h>
#include <ansi.h>

inherit ROOM;
void create()
{
	set("short", "ɳĮ");
	set("long", @LONG
����һƬû�߼ʵ�ɳĮ�������ǽ����׸ߵľ޴�ɳ����һ�߽���
�ͷ·�����·��
LONG );
	set("exits", ([
		"north" : __FILE__,
		"south" : __DIR__"shamo1",
		"east"  : __FILE__,
		"west"  : __FILE__,
		"enter" : __DIR__"shidong",
	]));
	set("outdoors", "huanghe");
	setup();
}

void init()
{
	object ob = this_player();

	if (ob->query("water") > 10)
		ob->add("water", -10);
	else
		ob->set("water", 0 );

	message_vision(HIY "�����ɳ��$N" HIY "�е�����ð�̣��ɿ��Ѱ���"NOR"\n", ob);
}

int valid_leave(object me, string dir)
{
	int total_steps = 10;

	if (dir == "north")
		me->add_temp("shamo/steps", 1);

	if (dir == "south")
		me->add_temp("shamo/steps", -1);

	if (me->query_temp("shamo/steps") == total_steps)
	{
		me->move(__DIR__"jingyuan");
		me->delete_temp("shamo/steps");
		write("�����˰��죬�����߳�������ɳĮ��\n");
		return -1;
	}

	if (me->query_temp("shamo/steps") == -total_steps)
	{
		me->move(__DIR__"qingcheng");
		me->delete_temp("shamo/steps");
		write("�����˰��죬�����߳�������ɳĮ��\n");
		return -1;
     	}
	return ::valid_leave(me,dir);
}
