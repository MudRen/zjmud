// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����һ���ųǱ����Ĵ��������壬�����г���Ѫ�ȵ�ζ������Խ��Խ���¡�����
LONG
	);
	set("exits", ([
		"south" : __DIR__"room"+(random(10)+1),
		"north" : __DIR__"room"+(random(10)+1),
		"up" : __DIR__"room"+(random(10)+1),
		"down" : __DIR__"room"+(random(10)+1),
		"west" : __DIR__"room"+(random(10)+1),
		"east" : __DIR__"room"+(random(10)+1),
	]));

	setup();
}
#include "/d/fuben/room_fb.h"