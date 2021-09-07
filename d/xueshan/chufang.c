//      chufang.c ����
inherit ROOM;
void init();
int work();

void create()
{
	set("short", "����");
	set("long", @LONG
������ѩɽ�µĳ�����������ɮ�˿����ڴ˴��ӡ���
����Ŀ��λ����һ�����ӡ�
LONG );
	set("item_desc", ([
		"�����ӡ�" : "�����������ӹ�������(work)һ�θ���ʮ����\n"
		ZJOBACTS2"��:work\n",
	]));
	set("no_fight",1);
	set("no_steal",1);
	set("exits", ([
		"south" : __DIR__"xiaoyuan",
	]));

	set("objects", ([
		__DIR__"obj/cha" : 2 + random(2),
		__DIR__"obj/nailao" : 2 + random(2),
	]));

	set("resource/water", 1);

	set_temp("times" , 5);
	setup();
}

void init()
{
	add_action("do_work","work");
}

int do_work()
{
	object me = this_player();
	object ob;

	if (me->is_busy())
		return notify_fail("����æ���أ�\n");
	if (query_temp("times")==0)
		return notify_fail("����Ļ�����ˣ����������ɣ�\n");
	if(me->query("qi")<20)
		return notify_fail("�����̫���������ܹ�����\n");
	me->add("qi",-20);
	message_vision("$N����һЩ�ӻ�۵ù�Ǻ�������õ���10�����ӵĹ�Ǯ��\n" , me);
	add_temp("times",-1);

	ob=new("/clone/money/silver");
	ob->set_amount(10);
	ob->move(me);
	me->start_busy(6);
	return 1;
}

void reset()
{
	::reset();
	set_temp("times", 5);
}

