//by 游侠 ranger's ednpc tools.
// qian.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","东方阁");
	set("long","这里是东方阁，创建者尚未设定本地详细描述。");
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

