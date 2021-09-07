// fochen.c ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "���"ZJBR"����"; }

int perform(object me, object target)
{
	int angry;
	string msg;
	int skill, ap, dp, damage;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! me->is_fighting(target))
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	skill = me->query_skill("yujiamu-quan", 1);

	if (skill < 100)
		return notify_fail("��Ľ�����ĸȭ��Ϊ����, �޷�ʹ�á���������\n");

	if (me->query("neili") < 180)
		return notify_fail("��������������޷����á���������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	if (angry = me->query("qi") < me->query("max_qi") / 2)
		msg = HIY "$N" HIY "Ŀ�����ѣ�һ�����ȣ�ȭͷ����������$n"
		      HIY "��Ҫ����"NOR"\n";
	else
		msg = HIY "$N" HIY "���һ����ȭͷ����������$n"
		      HIY "��Ҫ����"NOR"\n";

	ap = me->query_skill("cuff", 1) / 2 + skill;
	dp = target->query_skill("dodge");
	if (dp < 1) dp = 1;
	if (ap / 2 + random(ap * 4 / 5) > dp)
	{
		me->add("neili", -100);
		me->start_busy(1);
		damage = 10 + skill / 3 + random(skill / 2);
		if (angry) damage += random(damage / 2);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35,
					   HIR "���$p" HIR "�޷��ֵ�$P"
					   HIR "������һ������ʱ������������ҡ�β�����"NOR"\n");
	} else
	{
		me->add("neili",-40);
		msg += CYN "����$p" CYN "��δ�����������壬���ƽŲ����㿪��$P"
		       CYN "�Ĺ�����"NOR"\n";
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
