//by ���� ranger's ednpc tools.
// qian.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","������");
	set("long","�����Ƕ����󣬴�������δ�趨������ϸ������");
	set("owner_build","q456789");
	set("exits", ([
		"east" : "/data/home/q/q456789/hell/gong",
		"north" : "/data/home/q/q456789/hell/lian",
		"west" : "/data/hell/4/wulinsi11",
	]));
	set("objects", ([
	]));
	setup();
}

