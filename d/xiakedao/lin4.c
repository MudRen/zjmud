// Room: /xiakedao/lin4.c

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
		"west" : __DIR__"lin5",
		"south" : __FILE__,
		"north" : __FILE__,
		"southeast" : __FILE__,
		"northwest" : __DIR__"lin3",
	]));
	setup();
}
