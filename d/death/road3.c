// Room: /d/death/road3.c

inherit ROOM;

void create()
{
	set("short", "·�ľ�ͷ");
	set("long", @LONG

..... ��û�뵽 ....

LONG );
	set("exits", ([ /* sizeof() == 1 */
		"south" : "/d/death/road2",
	]));

	set("no_fight", 1);
	set("no_sleep_room", 1);

	setup();
}
