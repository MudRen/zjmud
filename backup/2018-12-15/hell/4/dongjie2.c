// by luoyun

inherit ROOM;

void create()
{
	set("short", "���ֶ���");
	set("long", "����һ����������ʯ�ֵ���");
	set("outdoors", "hell");
	set("exits", ([
		"west" : __DIR__"dongjie1",
		"east" : __DIR__"dongjie3",
	]));
	set("objects", ([
	]));
	setup();
}
