// chang3.c С���䳡

inherit ROOM;

void create()
{
	set("short", "С���䳡");
	set("long", @LONG
������ѩɽ�µ�С���䳡�����źö�ľ׮��ɳ����ɮ
�����ճ����ڴ˿̿�ϰ�䡣�����߾��Ǵ����䳡�����ѩ
ɽ����������������
LONG );
	set("outdoors", "xueshan");

	set("exits", ([
		"north" : __DIR__"houyuan",
		"south" : __DIR__"chang",
	]));

	set("objects", ([
	    	"/clone/npc/mu-ren" : 3,
	]));

	setup();
}

