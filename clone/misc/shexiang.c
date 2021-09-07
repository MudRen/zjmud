// Yanwu.c ����

#include <command.h>
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIM "�����" NOR, ({ "shexiang fen" }) );
	set_weight(80);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��ɢ���������ҩ�ۡ���������(apply)��ɢ����ζ��������ߡ�\n");
		set("unit", "��");
		set("value", 150000);
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
	int dex;

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
			if (sc > 500000) sc = 500000;
			//if (sc / 4 + random(sc) > 200000)
			if (random(sc) > 250000)
			{
				message_vision("\n$N�ͳ�����۾�������һ����Ȼ��$n"
					       "���һ��������Ҳ������" +
					       RANK_D->query_self(obs[i]) +
					       "���߽����ж����꣬���Ȼ���������ְ�Ϸ����\n"
					       "˵��ֻ��$n����һ�ӣ���$N�����ȫ���𿪡�\n",
					       me, obs[i]);
				destruct(this_object());
				return 1;
			}
		}
	}

	me->set_temp("no_follow",1);
	tell_room(environment(me), HIM "\n��Ȼһ�����㴫��������"
				   "�����ķΣ���̩�ޱȣ�����һʱ��ֻ��˯����"NOR"\n");

	me->set_temp("success_flee", "������������ҳɹ��������ˡ�\n");
	dex = me->query("dex");
	me->set("dex", dex * 5);
	GO_CMD->do_flee(me);
	me->set("dex", dex);
	destruct(this_object());
	return 1;
}

int do_apply(string arg)
{
	if (! arg || ! id(arg))
		return notify_fail("��Ҫ��ʲô��\n");

	return apply_for_wimpy(this_player());
}
