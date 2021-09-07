// shan.c

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "�ǹ�"ZJBR"��˸"; }

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
		return notify_fail("�ǹ���˸ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("handing")) ||
	    (string)weapon->query("skill_type") != "throwing")
		return notify_fail("���������в�û�����Ű�������ôʩչ�ǹ���˸��\n");

	if (weapon->query_amount() < 3)
		return notify_fail("����Ҫ����ö���������ʩչ�ǹ���˸��\n");

	if ((skill = me->query_skill("mantian-xing", 1)) < 100)
		return notify_fail("��������ǲ�����죬����ʹ���ǹ���˸��\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�����������ˡ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	me->add("neili", -80);
	weapon->add_amount(-3);

	msg= HIY "$N" HIY "ͻȻ�������һ�����������ڿ���ص�һ˲"
	     "�䣬$n" HIY "��Ȼ���ּ��㺮����˸������Ϯ���Լ���"NOR"\n";

	me->start_busy(2);
	my_exp = me->query_skill("throwing");
	ob_exp = target->query_skill("dodge");
	if (my_exp / 2 + random(my_exp) > ob_exp)
	{
		msg += HIR "���$p" HIR "��Ӧ����������$P" + HIR "һ" +
		       weapon->query("base_unit") + weapon->name() +
		       HIR "��"NOR"\n";
		target->receive_wound("qi", skill / 3 + random(skill / 3), me);
		COMBAT_D->clear_ahinfo();
		weapon->hit_ob(me, target,
			       me->query("jiali") + 120);
		if (stringp(pmsg = COMBAT_D->query_ahinfo()))
			msg += pmsg;
		message_combatd(msg, me, target);
	} else
	{
		msg += HIG "����$p" HIG "���ݲ��ȣ����ɵ�������$P" HIG "������" +
		       weapon->name() + HIG "��"NOR"\n";
		message_combatd(msg, me, target);
	}

	me->reset_action();
	return 1;
}
