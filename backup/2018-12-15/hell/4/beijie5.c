// by luoyun

inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"beijie4",
		"east" : __DIR__"wulinsan1",
		"west" : __DIR__"wulinsan36",
		"north" : __DIR__"beijie6",
	]));
	set("objects", ([
	]));
	setup();
}