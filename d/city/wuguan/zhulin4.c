//zhulin4.c by river

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
		"west" : __DIR__"jiashan",
		"south"  : __FILE__,
		"east"  : __FILE__,
		"north" : __FILE__,
	]));
	set("no_fight",1);
	setup();
}
