// Room: /city/duchang.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "�ĳ�");
	set("long", @LONG
��������������ͨ��ͬ�ķ��䡣�����ǹ���С�ݡ�
LONG );
	set("exits", ([
		"east"  : __DIR__ "eproom",
		"west"  : __DIR__ "wproom",
		"south" : __DIR__ "sproom",
		"north" : __DIR__ "nproom",
		"down"  : __DIR__"duchang",
	]));
	setup();
}

