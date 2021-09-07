// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
��������������Ĵ��ţ���˵����ۼ��������֣�������Х�쵱�괳���������������Ķ����������ڴ˴������ű��������ż��������ӵ�ׯ����
LONG
	);
	set("exits", ([
		"south" : __DIR__"enter",
		"north" : __DIR__"room1",
	]));
	set("objects", ([
		__DIR__"npc/zhuangding": 4,
	]));
	setup();
}
int valid_leave(object me, string dir)
{
	object oba;
	object player;
	object *obs = all_inventory();
	
	oba = present("zhuang ding", environment(me));
	
	foreach(player in obs) {
		if (userp(player))
		{
			if (oba && (dir == "north")) {
				oba->kill_ob(player);
				player->kill_ob(oba);
				return notify_fail(oba->name()+"����������������������ı��ӵ�����Ȼ�ô���������\n");
			}
		}
	}
	return ::valid_leave(me, dir);
}
#include "/d/fuben/room_fb.h"