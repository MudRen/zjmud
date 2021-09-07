#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"߱��"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon, weapon2;
	int damage;
	string  msg;
	string  pmsg;
	string *limbs;
	string  limb;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill_mapped("sword") != "zhuihun-jian") 
		return notify_fail("��û�м���׷����������޷�ʹ�á�����ɲ�񡹡�\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("������ɲ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("zhuihun-jian", 1) < 160)
		return notify_fail("���׷���������������죬����ʹ�á�����ɲ�񡹡�\n");
				
	if ((int)me->query("neili", 1) < 300)
		return notify_fail("����������̫��������ʹ�á�����ɲ�񡹡�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "ͻȻ$N" HIW "һ����ߣ�һ���粽������" + weapon->name() +
	      NOR + HIW "�й�ֱ����������һ�����$n" HIW "��"NOR"\n";
	me->add("neili", -150);

	ap = me->query_skill("zhuihun-jian", 1) +
	     me->query_skill("sword", 1);
	dp = target->query_skill("parry", 1) * 2;

	me->want_kill(target);
	if (target->query("static/sadly") > 2)
		ap = ap * 2;

	if (ap / 2 + random(ap) > dp)
	{
		me->start_busy(2);
		me->add("neili", -200);
		damage = 0;

		if (me->query("max_neili") > target->query("max_neili") * 2)
		{
			damage = ap * 5 + (int)me->query_skill("force");

			pmsg = HIR "ֻ��$N" HIR "��һ�����ƺÿ죬��������"
			       "����һ����������û��$n" HIR "�ʺ��ߣ�\n$n"
			       HIR "���������������������̱����ȥ��"NOR"\n";

			msg += COMBAT_D->do_damage(me, target,
			       WEAPON_ATTACK, damage, 120, pmsg);
		} else

		if (objectp(weapon2 = target->query_temp("weapon")) &&
		   me->query_skill("force") > target->query_skill("parry") &&
		   ! random(3))
		{
			msg += HIR "ֻ����������һ����$n" HIR "���ѱ�$N"
			       HIR + weapon->name() + NOR + HIR "�Դ�����"
			       "������" + weapon2->name() + NOR + HIR
			       "��Ҳ׽�ò�ס�����ֶ��ɣ�"NOR"\n";
			me->start_busy(random(2));
			weapon2->move(environment(target));
		} else
		{
			damage = ap + (int)me->query_skill("force");
		      
			if (arrayp(limbs = target->query("limbs")))
				limb = limbs[random(sizeof(limbs))];
			else
				limb = "Ҫ��";
			pmsg = HIR "$n" HIR "���������Ȼ��ֻ����������"
			       "һ����$N" HIR + weapon->name() + NOR +
			       HIR "��û��$n" HIR + limb + "��磬��Ѫ"
			       "�񽦶�����"NOR"\n";
			msg += COMBAT_D->do_damage(me, target,
			       WEAPON_ATTACK, damage, 70, pmsg);
		}
	} else 
	{
		me->start_busy(3);
		msg += CYN "����$p" CYN "������$P"
		       CYN "����ͼ���ܿ�����һ�С�"NOR"\n";
	}

	message_combatd(msg, me, target);

	return 1;
}
