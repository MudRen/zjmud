// /guanwai/chuanchang.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����ǹ��򴬳���������λ�ڹ����ƽԭ�в���һ�����ϵ�С�򣬴���
�����ϡ������������Ը�ǽ���������ڼ��ء��������ɻ���������գ��˱�
�ұ�����Ҫ�ء��ɻ����ڶ���ʱ�����ͨ�У����ﻯ����ֻ���Ҵ��Ұ�æ�ˡ�
LONG );
	set("exits", ([
		"south"  : __DIR__"xuedi3",
		"east"   : __DIR__"bingmian",
	]));
	set("outdoors", "guanwai");
	set("action_list",([
		"����":"give 1 silver to chuan fu",
		"һέ�ɽ�":"cross",
	]));
	setup();
}

void init()
{
	add_action("do_cross", "cross");
}

int do_cross()
{
	object me;

	switch (NATURE_D->query_month())
	{
	case 11: case 12: case 1: case 2: case 3: case 4:
		return notify_fail("������ź���һ��������߹�ȥ�������ˣ�\n");
	}

	me = this_player();
	if (me->is_fighting())
	{
		tell_object(me, "��ôҲ���ȰѼܴ������߰ɡ�\n");
		return 1;
	}

	if (me->query_skill("dodge") < 100)
	{
		tell_object(me, random(2) ? "����ú���̫��û��ʮ��İ���Ծ��ȥ��\n"
					  : "�㿴�ű��ڲ�Ϣ�İ׺ӣ������е���ţ�����������\n");
		return 1;
	}

	if (me->query("neili") < 100)
	{
		tell_object(me, "�������������������Ϣһ����˵�ɡ�\n");
		return 1;
	}

	me->add("neili", -50);
	message_vision("$N����һ�Σ���ƮƮ������׺ӣ�ֻ��$P�����˻�������Զȥ��\n", me);
	tell_object(me, "��˳���ĵ����˱˰���\n");
	me->move(__DIR__"damenkan");
	return 1;
}

int valid_leave(object me, string dir)
{
	object obj;
	int i;

	if (dir == "east")
	{
		switch (NATURE_D->query_month())
		{
		case 11: case 12: case 1: case 2: case 3: case 4:
			message_vision("$N������ᶳ����׳���Ӳȱ�������\n\n", me);
			if (random(me->query_dex()) + me->query_dex() * 2 / 3 < 20)
			{
				me->receive_wound("qi", 20);
				me->receive_damage("qi", 10);
				message_vision("$Nֻ���ý���һ����ȫ���ڿ�"
					       "���𣬽��ʵʵ��ˤ���˱����ϣ�\n", me);
			}
			return 1;
		default:
			if (! present("chuan fu", this_object()))
			{
				obj = new(__DIR__"npc/chuanfu");
				obj -> move(environment(me));
				message_vision("�������߳�һ�����򣬵����ۿ���$N��\n", me);
			}
			else
				message_vision("�������Ա����۵���$N����\n", me);
			write("���滯�����㻹�ǳ˴��ɣ�\n");
			return -1;
		}
	}
	return ::valid_leave(me, dir);
}
