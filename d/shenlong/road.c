#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
����һ�����Ĵ����ȫ����ʯ�ѳɣ���Ȼ�����˲�����������
����һƬ�����ء�
LONG );

	set("exits", ([
		"west" : __DIR__"kongdi",
		"north" : __DIR__"road2",
	]));
	set("objects", ([
		__DIR__"npc/old": 2,
	]));
	set("outdoors", "shenlong");
	setup();
}

