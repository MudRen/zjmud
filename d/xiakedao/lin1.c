// Room: /xiakedao/lin1.c

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
		"west" : __FILE__,
		"south" : __DIR__"lin2",
		"north" : __DIR__"haitan",
	]));
	setup();
}
