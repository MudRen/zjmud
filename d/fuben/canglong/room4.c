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
	]));
	set("room_hide", 1);
	set("auto_kill", 1);
	set("objects", ([
		"/d/fuben/npc/hanfei": 2,
		"/d/fuben/npc/hanfeitou": 2,
		"/d/fuben/obj/baoxiang1": 1,
	]));
	setup();
}
#include "/d/fuben/room_fb.h"