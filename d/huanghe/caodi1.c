// Room: /huanghe/caodi1.c
// Java. Sep 21 1998

#include <ansi.h>

inherit BUILD_ROOM;
void create()
{
	set("short", "�ݵ�");
	set("long", @LONG
������һ��������Ĳݵأ�����һ����ɫ��̺�����ڵ��ϡ��ݴ���
����һЩ��֪����С�����к�ġ��Ƶģ������ϵġ������ϡ���Ҷ�ϵ�
¶�����ž�Ө�Ĺ⡣���������ݳǵı��š�
LONG );
	set("exits", ([
		"east" : "/d/city/beimen",
		"west" : __DIR__"caodi2",
	]));
	set("max_room", 2);
	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	setup();
	replace_program(BUILD_ROOM);
}

