//zhulin2.c
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
		"north" : __DIR__"zhulin3",
		"east"  : __FILE__,
		"west"  : __FILE__,
		"south" : __FILE__,
	]));
	set("no_fight",1);
	setup();
}
