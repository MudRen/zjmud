// Room: /xiakedao/lin6.c

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
		"east" : __DIR__"lin7",
		"west" : __FILE__,
		"south" : __FILE__,
		"north" : __FILE__,
		"southeast" : __DIR__"lin5",
		"northwest" : __FILE__,
	]));
	setup();
}
