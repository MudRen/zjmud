inherit ROOM;

void create()
{
	set("short", "����㳡");
	set("long", @LONG
�����ǳ��е������ģ�һ���ܿ����Ĺ㳡��������һ�ô��������ݴ�����ǧ������䣬���������е���ʷ��֤�����ɵײ���һ���ܴ�
��������
LONG );
	set("no_sleep_room",1);
	set("outdoors", "city");
	set("item_desc", ([
		"��������" : "����һ���ڲ����еĴ󶴣����治֪����Щʲô�Ź֡�\n"
		ZJOBACTS2"�궴:enter dong\n",
	]));

	set("action_list", ([
		HIW"ʥ������"NOR : "shake_shu",
	]));

	set("exits", ([
		"northeast" : __DIR__"shengxiantang",
		"northwest" : __DIR__"banghui",
		"southeast" : __DIR__"heishi",
		"southwest" : __DIR__"lajichang",
		"east" : __DIR__"dongdajie1",
		"south" : __DIR__"nandajie1",
		"west" : __DIR__"xidajie1",
		"north" : __DIR__"beidajie1",

	]));

	set("objects", ([
		__DIR__"npc/liapo" : 1,
	     
	]));

	setup();
}

void init()
{
	add_action("do_enter", "enter");
	add_action("do_shake", "shake_shu");
}

int do_shake(string arg)
{
	string str;
	object ob,me,box;
	int last;

	me = this_player();

	if(!arg)
	{
		str = ZJOBLONG"����һ��һֱ����Ц�ݶ����е���ֵ����ˣ�ÿ��ʥ���ڶ���������Ӱ\n";
		str += ZJOBACTS2"����:shake_shu ok\n",
		write(str);
		return 1;
	}
	if(localtime(time())[3]<24 || localtime(time())[3]>25 || localtime(time())[4]<11)
		return notify_fail(HIY"ʥ���ڻ�û���ˣ���ô�����ðɣ�����ǰף��ʥ������ (^_^) ��"NOR"\n");

	last = me->query("zjvip/last_shake_shu");
	if(localtime(time())[3] == localtime(last)[3])
		return notify_fail("������Ѿ�Ҫ�������ˣ���Ҫ̫̰��Ŷ��\n");

	me->set("zjvip/last_shake_shu",time());

	box = new("/clone/gift/gift_shengdan");
	tell_object(me,"������ֶ�ʥ������Ц��Ц��\n");
	tell_object(me,"��õ���"+box->short()+"��\n");
	ob = new("/clone/gift/tianxiang1");
	tell_object(me,"��õ���"+ob->short()+"��\n");
	log_ufile(me,"shengdan_box","��ʥ����������õ���"+box->short()+"\n");
	box->move(me);
	ob->move(me);

	return 1;
}

int do_enter(string arg)
{
	object me;
	me = this_player();

	if (! arg || arg == "")
		return 0;

	if (arg == "dong")
	{
		if (me->is_busy())
			return notify_fail("��Ķ�����û����ɣ������ƶ���\n");

		message("vision",
			me->name() + "һ�������������˽�ȥ��\n",
			environment(me), ({me}) );
		me->move("/d/gaibang/inhole");
		message("vision",
			me->name() + "�Ӷ������˽�����\n",
			environment(me), ({me}) );
		return 1;
	}
}       
