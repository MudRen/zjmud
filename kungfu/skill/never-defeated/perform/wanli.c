// wanli.c �������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "���"ZJBR"����"; }

int perform(object me, object target)
{
	object  weapon;
	int     damage;
	string  msg;
	string  pmsg;
	string *limbs;
	string  limb;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("never-defeated", 1) < 120)
		return notify_fail("��Ĳ����񹦻�������죬����ʹ��������\n");
				
	if ((int)me->query("neili", 1) < 200)
		return notify_fail("����������̫��������ʹ��������\n");
			
	if (! objectp(weapon = me->query_temp("weapon")))
		return notify_fail("������ֱֳ��в���ʩչ������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "����" + weapon->name() + HIC "��һ"
	      "ȦȦ�Ļ���$n" HIC "����$p" HIC "���ڵ��У�"NOR"\n";
	me->add("neili", -20);

	ap = me->query_skill("never-defeated", 1) * 3 / 2 +
	     me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry") +
	     target->query_skill("martial-cognize", 1);

	if (ap / 2 + random(ap * 2) > dp)
	{
		me->start_busy(2);
		me->add("neili", -180);

		damage = ap + me->query_skill("force");
		damage = damage / 2 + random(damage / 2);

		if (arrayp(limbs = target->query("limbs")))
			limb = limbs[random(sizeof(limbs))];
		else
			limb = "Ҫ��";
		pmsg = HIR "$n��æ��Ų������Ȼ�������ꡱһ����" + weapon->name() +
		       HIR "���û���$p" HIR "��" + limb + "��$p"
		       HIR "һ���ҽУ�����������"NOR"\n";
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, pmsg);
	} else 
	{
		me->start_busy(2);
		msg += CYN "����$p" CYN "������$P"
		       CYN "�ı仯�����в��У�û���ܵ��κ��˺���"NOR"\n";
	}

	message_combatd(msg, me, target);

	return 1;
}
