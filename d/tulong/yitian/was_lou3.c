#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "���µ�����");
	set("long", @LONG
���������µĵ����㣬��¥��վ�ż������Ż�����ĵĺ��С�һ������¥��
��������������
LONG);
	set("exits", ([
	    "down"  : __DIR__"was_lou2",
	    "up"    : __DIR__"was_lou4",
	]));

	set("objects", ([
	    __DIR__"npc/18jingang-5jian" :2,
	]));

	set("no_clean_up", 0);
	setup();
}
int valid_leave(object me, string dir)
{
	if (dir == "up" && objectp(present("jian seng", environment(me))))
	   return notify_fail(CYN "��ɮ�����ȵ��������ߣ���������"NOR"\n");

	if (dir == "down" && objectp(present("jian seng", environment(me))))
	   return notify_fail(CYN "��ɮ�����ȵ��������ӣ���������"NOR"\n");

	return ::valid_leave(me, dir);
}

