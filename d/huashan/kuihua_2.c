inherit ROOM;

void create()
{
	set("short", "ɽ��");
	set("long", @LONG
��������Ů��ɽ�µĶ���ɽ�£���ǰ�ߵ�ɽ�±Ƚ�Զ��������Ҫ����
ȥ�������ס�
LONG );
	set("outdoors", "huashan");
	setup();
}

void init()
{
	add_action("do_climb","climb");
}

int do_climb()
{
	object me;
	int n = this_player()->query_skill("dodge", 1);

	me = this_player();

	message_vision("$N������һ��������������ɽ����������\n", this_player());
	if (n > 100)
	{
		message_vision("$N���˰��죬����ϥ�Ƕ��ѱ���ʯ�����Ѫ���죬��������������\n", this_player());
		this_player()->move(__DIR__"kuihua_1");
	}
	else
	{
		message_vision("$N����һ�ᣬһ�������񣬵�����ȥ��\n", this_player());
		me->unconcious(); 
	}
	return 1;
}
