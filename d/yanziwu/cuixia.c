//room: /d/yanziwu/cuixia.c
inherit ROOM;

void create()
{
	set("short","��ϼ��");
	set("long",@LONG
����ׯ�ϣ����ȷǷ�����һ���žͲ��ɵľ�̾���ô�һ������! ��
�߷·���һ��С������������һƬ���֣�������һ�����ã���֪ͨ��ʲ
ô�ط���
LONG );
	set("exits",([
		"west" : __DIR__"xiaoting",
		"east" : __DIR__"zhulin1",
		"south": __DIR__"chuantang",
	]));

	set("objects",([
		__DIR__"npc/azhu" : 1,
		__DIR__"npc/deng" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (dir != "east")
		return 1;

	if (guarder = present("deng baichuan", this_object()))
		return guarder->permit_pass(me, dir);

	return 1;
}
