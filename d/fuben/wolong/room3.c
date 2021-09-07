// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�������������Ĵ�����
LONG
	);
	set("exits", ([
		"south" : __DIR__"room2",
		"north" : __DIR__"room4",
		//"east" : __DIR__"room15",
		//"west" : __DIR__"room16",
	]));
	set("objects", ([
		__DIR__"npc/zongguan": 1,
		__DIR__"npc/huyuan": 4,
	]));
	setup();
}
int valid_leave(object me, string dir)
{
	object oba, obb, obc;
	object player;
	object *obs = all_inventory();
	
	oba = present("zong guan", environment(me));
	
	foreach(player in obs) {
		if (userp(player))
		{
			if (oba && dir == "north") {
				oba->kill_ob(player);
				player->kill_ob(oba);
				return notify_fail(oba->name()+"���������վס��\n");
			}
		}
	}
	return ::valid_leave(me, dir);
}

#include "/d/fuben/room_fb.h"
