//Room: tuchangguan.c

inherit ROOM;

void create()
{
	set("short", "��潹�");
	set("long", @LONG
��û�����!�Ǻ�!
LONG);
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"huarui6",
	]));
	set("objects", ([
		__DIR__"npc/jinu" : 1,
	]) );

	setup();
}
