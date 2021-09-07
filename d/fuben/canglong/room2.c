// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "Ӣ����");
	set("long", @LONG
������һ��������������������д�ż�����������Ĵ��֡�Ӣ��������
LONG
	);
	set("exits", ([
		"south" : __DIR__"room1",
		"north" : __DIR__"room3",
	]));
	set("objects", ([
		"/d/fuben/npc/hanfei": 2,
	]));
	setup();
}
int valid_leave(object me, string dir)
{
	object oba, obb, obc;
	object player;
	object *obs = all_inventory();
	
	oba = present("han fei", environment(me));
	
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
