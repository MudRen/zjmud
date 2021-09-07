// Room: /d/gaibang/undertre.c 
inherit ROOM; 
	
void create() 
{
	set("short", "������"); 
	set("long", @LONG 
�����ϻ����ײ������ܹ��߻谵����Ӱ�λΣ��ƺ��м����ڰ��Ķ��� 
������ߣ�ͨ������˷���һλ����ؤ�����ֵ��������еĵ��ϡ����� 
�����㷢��ǽ���ϻ��ŷ��ֲڵ�·�߲�ͼ�� 
LONG 
	); 
	set("exits", ([ 
		"up"   : __DIR__"inhole", 
		"down" : __DIR__"chuchang",
		"west" : "/d/city/gbxiaowu"
	]));

	set("direct", ([ 
		"1"    : __DIR__"bjandao1", 
		"2"    : __DIR__"slandao1", 
		"3"    : __DIR__"gwandao1", 
		"4"    : __DIR__"hzandao1", 
		"5"    : __DIR__"qzandao1", 
		"6"    : __DIR__"fzandao1", 
		"7"    : __DIR__"fsandao1", 
		"8"    : __DIR__"wgandao1", 
		"9"    : __DIR__"xsandao1", 
		"a"    : __DIR__"xxandao1", 
		"b"    : __DIR__"lzandao1",
		"c"    : __DIR__"dlandao1",
		"d"    : __DIR__"cdandao1",
		"e"    : __DIR__"hsandao1",
		"f"    : __DIR__"wdandao1", 
	])); 
 
	set("item_desc", ([ "���ܵ���" :
		"��ѡ����Ҫȥ�ĵط���\n"
		ZJOBACTS2+ZJMENUF(4,4,7,26)
		"����:goto 1"ZJSEP
		"��ɽ:goto 2"ZJSEP
		"����:goto 3"ZJSEP 
		"����:goto 4"ZJSEP
		"����:goto 5"ZJSEP
		"����:goto 6"ZJSEP
		"��ɽ:goto 7"ZJSEP
		"�书:goto 8"ZJSEP
		"ѩɽ:goto 9"ZJSEP
		"����:goto a"ZJSEP
		"����:goto b"ZJSEP
		"����:goto c"ZJSEP
		"�ɶ�:goto d"ZJSEP
		"��ɽ:goto e"ZJSEP
		"�䵱:goto f\n"
	])); 
       
	set("objects", ([ 
		CLASS_D("gaibang") + "/liang" : 1,
		CLASS_D("gaibang") + "/ma-jw" : 1, 
	])); 
       
	set("no_fight", 1); 
       
	setup(); 
} 

void init()
{
	add_action("do_goto", "goto");
}

int do_goto(string arg)
{
	string dest;
	object me;

	if (! arg)
		return notify_fail("��Ҫȥ���\n");

	me = this_player();

	if (undefinedp(dest = query("direct/" + arg)))
		return notify_fail("��Ҫȥ���\n");

	if (me->is_busy())
	{
		write("������æ���أ��Ȼ����˵�ɡ�\n");
		return 1;
	}

	message_vision("$N���ܹ۲���һ��������˸�����ƮȻ��ȥ��\n", me);
	me->move(dest);
	me->start_busy(1);
	return 1;
}

int valid_leave(object me, string dir) 
{
	object guarder;

	if (objectp(guarder = present("liang zhanglao", this_object())) && 
	    living(guarder) && dir != "up")
		return guarder->permit_pass(me, dir);

	return ::valid_leave(me, dir); 
}
