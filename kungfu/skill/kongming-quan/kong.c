// kong.c ����ȭ�տ���Ҳ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "�տ�"ZJBR"��Ҳ"; }
string *pfm_type() { return ({ "unarmed", }); }

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�տ���Ҳֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ�á��տ���Ҳ����\n");		
		
	if ((int)me->query_skill("kongming-quan", 1) < 125)
		return notify_fail("��Ŀ���ȭ������죬����ʹ�á��տ���Ҳ����\n");
				
	if ((int)me->query("neili", 1) < 150)
		return notify_fail("����������̫��������ʹ�á��տ���Ҳ����\n");

	if (me->query_skill_mapped("unarmed") != "kongming-quan")
		return notify_fail("��û�м�������ȭ������ʹ�á��տ���Ҳ����");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = CYN "$N" CYN "ʹ������ȭ���տ���Ҳ����ȭ���仯Ī�⣬��$n"
	      CYN "һʱ���Բ�׽��"NOR"\n";
	me->add("neili", -80);

	ap = me->query_skill("unarmed") + me->query_skill("force");
	dp = target->query_skill("parry") + target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		me->start_busy(3);
		
		damage = ap / 2 + random(ap / 2);
		
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
					   damage, 48,
					   CYN "$nʵ���޷�����$N" CYN
					   "��һȭ�ľ�������$P"
					   CYN "��һȭ���ô��У�\n"
					   ":����@?");
	} else 
	{
		me->start_busy(2);
		msg += CYN "����$p" CYN "ʶ����$P"
		       CYN "��ȭ���еı仯������Ӧ�ԣ���û�гԿ���"NOR"\n";
	}
	message_combatd(msg, me, target);
	return 1;
}
