#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
���������µĲ��������ϰ��ż������š�
LONG );
	set("exits", ([
		"west" : __DIR__"was_zoulang1",
	]));

	set("outdoors", "beijing");
	setup();
}


