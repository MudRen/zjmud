// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "���᷿");
	set("long", @LONG
��������������һ���᷿��
LONG
	);
	set("exits", ([
		"east" : __DIR__"room1",
	]));
	set("objects", ([
		__DIR__"npc/jiaotou": 4,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"