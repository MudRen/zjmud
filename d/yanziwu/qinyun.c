//room: qinyun.c

inherit ROOM;

void create()
{
	set("short","����С��");
	set("long",@LONG
����һ��С������ķ��ᣬ��Ϊ���š���Χϡϡ����������С��
�ݣ�������һ����֪��С�����ǰ뵺�ϡ�
LONG );
	set("exits", ([
		"westdown" : __DIR__"muti",
		"east"     : __DIR__"xiaoting",
		"south"    : __DIR__"neitang",
	]));

	set("objects", ([
	 	__DIR__"npc/bao"  : 1,
		__DIR__"npc/feng" : 1,
	]));

	set("valid_startroom", 1);
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (dir != "east")
		return 1;

	if (guarder = present("bao butong", this_object()))
		return guarder->permit_pass(me, dir);

	if (guarder = present("feng boe", this_object()))
		return guarder->permit_pass(me, dir);

	return 1;
}
