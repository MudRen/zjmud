// by ranger_����
// wanan.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", "���������¡�");
	set("exits", ([
		"north" : __DIR__"guangchang",
	]));
	set("objects", ([
		"/clone/fuben/wanansi/npc/kutoutuo": 1,
	]));
	setup();
}
