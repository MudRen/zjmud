#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
���������µĺ��ǳ��Ŀ�����������ǰ����һ�����������ϵ�
��¯�в��ż����㣬���ϰ���һЩ���š����״�һ��ľ�ƽ��ݣ�����ͨ����
���µ���¥��
LONG);
	set("exits", ([
	    "south"  : __DIR__"was_zoulang3",
	    "up"    : __DIR__"was_lou2",
	]));

	set("objects", ([
	    __DIR__"npc/18jingang-5dao" :2,
	]));

	set("no_clean_up", 0);
	setup();
}
int valid_leave(object me, string dir)
{
	if (dir == "up" && objectp(present("dao seng", environment(me))))
	   return notify_fail(CYN "��ɮ�����ȵ��������ߣ���������"NOR"\n");

	if (dir == "south" && objectp(present("dao seng", environment(me))))
	   return notify_fail(CYN "��ɮ�����ȵ��������ӣ���������"NOR"\n");

	return ::valid_leave(me, dir);
}

