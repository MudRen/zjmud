// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "���䳡");
	set("long", @LONG
�����������������䳡������վ���ż����������ݵĴ󺺡�
LONG
	);
	set("exits", ([
		"north" : __DIR__"room3",
		"south" : __DIR__"room1",
		"east" : __DIR__"room13",
		"west" : __DIR__"room14",
	]));
	set("room_hide", 1);
	set("objects", ([
		__DIR__"npc/zjiaotou": 1,
		__DIR__"npc/huyuan": 4,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"