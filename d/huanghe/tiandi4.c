// Room: /huanghe/tiandi4.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "���");
	set("long", @LONG
������һ��Ƭũ���Զ����һЩ��ׯ�������������𡣴�ׯ��Χ
��һ������أ�������һЩ���ڸ�����ũ�ˡ����ﲻʱ����һ������
Ȯ�͡�
LONG );
	set("exits", ([
		"southwest" : __DIR__"tiandi3",
		"north"     : __DIR__"huanghe1",
	]));
	set("objects", ([
		"/d/village/npc/dog" : 1,
	]));
	set("no_clean_up", 0);
	set("outdoors", "huanghe");
	setup();
}
