#include <room.h>
inherit ROOM;
#include "jjroom.h"

void create()
{
	set("short", "��������");
	set("long", "���������ɾ������Ķ�����");
	set("exits", ([
		"southwest" : __DIR__"south",
		"west" : __DIR__"center",
		"northwest" : __DIR__"north",
	]));
	set("objects",([
	]));
	setup();
}
