#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "���µڶ���");
	set("long", @LONG
���������µĵڶ��㣬��¥��վ�ż������Ż�����ĵĺ��С�һ������¥��
��������������
LONG);
	set("exits", ([
	    "down"  : __DIR__"was_houdian",
	    "up"    : __DIR__"was_lou3",
	]));

	set("objects", ([
	    __DIR__"npc/18jingang-4zhang" :2,
	]));

	set("no_clean_up", 0);
	setup();
}
int valid_leave(object me, string dir)
{
	if (dir == "up" && objectp(present("zhang seng", environment(me))))
	   return notify_fail(CYN "��ɮ�����ȵ��������ߣ���������"NOR"\n");

	if (dir == "down" && objectp(present("zhang seng", environment(me))))
	   return notify_fail(CYN "��ɮ�����ȵ��������ӣ���������"NOR"\n");

	return ::valid_leave(me, dir);
}


