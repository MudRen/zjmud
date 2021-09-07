// tianwai.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }

int perform(object me)
{
	string msg;
	object weapon, target;
	int skill, ap, dp, neili_wound, qi_wound,lvl;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("bibo-shengong", 1) < 120)
		return notify_fail("��ı̲��񹦵ȼ���������"
				   "��ʹ�á�������������\n");

	skill = me->query_skill("yuxiao-jian", 1);

	if (skill < 100)
		return notify_fail("������｣���ȼ�����, ����ʹ�á�������������\n");

	if (me->query("neili") < 200)
		return notify_fail("��������������޷����á�������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "һ����Х����������" + weapon->name() +
	      HIC "������ֹ����Ӱ��ҹĻ������$n" HIC "��"NOR"\n";

	ap = me->query_skill("sword") + me->query_skill("chuixiao-jifa");
	dp = target->query_skill("force") + target->query_skill("chuixiao-jifa");
	if (dp < 1) dp = 1;
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -180);
		qi_wound = (int)me->query_skill("sword") +
			   (int)me->query_skill("bibo-shengong", 1);
		qi_wound = qi_wound *2/ 3 + random(qi_wound / 3);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, qi_wound, 66,
					   HIR "$n" HIR "��ʱ������ǰ�����������˫������"
					   "��������֪����һ���ʹ������һ�㣡"NOR"\n");
            target->receive_wound("qi", qi_wound / 2, me);
	        message_combatd(msg, me, target);

            lvl=me->query_skill("chuixiao-jifa");
	        target->add_temp("apply/dodge", -lvl/3);
	        target->add_temp("apply/parry", -lvl/3);

		if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, weapon, 0);
		if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, weapon, 0);
		if (me->is_fighting(target)) COMBAT_D->do_attack(me, target, weapon, 0);

	        target->add_temp("apply/dodge", lvl/3);
	        target->add_temp("apply/parry", lvl/3);

		me->start_busy(1 + random(3));
	} else
	{
		me->add("neili", -70);
		msg += HIG "����$n" HIG "���ľ��������ֻ�������$N"
		       HIG "������Ʋ��һ�ߡ�"NOR"\n";
	        message_combatd(msg, me, target);
		me->start_busy(2);
	}

	return 1;
}
