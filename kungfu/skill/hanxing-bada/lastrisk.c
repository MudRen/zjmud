// hanxing-fada/lastrisk.c

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "��ע"ZJBR"һ��"; }

int perform(object me, object target)
{
	int i, skill;
	string msg;
	object *ob;
	object weapon;
	string pmsg;
	int ap, dp;
	int n;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��עһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("handing")) ||
	    (string)weapon->query("skill_type") != "throwing" ||
	    weapon->query_amount() < 1)
		return notify_fail("�����б������а�����\n");

	if ((skill = me->query_skill("hanxing-bada", 1)) < 60)
		return notify_fail("��ĺ��ǰ˴���Ϊ̫ǳ���޷�ʩչ��עһ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = CYN "$N" CYN "��עһ�����������а�������$n" CYN "��"NOR"\n";
	me->start_busy(2);
	ap = me->query_skill("throwing");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR "���$p" HIR "��$P" HIR "���˸����ֲ�����������ö������"NOR"\n";
		target->receive_wound("qi", skill / 2 + random(skill / 2), me);
		COMBAT_D->clear_ahinfo();
		n = random(weapon->query_amount()) + 1;
		if (n > 5) n = 5;
		while (n--)
			weapon->hit_ob(me, target, me->query("jiali") + 120);

		if (stringp(pmsg = COMBAT_D->query_ahinfo()))
			msg += pmsg;
	} else
	{
		msg += CYN "����$p" CYN "���ݲ��ȵĶ����$P"
		       CYN "�����һ����"NOR"\n";
	}

	message_combatd(msg, me, target);
	destruct(weapon);
	me->reset_action();
	return 1;
}
