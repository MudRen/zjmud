#include <room.h>
inherit ROOM;
#include "jjroom.h"

void create()
{
	set("short", "��������");
	set("long", "���������ɾ��������ϲ���");
	set("exits", ([
		"northeast" : __DIR__"east",
		"north" : __DIR__"center",
		"northwest" : __DIR__"west",
	]));
	set("objects",([
	]));
	setup();
}
