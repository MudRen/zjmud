#include <room.h>
inherit ROOM;
#include "jjroom.h"

void create()
{
	set("short", "��������");
	set("long", "���������ɾ�������������");
	set("exits", ([
		"southeast" : __DIR__"south",
		"east" : __DIR__"center",
		"northeast" : __DIR__"north",
	]));
	set("objects",([
	]));
	setup();
}
