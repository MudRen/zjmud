//zoulang6.c
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һ�����ȣ��ȶ�����Ž��������ķ羰��ÿ��������ɫ�����Ӽ����
Ҳ�������ߵľ��룬���ɫ�������ߣ��ۻ�ɫ�ĵ�ש�����������棬Ѿ�ߡ�ū
����������ȥ����æ���Լ������飬������һ�㵡�����������߶������ȣ���
������Ϲ������鷿�ˡ�
LONG
	);
	set("no_fight",1);
	set("exits", ([
		"west" : __DIR__"zoulang5",
		"east" : __DIR__"zoulang7",
		"north" : __DIR__"shufang",
		"south" :__DIR__"zhangfang",
	]));

	setup();
}
