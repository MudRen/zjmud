#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�᷿");
	set("long", @LONG
�����Ǻ��ι���������һ���᷿���������ι����Ŀ��˾�ס��
LONG );
	set("exits", ([
		"east" : __DIR__"hai_dayuan",
	]));

	set("sleep_room", "1");
	set("outdoors", "beijing");
	setup();
}
