// Room: /d/xingxiu/xxroad4.c

inherit ROOM;

void create()
{
	set("short", "С·");
	set("long", @LONG
ɽ�������･�����ƽ�������Ѿ�������������ɽ���׵�ˮ����������һ
��ɽ����
LONG );
	set("exits", ([
	    "south" : __DIR__"xxroad4",
	    "enter" : __DIR__"cangku",
	    "north" : __DIR__"xxroad6",
	]));
	set("objects", ([
	    CLASS_D("xingxiu")+"/chuchen" : 1,
	]) );
	set("outdoors", "xingxiu");
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (! objectp(guarder = present("chuchen zi", this_object())))
		return 1;

	if (dir == "north" || dir == "enter")
		return guarder->permit_pass(me, dir);

	return 1;
}

