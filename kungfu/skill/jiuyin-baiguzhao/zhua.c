// zhua.c �����׹�צ - ������ץ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"��ץ"; }
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
		return notify_fail("������ץֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ�þ�����ץ��\n");
		
	if ((int)me->query_skill("jiuyin-baiguzhao", 1) < 80)
		return notify_fail("��ľ����׹�צ��������죬����ʹ�þ�����ץ��\n");

	if (me->query_skill_mapped("claw") != "jiuyin-baiguzhao")
		return notify_fail("��û�м��������׹�צ���޷�ʹ�þ�����ץ��\n");
				
	if ((int)me->query("neili", 1) < 200)
		return notify_fail("����������̫��������ʹ�þ�����ץ��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "��Цһ������¶�׹⣬���ֳ�צ��������������"
	      "ʵʵ����$n" HIR "��ͷ��ץ��������"NOR"\n";
	me->add("neili", -20);

	me->want_kill(target);
	ap = me->query_skill("claw");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap * 2 / 3) > dp)
	{
		me->start_busy(2);
		me->add("neili", -180);
		damage = 0;

		if (me->query("max_neili") < target->query("max_neili") * 4 / 5 &&
		    me->query_skill("force") < target->query_skill("force"))
			msg += HIY "��ž����һ��$N" HIY "��ץ��$n" HIY "��������ϣ�"
			       "�����á����ۡ��ֽ���������"NOR"\n";
		else
		if (me->query("max_neili") > target->query("max_neili") * 2)
		{
			damage = ap * 5 + (int)me->query_skill("force");

			pmsg = HIY "�����ꡱһ����$N" HIY "��ָ������$n" HIY "������"
			       "�ǣ�$n" HIY "һ���ҽУ��������̱����ȥ��"NOR"\n";

			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120, pmsg);
		} else
		{
			damage = ap + (int)me->query_skill("force");
			damage = damage / 2 + random(damage / 2);
			
			if (arrayp(limbs = target->query("limbs")))
				limb = limbs[random(sizeof(limbs))];
			else
				limb = "Ҫ��";
			pmsg = HIC "$n��æ��Ų������Ȼ�������ꡱһ����$N"
			       HIC "��ָ������$n" HIC "��" + limb + "��$n"
			       HIC "һ���ҽУ�Ѫ���岽��"NOR"\n";
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 66, pmsg);
		}
	} else 
	{
		me->start_busy(2);
		msg += CYN "����$p" CYN "������$P"
		       CYN "����ͼ�����μ������㿪����һץ��"NOR"\n";
	}

	message_combatd(msg, me, target);

	if (! target->is_killing(me))
		target->kill_ob(me);

	return 1;
}

