// sroad9.c
inherit ROOM;
void create()
{
	set("short", "��ѩɽɽ��");
	set("long", @LONG
ɽ�����ػ�ѩ�����ܶ����ͱڡ�ֻ������һ�����ڣ������ƺ���
��ɽ����
LONG );
	set("exits", ([
		"northdown" : __DIR__"wangyougu",
		"east"      : __DIR__"shandong2",
	]));
	set("objects", ([
		CLASS_D("xuedao") + "/shengdi" : 1,
	]));
	set("outdoors", "xuedao");
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (dir == "east" &&
	    objectp(guarder = present("sheng di", this_object())))
	{
		return guarder->permit_pass(me, dir);
	}

	return ::valid_leave(me, dir);
}

