inherit ROOM;

void create()
{
	set("short", "中央广场");
	set("long", @LONG
这里是城市的正中心，一个很宽阔的广场。中央有一棵大榕树，据传已有千年的树龄，是这座城市的历史见证。树干底部有一个很大
的树洞。
LONG );
	set("no_sleep_room",1);
	set("outdoors", "city");
	set("item_desc", ([
		"【树洞】" : "这是一个黑不溜湫的大洞，里面不知道有些什么古怪。\n"
		ZJOBACTS2"钻洞:enter dong\n",
	]));

	set("action_list", ([
		HIW"圣诞老人"NOR : "shake_shu",
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
		str = ZJOBLONG"这是一个一直带着笑容而有有点奇怪的老人，每到圣诞节都有它的身影\n";
		str += ZJOBACTS2"礼物:shake_shu ok\n",
		write(str);
		return 1;
	}
	if(localtime(time())[3]<24 || localtime(time())[3]>25 || localtime(time())[4]<11)
		return notify_fail(HIY"圣诞节还没来了，这么急？好吧，先提前祝你圣诞快乐 (^_^) ！"NOR"\n");

	last = me->query("zjvip/last_shake_shu");
	if(localtime(time())[3] == localtime(last)[3])
		return notify_fail("你今天已经要过礼物了，不要太贪心哦！\n");

	me->set("zjvip/last_shake_shu",time());

	box = new("/clone/gift/gift_shengdan");
	tell_object(me,"你伸出手对圣诞老人笑了笑！\n");
	tell_object(me,"你得到了"+box->short()+"！\n");
	ob = new("/clone/gift/tianxiang1");
	tell_object(me,"你得到了"+ob->short()+"！\n");
	log_ufile(me,"shengdan_box","从圣诞老人那里得到了"+box->short()+"\n");
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
			return notify_fail("你的动作还没有完成，不能移动。\n");

		message("vision",
			me->name() + "一弯腰往洞里走了进去。\n",
			environment(me), ({me}) );
		me->move("/d/gaibang/inhole");
		message("vision",
			me->name() + "从洞里走了进来。\n",
			environment(me), ({me}) );
		return 1;
	}
}       
