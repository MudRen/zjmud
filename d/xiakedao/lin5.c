// Room: /xiakedao/lin5.c

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
		"east" : __DIR__"lin4",
		"west" : __FILE__,
		"south" : __FILE__,
		"north" : __FILE__,
		"southeast" : __FILE__,
		"northwest" : __DIR__"lin6",
	]));
	setup();
}
