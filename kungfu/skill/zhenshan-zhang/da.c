#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "��ɽ"ZJBR"��ţ"; }

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ɽ��ţֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ�ø�ɽ��ţ��\n");	 
		
	if ((int)me->query_skill("zhenshan-zhang", 1) < 60)
		return notify_fail("�����ɽ�Ʋ�����죬����ʹ�ø�ɽ��ţ��\n");

	if (me->query("max_neili") < 500)
		return notify_fail("����ڹ���Ϊ���㣬�޷�ʩչ��ɽ��ţ��\n");

	if (me->query("neili") < 150)
		return notify_fail("����������̫�����޷�ʩչ��ɽ��ţ��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = WHT "$N" WHT "�Ŷ���������һ������ʹ����ɽ��ţ��˫�ƶ�׼$n"
	      WHT "ƽƽ�Ƴ���"NOR"\n";
	me->add("neili", -100);

	ap = me->query_skill("force");
	dp = target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		me->start_busy(3);
		
		damage = ap / 2 + random(ap / 2);
		
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
					   damage, 35,
					   HIR "$n" HIR "������æ���һ�ݣ����ֻ��"
					   "�ؿ�һ�𣬶�ʱ����������ԭ��$N" HIR 
					   "���ھ����ˣ�\n"
					   ":����@?");
	} else 
	{
		me->start_busy(3);
		msg += CYN "����$p" CYN "������$P"
		       CYN "����ͼ����û���ϵ���"NOR"\n";
	}
	message_combatd(msg, me, target);
	return 1;
}
