// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����һ�������ǰ�������������ˡ�
LONG
	);
	set("exits", ([
		"north" : __DIR__"room0",
	]));
	setup();
}
int valid_leave(object me, string dir)
{
	string fb_id;
	
	if (userp(me) && dir == "out") {
		me->delete_temp("zxt_again");
		if (fb_id = me->query_temp("fuben_path"))
			FUBEN_D->des_fuben(fb_id, 1);
	}
	return ::valid_leave(me, dir);
}

