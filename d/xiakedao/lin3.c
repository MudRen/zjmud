// Room: /xiakedao/lin3.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һƬï�ܵ����֣��ƺ����������������һ������һ�߽�
���������ʧ�˷���
LONG );
	set("outdoors", "xiakedao");
	set("exits", ([
		"east" : __FILE__,
		"west" : __DIR__"lin2",
		"south" : __FILE__,
		"north" : __FILE__,
		"southeast" : __DIR__"lin4",
		"northeast" : __FILE__,
	]));
	setup();
}
