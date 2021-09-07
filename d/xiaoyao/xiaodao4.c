// xiaodao1.c

inherit ROOM;

void create()
{
	set("short", "�ּ�С��");
	set("long", @LONG
����һ���������ּ�С�����Ӷ���һֱͨ�����ߣ�һ����ȥ��������·
�ľ�ͷ�����԰ٻ����ޡ���������������
LONG
	);
	set("exits", ([
		"east" : __DIR__"shulin1",
		"west" : __DIR__"qingcaop",
		"north" : __DIR__"jingji/enter",
		"south" : __DIR__"mubanlu",
	]));

	set("objects", ([
		CLASS_D("xiaoyao") + "/goudu": 1,
		__DIR__"npc/mengmianr": 2,
	]));

	set("outdoors", "xiaoyao");
	set("valid_startroom", 1);
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (dir !="west")
		return 1;

	if (! objectp(guarder = present("gou du", this_object())))
		return 1;

	return guarder->permit_pass(me, dir);
}

