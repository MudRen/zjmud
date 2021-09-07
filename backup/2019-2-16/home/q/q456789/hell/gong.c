//by 游侠 ranger's ednpc tools.
// gong.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","练功房");
	set("long","这里是练功房，创建者尚未设定本地详细描述。");
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

