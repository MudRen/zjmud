// Room: /city/milin.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����һƬï�ܵ������֣�һ�߽�������·���ʧ�˷���
LONG );
	set("exits", ([
		"east" : __FILE__,
		"west" : __FILE__,
		"south" : __DIR__"dongmen",
		"enter" : __DIR__"gbxiaowu",
		"north" : __DIR__"pomiao",
	]));
	set("outdoors", "city");
	setup();
}
