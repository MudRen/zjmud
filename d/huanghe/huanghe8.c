// Room: /huanghe/huanghe8.c
// Java. Sep 21 1998

#include <ansi.h>

inherit BUILD_ROOM;

void create()
{
	set("short", "�ƺ��뺣��");
	set("long", @LONG
�ƺ�������ظ�ԭ��������ԭ������ƽԭ���ܳ�һ����Ű��
���������󺣡�
LONG );
	set("max_room", 3);
	set("exits", ([
		"southwest" : __DIR__"huanghe7",
	]));
	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	setup();
	replace_program(BUILD_ROOM);
}

