#include <room.h>
inherit ROOM;
#include "jjroom.h"

void create()
{
	set("short", "��������");
	set("long", "���������ɾ������ı�����");
	set("exits", ([
		"southeast" : __DIR__"east",
		"south" : __DIR__"center",
		"southwest" : __DIR__"west",
	]));
	set("objects",([
	]));
	setup();
}
