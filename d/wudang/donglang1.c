// donglang1.c ��������
#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
������һ�������ϣ������м������ң��������������֡������Ǵ�
LONG );
	set("exits", ([
		"east" : __DIR__"donglang2",
		"west" : __DIR__"sanqingdian",
	]));
	set("objects", ([
		CLASS_D("wudang") + "/xi" : 1
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (dir != "east")
		return 1;

	if (! objectp(guarder = present("zhang songxi", environment(me))))
		return 1;

	return guarder->permit_pass(me, dir);
}
