// zheng.c

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
		return notify_fail("��ֻ����ս���жԶ��������롣\n");

	if (! objectp(weapon = me->query_temp("handing")) ||
	    (string)weapon->query("skill_type") != "throwing")
		return notify_fail("���������в�û�����Ű�����\n");

	if (weapon->query_amount() < 20)
		return notify_fail("����Ҫ�ж�ʮö���������ʩչ������롣\n");

	if ((skill = me->query_skill("mantianhuayu-zhen", 1)) < 100)
		return notify_fail("������컨�������벻����죬����֪��ô�������롣\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹����޷��������롣\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("�����������ˡ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	me->add("neili", -100);
	weapon->add_amount(-10);

	msg= HIY "$N" HIY "����Ծ������һ�ţ���ʱ����һƬ��â��"
	     "����" + weapon->name() + HIY "�缱�籩��һ��ֱ��$n"
	     HIY "��ȥ��"NOR"\n";

	me->start_busy(2);
	my_exp = me->query_skill("throwing");
	ob_exp = target->query_skill("dodge");
	if (random(my_exp) > ob_exp)
	{
		n = 1 + random(2);
		if (random(my_exp) > ob_exp) n += 1 + random(2);
		if (random(my_exp / 2) > ob_exp) n += 1 + random(2);
		if (random(my_exp / 4) > ob_exp) n += 1 + random(2);
		msg += HIR "���$p" HIR "һ���Һ���������$P" HIR "������" HIR +
		       chinese_number(n) + weapon->query("base_unit") +
		       weapon->name() + HIR "��"NOR"\n";
		target->receive_wound("qi", skill / 4 + random(skill / 4), me);
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
		msg += HIG "����$p" HIG "���Ӽ��ˣ������$P" HIG "���������" +
		       weapon->name() + HIG "��"NOR"\n";
		message_combatd(msg, me, target);
	}

	me->reset_action();
	return 1;
}

