// by luoyun

inherit ROOM;

void create()
{
	set("short", "�����ĺ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"south" : __DIR__"beijie3",
		"north" : __DIR__"beijie5",
		"east" : __DIR__"wuliner1",
		"west" : __DIR__"wuliner28",
	]));
	set("objects", ([
	]));
	setup();
}