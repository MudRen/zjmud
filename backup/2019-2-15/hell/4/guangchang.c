// by luoyun

inherit ROOM;

void create()
{
	set("short", "����㳡");
	set("long", "�����ǿ���֮�ǵ�����㳡�������������ַǷ���");
	set("outdoors", "hell");
	set("exits", ([
		"north" : __DIR__"beijie1",
		"south" : __DIR__"nanjie1",
		"west" : __DIR__"xijie1",
		"east" : __DIR__"dongjie1",
	]));
	set("objects", ([
	]));
	setup();
}

