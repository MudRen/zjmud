#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����·");
	set("long", @LONG
������һ�����ѵ�С·�ϣ�������������ˣ��䱸�������ϡ�
LONG );
	set("exits", ([
		"north" : __DIR__"was_damen",
		"south" : __DIR__"road2",
	]));

	set("objects", ([
		__DIR__"npc/bing1" : 2,
	]));

	set("outdoors", "beijing");
	setup();
}
