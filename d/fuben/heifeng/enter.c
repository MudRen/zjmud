// Room: banfang.c

inherit ROOM;

void create()
{
	set("short", "�ڷ�կ");
	set("long", @LONG
������һ�����صü���ɽկ��������֮�䴳�˽�����
LONG
	);
	set("exits", ([
		"north" : __DIR__"room1",
	]));
	setup();
}
int valid_leave(object me, string dir)
{
	string fb_id;
	
	if (userp(me) && dir == "out") {
		if (fb_id = me->query_temp("fuben_path"))
			FUBEN_D->des_fuben(fb_id, 1);
                  //return 0;
	}
	return ::valid_leave(me, dir);
}

