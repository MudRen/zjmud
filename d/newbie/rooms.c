// regiser: roome.c
// by Doing

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������һ��С�߷������õķǳ����ʣ�һС����������Ŀ�������
�ϣ���ҡ���ȣ��������֮�����������֮������Ц�����Ŀ�����������Ӵ˷���������޵�ת��������������Ը�Ϊ�������䡿��
LONG );
	set("no_fight", 1);
	set("objects", ([
		__DIR__"npc/wei" : 1,
	]));
	set("exits", ([
		"north"  : __DIR__"entry",
		"out"   : __DIR__"yanluodian",
	]));

	setup();
}

int valid_leave(object me, string dir)
{
	object ob;
	if (! objectp(ob = present("wei xiaobao", this_object())))
	{
		ob = new(__DIR__"npc/wei");
		ob->move(this_object());
	}

	ob->check_leave(me, dir);
	return ::valid_leave(me, dir);
}
