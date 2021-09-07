#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "������"; }

int perform(object me, object target)
{
	int damage;
	string msg;

	if (! target) target = offensive_target(me);

	if (userp(me) && ! me->query("can_perform/huzhua-shou/juehu"))
		return notify_fail("�����ڻ�����ʹ�á���������һ�У�\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query("shen") < 10000)
		return notify_fail("��������������Զ���ʩչ��������ͻȻ�뵽�˵��������۵�һ����룬���ò���;�����˹�����\n");

	if ((int)me->query_skill("huzhua-shou", 1) < 120)
		return notify_fail("��Ļ�צ�����ֲ�����죬����ʹ�á���������\n");

	if (me->query("neili") < 300)
		return notify_fail("��������������������ʹ�á���������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "���һ��������Ϊצ��˫צ��������צӰ����������һ����$n" HIR
	      "��Ҫ��ץȥ��"NOR"\n";

	if (random(me->query_skill("claw")) > target->query_skill("parry") / 2)
	{
		me->start_busy(3);

		damage = me->query_skill("huzhua-shou", 1);
		damage = damage * 4 + random(damage * 10);
		me->add("shen", -8000);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 25,
					   HIR "���$p" HIR "һ���Һ���û���м�ס$P" HIR
					   "�����Ĺ��ƣ���ץ��Ƥ����룬��Ѫ�ɽ���"NOR"\n");
		me->add("neili", -200);
	} else
	{
		me->start_busy(2);
		me->add("neili", -120);
		me->add("shen", -8000);
		msg += CYN "����$p" CYN "������$N" CYN
		       "����ͼ���㿪������ɱ�š�"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}

