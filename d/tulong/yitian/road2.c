#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����·");
	set("long", @LONG
������һ�����ѵ�С·�ϣ�������������ˡ�
LONG );
	set("exits", ([
		"north" : __DIR__"road3",
		"west" : __DIR__"road1",
	]));

	set("outdoors", "beijing");
	setup();
}
