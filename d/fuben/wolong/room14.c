// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "西练武场");
	set("long", @LONG
这里是卧龙堡的西练武场。
LONG
	);
	set("exits", ([
		"east" : __DIR__"room2",
	]));
	set("objects", ([
		__DIR__"npc/jiaotou": 4,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"