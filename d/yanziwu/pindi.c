//ROOM: /d/yanziwu/pindi.c

inherit ROOM;

void create()
{
	set("short", "Ʒ��ͥ");
	set("long",@LONG
ֻ��ǽ�Ϲ�������֮������������Ϸ���һ����ף�����Ľ������
���������������ˡ��������͵���̫�����ߣ�������Ľ�����ҽӴ���
�͵��������ˡ�
LONG );
	set("exits", ([
	    "east"  : __DIR__"longfeng",
	    "west"  : __DIR__"bozhou",
	]));

	set("objects", ([
	 	__DIR__"npc/gongye"  : 1,
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (dir != "east")
		return 1;

	if (guarder = present("gongye qian", this_object()))
		return guarder->permit_pass(me, dir);

	return 1;
}
