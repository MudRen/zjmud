inherit ROOM;

void create()
{
	set("short", "�ĺ�����");
	set("long", @LONG
������һ��Сé�ݣ�����һλ��̹��¶�飬������ơ��������
�ǣ������������ֻ������һ��ͷ���Ӵ˷���������޵�ת��������������Ը�Ϊ���ĺ���������
LONG );
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/li" : 1,
	]));
	set("exits", ([
		"south"  : __DIR__"entry",
		"out"   : __DIR__"yanluodian",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	object ob;
	if (! objectp(ob = present("li zicheng", this_object())))
	{
		ob = new(__DIR__"npc/li");
		ob->move(this_object());
	}

	ob->check_leave(me, dir);
	return ::valid_leave(me, dir);
}
