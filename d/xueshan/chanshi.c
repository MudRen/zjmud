//      chanshi.c ����
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������ɮ���Ų��������ĵط������һ���������˿�
�˾��뵽������¡�
LONG );
	set("no_fight",1);
	set("sleep_room",1);
	set("no_steal",1);
	set("exits", ([
		"southwest" : __DIR__"dating",
	]));
	setup();
}
