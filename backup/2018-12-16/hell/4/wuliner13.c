

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"wuliner12",
		"west" : __DIR__"wuliner14",
	]));
	set("price_build", 1000);
	setup();
}
