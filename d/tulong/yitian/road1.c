#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����·");
	set("long", @LONG
������һ�����ѵ�С·�ϡ��ϱ߷���һ��С�߸ڿ��Իص����ǡ�
LONG );
	set("exits", ([
		"east" : __DIR__"road2",
	]));

	set("outdoors", "beijing");
	setup();
}
void init()
{
	object me = this_player();
	
	if (playerp(me)) {
		message_vision(HIB "ҹ�Ѿ����ˣ������ϱߵ�С�߸ڿ�����С·���ؾ��ǡ�"NOR"\n", me);
		remove_call_out("mes");
		call_out("mes",1,this_player());
		this_player()->set_temp("want_leave",1);
		add_action("do_leave", "leave");
	}
}

void mes(object me)
{
	if (me)
		tell_object(me, HIR "���Ƿ�Ը�����£�"NOR"\n"+ZJURL("cmds:leave")+ZJSIZE(22)+"�뿪����"NOR"\n");
}

int do_leave()
{
	object me = this_player();
	if (me->query_temp("want_leave")) 
	{
		tell_object(me, HIR "������뿪���¡�\n");
		me->move("/d/heimuya/road3");
	}
	return 1;
}
