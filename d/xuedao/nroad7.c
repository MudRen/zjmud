// nroad7.c
inherit ROOM;
void create()
{
	set("short", "ɽ·");
	set("long", @LONG
������һɽ·�ϣ�������һ����Сɽ��
LONG );
	set("exits", ([
		"eastdown" : "/d/xueshan/shanjiao",
		"south"    : __DIR__"nroad6",
	]));
	set("outdoors", "xuedao");
	setup();
}

