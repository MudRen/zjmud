#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һ�����ȣ����߶���ʯͷ���ӡ������Ǵ����������ǳ�����
������һƬ���������䳡������������Ϣ�ҡ�
LONG );

	set("exits", ([
		"east" : __DIR__"chufang",
		"west" : __DIR__"dating",
		"south" : __DIR__"wuchang",
		"north" : __DIR__"xiuxishi",
	]));
	set("objects", ([
		CLASS_D("shenlong")+"/zhang" : 1,
	]));
	set("outdoors", "shenlong");
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (dir == "west" )
		return 1;

	if (objectp(guarder = present("zhang danyue", this_object())))
		return guarder->permit_pass(me, dir);

	return 1;
}
