// Room: /xiakedao/lin7.c

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
		"west" : __DIR__"lin6",
		"south" : __DIR__"lin8",
		"north" : __FILE__,
		"southeast" : __FILE__,
		"northwest" : __FILE__,
	]));
	setup();
}
