#include <room.h>
inherit ROOM;
#include "jjroom.h"

void create()
{
	set("short", "��������");
	set("long", "���������ɾ����������롣");
	set("exits", ([
		"south" : __DIR__"south",
		"north" : __DIR__"north",
		"east" : __DIR__"east",
		"west" : __DIR__"west",
	]));
	set("objects",([
	]));
	setup();
}
