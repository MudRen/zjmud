// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "Ժ��");
	set("long", @LONG
�����Ǳ��ڴ�Ժ�ӣ����г�����ɱ֮����
LONG
	);
	set("exits", ([
		"south" : __DIR__"enter",
		"north" : __DIR__"room2",
		"east" : __DIR__"room11",
		"west" : __DIR__"room14",
	]));
	set("objects", ([
		"/d/fuben/npc/hanfei": 2,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"