

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"wuliner17",
		"north" : __DIR__"wuliner19",
	]));
	set("price_build", 1000);
	setup();
}
