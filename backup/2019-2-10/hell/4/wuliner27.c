

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"wuliner26",
		"east" : __DIR__"wuliner28",
	]));
	set("price_build", 1000);
	setup();
}
