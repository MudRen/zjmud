// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "�����䳡");
	set("long", @LONG
�������������Ķ����䳡��
LONG
	);
	set("exits", ([
		"west" : __DIR__"room2",
	]));
	set("objects", ([
		__DIR__"npc/jiaotou": 4,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"