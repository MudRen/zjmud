//zoulang1.c
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һ�����ȣ��ȶ�����Ž��������ķ羰��ÿ��������ɫ�����Ӽ����
Ҳ�������ߵľ��룬���ɫ�������ߣ��ۻ�ɫ�ĵ�ש�����������棬Ѿ�ߡ�ū
����������ȥ����æ���Լ������飬������һ�㵡�������洫���������˵���
���������߾͵��˺�Ժ��������һ�����䳡��
LONG
	);
	set("no_fight",1);
	set("exits", ([
		"west" : __DIR__"chufang",
		"east" : __DIR__"zoulang2",
		"north" : __DIR__"shilu1",
		"south" : __DIR__"wuchang2",
	]));

	setup();
}
