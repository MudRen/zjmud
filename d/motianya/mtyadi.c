// mtyadi.c �µ�

inherit ROOM;

int do_climb(string arg);

void create()
{
	set("short", "�µ�");
	set("long", @TEXT
�����ǰ��һ����ֱ��ɽ�壬����ǧ�ɣ��嶥����������Լ�ɼ���
ɽ���ͺͺ�ģ����������㴦��ɽ�崹��һ������(lian)����ϸһ����
���������⼣���ƺ�����������(climb)�����¡�
TEXT );
	set("outdoors", "motianya");
	set("exits", ([
		"north" : __DIR__"mtroad",
	]));
	setup();
}

void init()
{
	add_action("do_climb","climb");
}

int do_climb(string arg)
{
	int n;
	object me;

	if (arg != "lian")
	{
		write("��Ҫ��ʲôѽ? \n");
		return 1;
	}

	me = this_player();
	n = me->query_skill("dodge", 1);
	message_vision("$N������һ����������������������������\n", me);
	if (n > 80)
	{
		message_vision("$N���˰��죬����������ȥ��$N���˵�"
			       "Ĩ��Ĩ����\n", me);
		me->move(__DIR__"mtdating");
	} else
	{
		message_vision("$N����һ�ᣬһ��С��ˤ��������\n", me);
		me->receive_damage("qi", 50);
		me->receive_wound("qi", 50);
	}

	return 1;
}
