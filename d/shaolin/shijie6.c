// Room: /d/shaolin/shijie6.c
// Date: YZC 96/01/19

#include <ansi.h>

inherit BUILD_ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
�������ٲ��Ϸ�һ��խխ��ɽ������Ȼ��ɡ�ʯ�������˹�
���һ�����ݡ����϶��˼���ľ׮�����ϴֳ���������Ϊ���֡�
�ٲ��ڽ��±��ڶ������ڲ�Զ��ɽ���»��һ����̶��
LONG );
	set("max_room", 1);
	set("exits", ([
		"southdown" : __DIR__"shijie5",
		"northup" : __DIR__"shijie7",
	]));
	set("outdoors", "shaolin");
	setup();
	replace_program(BUILD_ROOM);
}

