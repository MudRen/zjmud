// zhua.c ������ץ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"��ץ"; }

int perform(object me, object target)
{
	int damage;
	string  msg;
	string  pmsg;
	string *limbs;
	string  limb;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("������ץֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("jiuyin-shengong", 1) < 120)
		return notify_fail("��ľ����񹦻�������죬����ʹ�þ�����ץ��\n");
				
	if ((int)me->query("neili", 1) < 200)
		return notify_fail("����������̫��������ʹ�þ�����ץ��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "΢΢һЦ�����ֳ�צ������ץ��$n"
	      HIY "��ҪѨ��"NOR"\n";
	me->add("neili", -20);

	ap = me->query_skill("jiuyin-shengong", 1) * 3 / 2 +
	     me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry") +
	     target->query_skill("martial-cognize", 1);

	me->want_kill(target);
	if (ap / 2 + random(ap * 2) > dp)
	{
		me->start_busy(2);
		me->add("neili", -180);
		damage = 0;

		if (me->query("max_neili") > target->query("max_neili") * 2)
		{
			damage = ap * 5 + (int)me->query_skill("force");

			pmsg = HIR "$N" HIR "��һצ���ƺÿ죬��ץ��$n"
			       HIR "��̴�д�Ѩ��$n" HIR
			       "һ���ҽУ��������̱����ȥ��"NOR"\n";

			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120, pmsg);
		} else
		{
			damage = ap + (int)me->query_skill("force");
			damage = damage / 2 + random(damage / 2);
			
			if (arrayp(limbs = target->query("limbs")))
				limb = limbs[random(sizeof(limbs))];
			else
				limb = "Ҫ��";
			pmsg = HIR "$n��æ��Ų������Ȼ�������ꡱһ����$N"
			       HIR "��ָ������$n" HIR "��" + limb + "��$n"
			       HIR "һ���ҽУ�Ѫ���岽��"NOR"\n";
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70, pmsg);
		}
	} else 
	{
		me->start_busy(2);
		msg += CYN "����$p" CYN "������$P"
		       CYN "�����ƣ���Ӧ�÷����ܿ�����һץ��"NOR"\n";
	}

	message_combatd(msg, me, target);

	return 1;
}

