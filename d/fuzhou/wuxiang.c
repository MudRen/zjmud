// Room: /d/fuzhou/wuxiang.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
һ��СС���á�
LONG );
	set("exits", ([
		"south" : __DIR__"shulin",
	]));
	set("outdoors", "fuzhou");
	setup();
}

