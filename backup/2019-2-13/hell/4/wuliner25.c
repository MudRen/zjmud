
inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"wuliner24",
		"east" : __DIR__"wuliner26",
	]));
	set("price_build", 1000);
	setup();
}
