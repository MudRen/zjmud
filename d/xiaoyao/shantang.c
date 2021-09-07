// shantang.c
inherit ROOM;
void create()
{
	set("short", "�Ƽ�");
	set("long", @LONG
�����������е�һ��СС�ľƼң��ط���Ȼ���󣬵���Ҳ�в�����ң��
�ĵ��ӹ������������ҵ���ζ����Դ�ˣ����ſɿڵķ��ˣ����̲�סҲ
��� (order)һ���ˡ�
LONG );
	set("exits",([
		"north" : __DIR__"xiaodao2",
	]));
	set("resource/water", 1);
	set("ricewater", 5);
	set("item_desc", ([
		"�����ӡ�" : "����ÿ��Ϊ���������ṩ5����ѵķ��ˡ�\n"
		ZJOBACTS2"��һ��:order\n",
	]));
	setup();
}
void init()
{
	add_action("do_order","order");
}

int do_order(string arg)
{
	object me;
	object food;
	object water;
	me=this_player();
	if (arg)  return notify_fail("С�����ܳ�����: ������������û�а���\n");
	if (query("ricewater")>0)
	{
		message_vision("С����������Ӧ��������һ�����ܳ���������һ���׷���һ��ˮ���˸�$N��\n",me);
		food=new(__DIR__"obj/rice");
		water=new(__DIR__"obj/bowl");
		food->move(me);
		water->move(me);
		add("ricewater",-1);
	}
	else 
		message_vision("С������������$NǸ��Ӧ��: �ˣ��ԵĺȵĶ�û�ˡ�\n",me);
	return 1; 
}

int valid_leave(object me,string dir)
{
	me=this_player();
	if(dir=="north" && (present("bowl",this_player()) ||
			    present("rice",this_player()))) 
	     return notify_fail("С��˵�����汧Ǹ����������û�д������\n");
	return ::valid_leave(me,dir);
}

void reset()
{
	::reset();
	set("ricewater", 5);
}

