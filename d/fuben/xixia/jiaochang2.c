
#include <room.h>

inherit ROOM;
void create()
{
	set("short", "У����̨");
	set("long", @LONG
����������У���е�һ������ƽ̨��
LONG );
	set("exits", ([
		"south":__DIR__"jiaochang",
	]));
	set("objects", ([
	]));
	setup();
}

void heart_beat()
{
	object *inv;
	inv = all_inventory(this_object());
	if(!sizeof(inv)||(sizeof(inv)==1&&!playerp(inv[0])))
	{
		set_heart_beat(0);
		destruct(this_object());
	}
}

