inherit ROOM;

void create()
{
	set("short", "���ռ�թ");
	set("long", @LONG
������һ��Сʯ�ݣ���������ʲô�ر���������һλ������Ȼ��
�󺺣��������㿴���Ӵ˷���������޵�ת��������������Ը�Ϊ�����ս�թ����
LONG );
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/hua" : 1,
	]));
	set("exits", ([
		"east"  : __DIR__"entry",
		"out"   : __DIR__"yanluodian",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	object ob;
	if (! objectp(ob = present("hua tiegan", this_object())))
	{
		ob = new(__DIR__"npc/hua");
		ob->move(this_object());
	}

	ob->check_leave(me, dir);
	return ::valid_leave(me, dir);
}
