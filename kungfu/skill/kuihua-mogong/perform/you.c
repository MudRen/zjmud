// you.c ��ڤһ��
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
string query_name() { return "��ڤ"ZJBR"һ��"; }

int perform(object me, object target)
{
	string msg;
	int ap, dp;
	int damage;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ڤһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (me->query_skill("kuihua-mogong", 1) < 120)
		return notify_fail("��Ŀ���ħ����������죬����ʹ����ڤһ����\n");

	if (me->query("neili") < 200)
		return notify_fail("�����������������ʹ����ڤһ����\n");
 
       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "��������ǰȥ����ʱ��ƽ�$n" HIR
	      "������������Ȼ����$p��Ҫ����"NOR"\n";
 
	ap = me->query_skill("sword")*3/2 + me->query("dex") * 20 +
	     me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry") + target->query("dex") * 20 +
	     target->query_skill("martial-cognize", 1);

	me->start_busy(1);
	me->add("neili", -40);

	if (ap / 2 + random(ap) < dp)
	{
		msg += HIG "Ȼ��$n" HIG "�ֵ��÷�����$N" HIG
		       "�Ĺ���һһ���⡣"NOR"\n";
	} else
	{
		me->add("neili",-60);
		damage = ap / 3 + random(ap / 3) - random(100);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
					   HIR "$n" HIR "��æ���ˣ�������ң��������$N"
					   HIR "���У���Ѫ����һ�أ�"NOR"\n");
	}

	message_combatd(msg, me, target);
	return 1;
}
