// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "��Ժ");
	set("long", @LONG
��������������Ժ�������ż�����Ժ��
LONG
	);
	set("exits", ([
		"south" : __DIR__"room0",
		"north" : __DIR__"room2",
		"east" : __DIR__"room11",
		"west" : __DIR__"room12",
	]));
	set("objects", ([
		__DIR__"npc/huyuan": 4,
	]));
	setup();
}
int valid_leave(object me, string dir)
{
	object oba;
	object player;
	object *obs = all_inventory();
	
	oba = present("hu yuan", environment(me));
	
	foreach(player in obs) {
		if (userp(player))
		{
			if (oba && (dir == "north" || dir == "west" || dir == "east")) {
				oba->kill_ob(player);
				player->kill_ob(oba);
				return notify_fail(oba->name()+"����������������ֵ��ǣ��������ϡ�\n");
			}
		}
	}
	return ::valid_leave(me, dir);
}
#include "/d/fuben/room_fb.h"