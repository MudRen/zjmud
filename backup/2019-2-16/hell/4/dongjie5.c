// by luoyun

inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"east" : __DIR__"dongjie6",
		"west" : __DIR__"dongjie4",
		"north" : __DIR__"wulinsan9",
		"south" : __DIR__"wulinsan10",
	]));
	set("objects", ([
	]));
	setup();
}
