inherit ROOM;
void create()
{
	set("short","����");
	set("long",@LONG
һֻ�󽭴�����Ѱ���Ĵ�������࣬��ʱ���Ѿ���������ʱ���ԴӼ�
��(deck)������ȥ��
LONG);
	set("item_desc", ([
		"deck" : "�󴬵ļװ壬�Ѿ�����ˮ��ʴ�ø��ò�����\n"+ZJOBACTS2"����:jump deck\n",
	]));

	set("no_fight",1);

setup();
}

void init()
{
	add_action("do_jump", "jump");
}

int do_jump(string arg)
{
	object me;
	me = this_player();

	if( !arg || arg=="" )
	return notify_fail("��Ҫ����������\n");

	if( arg=="deck" ) 
	{
		if (me->is_busy() )
		{
			return notify_fail("��Ķ�����û����ɣ������ƶ���\n");
			return 1; 
		}

		message("vision",
			me->name() + "����һԾ���Ӵ󴬵ļװ�������������\n",
			environment(me), ({me}) );
		me->move(__DIR__"shatan");
		message("vision",
			me->name() + "�����˴�����Զ���ĺ������˹�����\n",
			environment(me), ({me}) );
		return 1;
	}
}       

