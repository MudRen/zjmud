inherit ROOM;
#include <ansi.h>
#include <room.h>

void create()
{
	set("short", "练功房");
	 set("long", "孤峰之上云海飘渺，天雾缭绕，时有微风洗面。美景如画，你仿佛来到了世外桃源。");

	set("valid_startroom",1);
	set("exits", ([
	]));
	setup();
}
