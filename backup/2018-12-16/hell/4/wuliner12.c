

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"wuliner11",
		"west" : __DIR__"wuliner13",
	]));
	set("price_build", 1000);
	setup();
}
