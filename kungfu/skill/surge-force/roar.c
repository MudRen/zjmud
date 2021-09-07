// roar.c ��Ȼ��

#include <ansi.h>

inherit F_CLEAN_UP;

string query_name() { return "��Ȼ��"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	object *ob;
	int i, skill, damage;

	if (me->query_skill("surge-force", 1) < 100)
		return notify_fail("����Ȼһ����̾����������˼�ֻ����\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ�ܹ�������! \n");

	skill = me->query_skill("force");

	me->add("neili", -100);
	me->receive_damage("qi", 10);

	me->start_busy(5);
	message_combatd(HIR "$N" HIR "���쳤Х������һ��һ���ĵ���"
			"ȥ�����˷����������������ԣ�"NOR"\n", me);

	ob = all_inventory(environment(me));
	for (i = 0; i < sizeof(ob); i++)
	{
		if (! ob[i]->is_character() || ob[i] == me)
			continue;

		if (skill / 2 + random(skill / 2) < (int)ob[i]->query("con") * 2)
			continue;

		if (userp(ob[i]) && !ob[i]->die_protect(me))
			continue;

		me->want_kill(ob[i]);
		me->fight_ob(ob[i]);
		ob[i]->kill_ob(me);
		
		damage = skill - ((int)ob[i]->query("max_neili") / 10);
		if (damage > 0)
		{
			ob[i]->receive_damage("jing", damage * 2, me);
			if ((int)ob[i]->query("neili") < skill * 2)
				ob[i]->receive_wound("jing", damage, me);
			tell_object(ob[i], "���������Ӻ��һ��......\n");
		}
	}
	return 1;
}
