// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "���᷿");
	set("long", @LONG
������ɽկ���һ�����᷿��
LONG
	);
	set("exits", ([
		"south" : __DIR__"room15",
		"north" : __DIR__"room16",
		"east" : __DIR__"room1",
	]));
	set("objects", ([
		"/d/fuben/npc/tufei": 1,
		"/d/fuben/obj/baoxiang": 1,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"