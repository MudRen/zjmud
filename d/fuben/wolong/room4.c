// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "��Ժ");
	set("long", @LONG
�������������ĺ�Ժ���Ǳ�����Х�����ڵĵط���
LONG
	);
	set("exits", ([
		"south" : __DIR__"room3",
	]));
	set("objects", ([
		__DIR__"npc/baozhu" : 1,
		__DIR__"npc/jiaotou": 4,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"
