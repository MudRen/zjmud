//by ���� ranger's ednpc tools.
// gong.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","������");
	set("long","����������������������δ�趨������ϸ������");
	set("owner_build","q456789");
	set("exits", ([
		"west" : "/data/home/q/q456789/hell/qian",
	]));
	set("objects", ([
	]));
	set("practice_room", 1);
	set("owner_special", 1);
	setup();
}

