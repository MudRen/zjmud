

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"wuliner19",
		"north" : __DIR__"wuliner21",
	]));
	set("price_build", 1000);
	setup();
}
