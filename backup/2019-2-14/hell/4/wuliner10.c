

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"wuliner9",
		"south" : __DIR__"wuliner11",
	]));
	set("price_build", 1000);
	setup();
}
