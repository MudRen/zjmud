// qimen.c  ��Ӣ���ơ�������ת��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"��ת"; }

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ת��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("luoying-shenzhang", 1) < 80)
		return notify_fail("�����Ӣ���Ʋ�����죬����ʹ�á�������ת����\n");

	if ((int)me->query_skill("qimen-wuxing", 1) < 100)
		return notify_fail("����������е��о�����͸�����޷����á�������ת����\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹��ߣ��޷�ʹ�á�������ת����\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("�����������������޷�ʹ�á�������ת����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "ͻȻ���Ī�⣬˫�Ʒ��ɣ�����ʵʵ�Ĺ���$n" HIG "��"NOR"\n";

	ap = (int)me->query_skill("luoying-shenzhang", 1) +
	     (int)me->query_skill("qimen-wuxing", 1) +
	     (int)me->query_skill("force") +
	     (int)me->query("int") * 10;

	dp = (int)target->query_skill("force") +
	     (int)target->query_skill("parry") +
	     (int)target->query_skill("qimen-wuxing", 1) +
	     (int)target->query("int") * 10;

	me->start_busy(1);
	me->add("neili", -150);
	if (ap / 2 + random(ap) > dp)
	{
		damage = (int)me->query_skill("force") + (int)me->query_skill("strike");
		damage = damage / 3;
		damage += random(damage);

		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
					   HIR "$n" HIR "���һ��������ֵ����ˣ�"
					   "������������ƣ�����һ����Ѫ�����Ӽ�"
					   "ת����ͣ��"NOR"\n");
	} else
		msg += HIG "����$p" HIG "������$P" HIG
		       "����ͼ���������򣬱ܿ���$P" HIG "��һ����"NOR"\n";

	message_vision(msg, me, target);
	return 1;
}
