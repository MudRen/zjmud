// by luoyun

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"wuliner1",
		"east" : __DIR__"wuliner3",
	]));
	set("price_build", 1000);
	setup();
}