//by ���� ranger's ednpc tools.
// lian.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","������");
	set("long","�����Ǳ����󣬴�������δ�趨������ϸ������");
	set("owner_build","q456789");
	set("exits", ([
		"south" : "/data/home/q/q456789/hell/qian",
	]));
	set("objects", ([
	]));
	set("close_room", 1);
	set("owner_special", 1);
	setup();
}

