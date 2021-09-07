// Yanwu.c ����

#include <command.h>
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM "����" NOR, ({ "yanwu dan", "yanwu", "dan" }) );
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ�����Ƶ���������������(apply)��������ң��û����ߡ�\n");
		set("unit", "��");
		set("value", 10000);
		set("no_sell", 1);
		set("can_apply_for_wimpy", 1);
	}
	setup();
}

void init()
{
	add_action("do_apply","apply");
}

int apply_for_wimpy(object me)
{
	object *obs;
	int i;
	int sc;

	if (me->is_busy())
		return notify_fail("����������æ���ء�\n");

	me->clean_up_enemy();
	if (me->is_fighting())
	{
		obs = me->query_enemy();
		for (i = 0; i < sizeof(obs); i++)
		{
			if (! living(obs[i]))
				continue;
			sc = obs[i]->query("score") -
			     me->query("score");
			if (sc < 0) continue;
			if (sc > 300000) sc = 300000;
			if (sc / 4 + random(sc) > 100000)
			{
				message_vision("\n$N�ͳ��������������ӣ�Ȼ��$n"
					       "���һ��������Ҳ������" +
					       RANK_D->query_self(obs[i]) +
					       "���߽����ж����꣬���Ȼ���������ְ�Ϸ����\n"
					       "˵��ֻ��$nһ�Ž�$N���ڵ��ϵ������ߵ�һ�ԡ�\n",
					       me, obs[i]);
				destruct(this_object());
				return 1;
			}
		}
	}

	me->set_temp("no_follow",1);
	tell_room(environment(me), HIM "\n����ͻȻ�ڳ�һ���Һ�ɫ��"
				   "�������ʲôҲ������������"
				   "����֮�С�"NOR"\n");

	me->set_temp("success_flee", "����Ż��ҳɹ��������ˡ�\n");
	GO_CMD->do_flee(me);
	destruct(this_object());
	return 1;
}

int do_apply(string arg)
{
	if (! arg || ! id(arg))
		return notify_fail("��Ҫ��ʲô��\n");

	return apply_for_wimpy(this_player());
}
