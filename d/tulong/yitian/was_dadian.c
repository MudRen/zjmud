#include <ansi.h>

inherit ROOM;


void create()
{
	set("short", "���");
	set("long", @LONG
���������µĴ��ǳ��Ŀ����������ﱾ��������ɮ�����֮
��������ǰ����һ�����������ϵ���¯�в��ż����㡣���ϰ���һЩ���š�
����������ϥ�������档��������������ƫ�
LONG );
	set("exits", ([
		"north" : __DIR__"was_zoulang3",
		"south" : __DIR__"was_zoulang2",
		"east" : __DIR__"was_piandiane",
		"west" : __DIR__"was_piandianw",
	]));

	set("objects", ([
	    __DIR__"npc/18jingang-4bo" :2,
	]));

	setup();
}
int valid_leave(object me, string dir)
{
	if (dir == "north" && objectp(present("bo seng", environment(me))))
	   return notify_fail(CYN "��ɮ�����ȵ��������ߣ���������"NOR"\n");

	if (dir == "south" && objectp(present("bo seng", environment(me))))
	   return notify_fail(CYN "��ɮ�����ȵ��������ӣ���������"NOR"\n");

	if (dir == "west" && objectp(present("bo seng", environment(me))))
	   return notify_fail(CYN "��ɮ�����ȵ��������ӣ���������"NOR"\n");

	if (dir == "east" && objectp(present("bo seng", environment(me))))
	   return notify_fail(CYN "��ɮ�����ȵ��������ӣ���������"NOR"\n");

	return ::valid_leave(me, dir);
}

