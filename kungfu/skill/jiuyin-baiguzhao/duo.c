// ziwu.c �����׹�צ - ��������צ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "claw", }); }

int perform(object me, object target)
{
	int damage;
	string msg;
	string pmsg;
	string *limbs;
	string  limb;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������צֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ�ö�������צ��\n");
		
	if ((int)me->query_skill("jiuyin-baiguzhao", 1) < 100)
		return notify_fail("��ľ����׹�צ��������죬����ʹ�ö�������צ��\n");

	if (me->query_skill_mapped("claw") != "jiuyin-baiguzhao")
		return notify_fail("��û�м��������׹�צ���޷�ʹ�ö�������צ��\n");

	if ((int)me->query("neili", 1) < 300)
		return notify_fail("����������̫��������ʹ�ö�������צ��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	switch (me->query("character"))
	{
	case "�ĺ�����":
		msg = HIR "$N" HIR "�����Ц����ָ΢΢������ٿ�ĳ�$n"
		      HIR "ͷ��ץ�¡�"NOR"\n";
		break;

	case "���ռ�թ":
		msg = HIR "$N" HIR "��Ц��������ָ΢΢������צ������$n"
		      HIR "ͷ��ץ�¡�"NOR"\n";
		break;

	case "��������":
		msg = HIR "$N" HIR "������������ָ΢΢������צ��������$n"
		      HIR "ͷ��ץ�¡�"NOR"\n";
		break;

	default:
		msg = HIR "$N" HIR "��ָ΢΢������צ���벻�������$n"
		      HIR "ͷ��ץ�¡�"NOR"\n";
		break;
	}

	me->add("neili", -100);

	ap = me->query_skill("claw");
	dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);
	damage = ap + me->query_skill("force");
	damage = damage / 3 + random(damage / 3);
	if (ap / 2 + random(ap) > dp)
	{
		me->start_busy(2);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
					   HIR "$p" HIR "��æ��ͷ��Ȼ��$N" HIR
					   "�������úÿ죬������$p" HIR "��ͷ��"
					   "��ʱ��Ѫ���졣"NOR"\n");
	} else 
	{
		me->add("neili", -150);
		me->start_busy(3);
		msg += HIC "$p" HIC "���в��ã���æ��ͷ������$N"
		       HIC "�ֱ��������죬��Ȼ������Ѹ���ޱȵ�ץ��$p��"NOR"\n";
		dp = target->query_skill("dodge") + target->query_skill("martial-cognize", 1);
		if (ap / 2 + random(ap) > dp)
		{
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
						   HIR "$n" HIR "�����ϵ�$N" HIR
						   "������˱��У�������������ͷ��$P"
						   HIR "ץ�˸���Ѫ���졣"NOR"\n");
		} else
			msg += CYN "$n" CYN "�������룬���м�ƮȻ���ˣ���$P"
			       CYN "��һ���޹�������"NOR"\n";
	}

	message_combatd(msg, me, target);
	return 1;
}

