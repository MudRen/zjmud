inherit ROOM;

#include <ansi.h>

void create()
{
	set("short","������Ժ");
	set("long", @LONG
�����������ĺ�Ժ��������һ����԰������һ�������ߵ�ֱͨ�����ݵ�
�鷿���ϱ�������˽����η�,�����ɼ������������������š�
LONG );
	set("exits", ([
		"north" :  __DIR__"aofu_naofang",
		"west" :  __DIR__"aofu_zoulang3",
		"south" :  __DIR__"aofu_zoulang2",
	]));
	set("objects", ([
		__DIR__"npc/shi_a" : 2,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	if (objectp(present("shi wei", environment(me))) && dir == "north")
		return notify_fail("����������ס�����û����ү�ķԸ���˭Ҳ���ܽ�ȥ��\n\n");
	return ::valid_leave(me, dir);
}
