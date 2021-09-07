// xiyu-tiezheng.c ����������

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int valid_enable(string usage) { return usage == "guzheng-jifa"; }

int valid_learn(object me)
{
	if (me->query_skill("guzheng-jifa", 1) < 100)
		return notify_fail("��Ĺ��ݼ���ˮƽ������������������˵�ɣ�\n");

	if (me->query_skill("guzheng-jifa", 1) < me->query_skill("xiyu-tiezheng", 1))
		return notify_fail("��Ĺ��ݼ���ˮƽ���ޣ��޷����������������������\n");

	return 1;
}

int practice_skill(object me)
{
	object ob;

	if (! objectp(ob = me->query_temp("handing")) ||
	    ! ob->valid_as_zheng())
		return notify_fail("���ó�����������ô��ϰ��\n");

	if ((int)me->query("jing") < 80)
		return notify_fail("��ľ��񲻹��ã�û����ϰ�ˡ�\n");

	if ((int)me->query("qi") < 30)
		return notify_fail("������ʵ����̫ƣ���ˡ�\n");

	me->receive_damage("jing", 45);
	me->receive_damage("qi", 20);

	return 1;
}

void do_effect(object me)
{
	object *obs;
	int lvl;
	int i;
	int damage;

	lvl = me->query_skill("guzheng-jifa", 1) / 2 +
	      me->query_skill("xiyu-tiezheng", 1);

	if (environment(me)->query("no_fight") || lvl < 150)
		return;

	lvl = lvl / 5 + me->query_skill("force");
	lvl /= 2;

	// special effort
	obs = all_inventory(environment(me));
	for (i = 0; i < sizeof(obs); i++)
	{
		if (! obs[i]->is_character() || obs[i] == me || ! living(obs[i]))
			continue;

		if (me->query_skill("xiyu-tiezheng") * 2 / 3 <
		    obs[i]->query_skill("xiyu-tiezheng"))
			continue;

		if (lvl + random(lvl) < obs[i]->query_skill("force"))
		{
			tell_object(obs[i], HIM "���������в���΢΢һ�����������������а���֮����"NOR"\n");
			continue;
		}

		damage = me->query("max_neili") - obs[i]->query("max_neili");
		if (damage < 500)
		{
			tell_object(obs[i], HIB "���Ȼ����һ�����ܣ���æ����һ�����������ѹ�����"NOR"\n");
			continue;
		}

		damage /= 10;
		me->want_kill(obs[i]);
		me->fight_ob(obs[i]);
		obs[i]->kill_ob(me);
		obs[i]->receive_damage("jing", damage, me);
		obs[i]->receive_wound("jing", damage / 3, me);
		
		tell_object(obs[i], HIB "�������������Ǻ������������ɵ��ĸ�����..."NOR"\n");
	}
}
