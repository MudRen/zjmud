//by 游侠 ranger's ednpc tools.
// lian.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","北方阁");
	set("long","这里是北方阁，创建者尚未设定本地详细描述。");
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

