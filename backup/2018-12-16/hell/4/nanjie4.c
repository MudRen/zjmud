// by luoyun

inherit ROOM;

void create()
{
	set("short", "�Ͻ��ĺ�");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"nanjie3",
		"south" : __DIR__"nanjie5",
		"east" : __DIR__"wuliner14",
		"west" : __DIR__"wuliner15",
	]));
	set("objects", ([
	]));
	setup();
}