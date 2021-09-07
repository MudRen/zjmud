// huayu.c

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }

int perform(object me, object target)
{
	int skill, i;
	int n;
	int my_exp, ob_exp;
	string pmsg;
	string msg;
	object weapon;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���컨��ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("handing")) ||
	    (string)weapon->query("skill_type") != "throwing")
		return notify_fail("���������в�û�����Ű�����\n");

	if (weapon->query_amount() < 10)
		return notify_fail("����Ҫ��ʮö���������ʩչ���컨�ꡣ\n");

	if ((skill = me->query_skill("feixing-shu", 1)) < 100)
		return notify_fail("��ķ�����������죬����ʹ�����컨�ꡣ\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹�������ʹ�����컨�ꡣ\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("�����������ˡ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	me->add("neili", -100);
	weapon->add_amount(-10);

	msg= HIG "ֻ��һ�ɾ����$N" HIG "���Ҳ෢����$N" HIG
	     "���е�" + weapon->name() + HIG "���������$n"
	     HIG "���ֹ�ȥ��\n";

	me->start_busy(2);
	my_exp = me->query_skill("throwing");
	ob_exp = target->query_skill("dodge");
	if (my_exp / 2 + random(my_exp) > ob_exp)
	{
		n = 1 + random(2);
		if (random(my_exp) > ob_exp) n += 1 + random(2);
		if (random(my_exp / 2) > ob_exp) n += 1 + random(2);
		if (random(my_exp / 4) > ob_exp) n += 1 + random(2);
		msg += "���$p" HIG "��Ӧ����������$P" HIG +
		       chinese_number(n) + weapon->query("base_unit") +
		       weapon->name() + HIG "��"NOR"\n";
		target->receive_wound("qi", skill / 3 + random(skill / 3), me);
		while (n--)
		{
			COMBAT_D->clear_ahinfo();
			weapon->hit_ob(me, target,
				       me->query("jiali") + 100 + n * 10);
		}
		if (stringp(pmsg = COMBAT_D->query_ahinfo()))
			msg += pmsg;
		message_combatd(msg, me, target);
	} else
	{
		msg += "����$p" HIG "�����$P" HIG "����������" +
		       weapon->name() + HIG "��"NOR"\n";
		message_combatd(msg, me, target);
	}

	me->reset_action();
	return 1;
}
