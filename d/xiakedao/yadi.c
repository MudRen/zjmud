// yadi.c �µ�

inherit ROOM;

int do_climb(string arg);
int do_swim(string arg);
int do_push(string arg);

void create()
{
	set("short", "�µ�");
	set("long", @LONG
��������¹ȵ����ˣ�������������һ����Ȼ�ĺ�������������
���ף�����ȫ��ˮ(water)����ʱ�м���������С���������ι�����
�沢�����Գ��ڡ�
LONG );
	set("item_desc",([
		"��ˮ̶��" : "���̱��̵�ˮ����������ҫ���������ˣ��㲻������Ӿ��(swim)��\n"
		ZJOBACTS2"��Ӿ:swim water\n",
	]));
	setup();
}

void init()
{
	add_action("do_climb","climb");
	add_action("do_push","push");
	add_action("do_swim","swim");
}

int do_push(string arg)
{
	int n;
	object me;

	me = this_player();
	n = me->query("neili");
	if (! arg || arg != "men")
	{
		write("������ʲôѽ? \n");
		return 1;
	}

	if (! me->query_temp("yadi_swim"))
	{
		write("������ʲôѽ? \n");
		return 1;
	}

	me->delete_temp("yadi_swim");
	message_vision("$N��������һ����������ץסʯ�ŵ�һ�ࡣ\n", me);
	if (n > 150)
	{
		message_vision("ֻ��$Nһ�˵�������˫��һʹ����ʯ�ž������Ŀ��ˡ�\n", me);
		set("exits/west",__DIR__"shidong9");
		me->add("neili", - 150);
		remove_call_out("close");
		call_out("close", 5, this_object());
	} else
	{
		message_vision("$Nʹ����ȫ�������ʯ��ȴ��˿û����\n", me);
		me->set("neili", 0);
	}

	return 1;
}

void close(object room)
{
	message("vision","ʯ���Զ��ĺ����ˡ�\n", room);
	room->delete("exits/west");
}

int do_swim(string arg)
{
	object me;

	me = this_player();

	if (! arg || arg != "water")
	{
		write("������ʲô���ڵ�����Ӿ��\n");
		return 1;
	}

	me->set_temp("yadi_swim", 1);
	message_vision("$N������һ����������������������\n", me);
	if (random(20) >10)
	{
		tell_object(me,"���������ţ�ͻȻ������һ��ʯ��(men)��Ҳ�����ܽ���"ZJURL("cmds:push men")+ZJSIZE(15)+"��"NOR"(push)����\n");
		me->receive_damage("qi", 15);
		me->receive_wound("qi", 10);
	} else
	{
		tell_object(me,"���������ţ�ͻȻ������һ������(suo)���������˹��������������������⣬���ܾ�������"ZJURL("cmds:push men")+ZJSIZE(15)+"��"NOR"������(climb)��\n");
		me->receive_damage("qi", 10);
		me->receive_wound("qi", 10);
	}
	return 1;
}

int do_climb(string arg)
{
	int n;
	object me;

	if (! arg || arg != "suo")
	{
		write("��Ҫ��ʲôѽ? \n");
		return 1;
	}

	me = this_player();
	n = me->query_skill("dodge", 1);

	message_vision("$N������һ����������������������������\n", me);
	if (n >= 120)
	{
		message_vision("$N���˰��죬��������������$N��������ǰ˫�ƺ�ʮ����л���档\n", me);
		me->move(__DIR__"pubu");
	} else
	{
		message_vision("$N����һ�ᣬ̫���ˣ���С�Ļ�������������û�취�ˣ������ɣ�\n", me);
		me->receive_damage("qi", 15);
		me->receive_wound("qi", 10);
	}
	return 1;
}
