// fugu.c ����������-���ǲ���

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���ǲ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon"))
		return notify_fail("�㲻�ǿ��֣�����ʹ�ø��ǲ���\n");

	if ((int)me->query_skill("jinshe-zhang", 1) < 100)
		return notify_fail("��Ľ����Ʋ�����죬����ʹ�ø��ǲ���\n");

	if ((int)me->query("neili", 1) < 300)
		return notify_fail("����������̫��������ʹ�ø��ǲ���\n");

	if (me->query_skill_mapped("strike") != "jinshe-zhang")
		return notify_fail("������û�м��������Ʒ����޷�ʹ�ø��ǲ���\n");

	if (me->query_skill_prepared("strike") != "jinshe-zhang")
		return notify_fail("������û��׼��ʹ�ý����Ʒ����޷�ʩչ���ǲ���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "���һ���������������һ̽��ס$n"
	      HIC "������������ɱ�֣�"NOR"\n";
	message_combatd(msg, me, target);

	if (target->is_busy() ||
	    random(me->query_skill("strike")) > target->query_skill("parry") / 2)
	{
		if (! target->is_busy())
			target->start_busy(1);

		COMBAT_D->do_attack(me, target, 0, 0);
		COMBAT_D->do_attack(me, target, 0, 0);
		COMBAT_D->do_attack(me, target, 0, 0);

		me->add("neili", -150);
		me->start_busy(2);
		msg = HIR "���$n" HIR "��$N" HIR "���������ƣ�"
		      "�ڡ����ǲ����£�һʱ��Ȼ�޷����֣�"NOR"\n";
	}
	else
	{
		me->start_busy(2);
		msg = CYN "����$p" CYN "ʶ����$P"
		      CYN "��һ�У�����һ�ͣ������˶Է����ơ�"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
