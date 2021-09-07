// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "东厢房");
	set("long", @LONG
这里是山寨里的一处东厢房。
LONG
	);
	set("exits", ([
		"south" : __DIR__"room12",
		"north" : __DIR__"room13",
		"west" : __DIR__"room1",
	]));
	set("objects", ([
		"/d/fuben/npc/tufei": 1,
		"/d/fuben/obj/baoxiang": 1,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"