// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "�����䳡");
	set("long", @LONG
�������������������䳡��
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