// Room: /d/city/jiaowai7.c

#include <room.h>

inherit BUILD_ROOM;

void create()
{
	set("short", "�ݵ�");
	set("long", @LONG
�������ݽ����һƬ���ݵأ���Ӣ�ͷף������裬��¶
Ϧ�⣬������Ƣ������̤��Զ���ʱ�⡣
LONG );
	 set("max_room", 8);
	set("exits", ([
		"east" : __DIR__"jiaowai6",
		"west" : __DIR__"nanmen",
	]));

	set("outdoors", "city");
	setup();
	replace_program(BUILD_ROOM);
}
