//zhulin1.c
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������һ��Ƭ���ܵ����֣������дУ�һ����������ͷ��΢�紵������Ҷ��
���˳���Ϊ֮һ�ӣ�����������������ȥ���ߣ���Ҫ�ҵ�������·����������
������ֻ���û���ҵ�������·��
LONG
	);
	set("outdoors","���");
	set("exits", ([
		"east"  : __DIR__"zhulin2",
		"west"  : __FILE__,
		"north" : __FILE__,
		"south" : __FILE__,
	]));
	set("no_fight",1);
	setup();
}
