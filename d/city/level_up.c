// Room: /city/level_up.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
���������ݹ㳡�������ϵ����ݣ�angelus������Ϊ�����ҷ����������ڹ㳡�Ĵ������ϡ�
LONG );
	set("no_fight", 1);
	set("exits", ([
		"down" : __DIR__"shiji",
		"east" : __DIR__"guest",
	]));
	set("objects", ([
		__DIR__"npc/angelus": 1,
		__DIR__"npc/jihaolan" : 1,
	]));
	setup();
}

