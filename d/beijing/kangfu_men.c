inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","��������");
	set("long", @LONG
������ǿ������������������ڡ��������һ�������ûʵľ�լԺ����
�������ǰ��������������ͷ�ߴ��ʯʨ�ӡ����Ϲ���������������Ȼд�Ŵ�
��ġ������֡���ǰվ�������ᵶ�������������ע���Ź��������ˡ�
LONG );
	set("exits", ([
		"west" : __DIR__"bei_2",
		"east" : __DIR__"kangfu_dayuan",
	]));
	set("objects", ([
		__DIR__"npc/shi_k" : 2,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	if (objectp(present("shi wei", environment(me))) && dir == "east")
		return notify_fail("��������һ����ס�㣬�����ȵ�������Ҫ�أ����������˵���������\n\n");
	return ::valid_leave(me, dir);
}
