// Room: /d/city/jiaowai1.c

#include <ansi.h>

inherit BUILD_ROOM;

void create()
{
	set("short", "�ݵ�");
	set("long", @LONG
�������ݽ����һƬ���ݵأ���Ӣ�ͷף������裬��¶
Ϧ�⣬������Ƣ�����Ǻ�ʱ�⡣ż�м���С��Ů���̤�࣬ݺ
����Ӱ�����ֶ��ˡ�
LONG );

	set("max_room", 4);
	set("exits", ([
		"north" : __DIR__"dongmen",
		"south" : __DIR__"jiaowai2",
	]));

	set("outdoors", "city");
	setup();
	replace_program(BUILD_ROOM);
}
