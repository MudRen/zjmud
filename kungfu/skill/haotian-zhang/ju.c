// ju.c �����۶�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"�۶�"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����۶�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("haotian-zhang", 1) < 60)
		return notify_fail("�������Ʋ�����죬����ʹ�������۶���\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���Ϊ����������ʩչ�����۶���\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("�����������������޷�ʹ�������۶���\n");

	if (me->query_skill_mapped("strike") != "haotian-zhang")
		return notify_fail("������û�м�������Ʒ����޷�ʹ�������۶���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "���һ����������$n" HIC "���ϣ�˫��"
	      "ͬʱ����������һ�С������۶�����"NOR"\n";

	if (random(me->query_skill("force")) > target->query_skill("force") / 2)
	{
		me->start_busy(2);
		me->add("neili", -110);
		damage = me->query_skill("strike");
		damage = damage / 3 + random(damage / 3);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
					   HIR "���$p" HIR "��$P" HIR "��������"
					   "�㣬��æ���ˣ������$P" HIR "һ�ƻ�"
					   "�˸����У���Ѫ��ֹ����"NOR"\n");
	} else
	{
		me->start_busy(3);
		me->add("neili", -60);
		msg += CYN "����$p" CYN "ʶ����$P"
		       CYN "��һ�У�ббһԾ�ܿ���"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
