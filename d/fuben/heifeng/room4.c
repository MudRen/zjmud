// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����Ǻڷ�կ���ң����˺��ѷ��֡�
LONG
	);
	set("exits", ([
		"up" : __DIR__"room3",
	]));
	set("room_hide", 1);
	set("objects", ([
		"/d/fuben/npc/tufei": 2,
		"/d/fuben/npc/hanfei": 1,
		"/d/fuben/obj/baoxiang1": 1,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"