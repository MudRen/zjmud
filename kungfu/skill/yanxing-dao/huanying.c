// huanying.c  ���е��������λ�Ӱ��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"��Ӱ"; }

int perform(object me, object target)
{
	int damage;
	string msg;
	object weapon;
	int i;

	if (! target) target = offensive_target(me);
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("����û����ôʹ�����λ�Ӱ����\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����λ�Ӱ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("yanxing-dao", 1) < 60 )
		return notify_fail("�����е���������죬ʹ���������λ�Ӱ����\n");

	if ((int)me->query_skill("force") < 120 )
		return notify_fail(RED"���ڹ���򲻹����޷�ʩչ�����λ�Ӱ����"NOR"\n");

	if ((int)me->query("neili") < 80)
		return notify_fail(HIC"����������������û�ܽ������λ�Ӱ��ʹ�꣡"NOR"\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "���һ����ȫ���Ĵ��ζ���$n"
	      HIC "ֻ����$N" HIC "����������Ӱ�����쵶"
	      HIC "��ϯ�������"NOR"\n";
	message_combatd(msg, me, target);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add("neili", -80);
	me->start_busy(1 + random(4));
	return 1;
}
