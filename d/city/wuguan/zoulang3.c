//zoulang3.c
inherit ROOM;
void create()
{
	set("short", "����");
	set("long", @LONG
����һ�����ȣ��ȶ�����Ž��������ķ羰��ÿ��������ɫ�����Ӽ����
Ҳ�������ߵľ��룬���ɫ�������ߣ��ۻ�ɫ�ĵ�ש���ڳ������棬Ѿ�ߡ�ū
����������ȥ����æ���Լ������飬������һ�㵡����������ǹ����������ˣ�
����������Ƕ������᷿��
LONG
	);
	set("no_fight",1);
	set("exits", ([
		"east" : __DIR__"xiangfang1",
		"north" : __DIR__"woshi",
		"south" : __DIR__"zoulang4",
	]));

	setup();
}
