// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "ƫ��");
	set("long", @LONG
��������������һ��ƫ����
LONG
	);
	set("exits", ([
		"west" : __DIR__"room3",
	]));
	set("objects", ([
		__DIR__"npc/jiaotou": 4,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"