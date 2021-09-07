// zhi.c ���ָ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "���ָ"; }
string *pfm_type() { return ({ "finger", }); }

int perform(object me, object target)
{
	string msg;
	int skill, ap, dp, damage;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! me->is_fighting(target))
		return notify_fail("�����ָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	skill = me->query_skill("canhe-zhi", 1);

	if (skill < 150)
		return notify_fail("��Ĳκ�ָ��Ϊ����, ����ʹ�á����ָ����\n");

	if (me->query_skill_mapped("finger") != "canhe-zhi")
		return notify_fail("��û�м����κ�ָ, ����ʹ�á����ָ����\n");

	if (me->query("neili") < 150)
		return notify_fail("��������������޷����á����ָ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "��ָ��Ȼ������������Ƿ����ؼ����ָ������"
	      "ʽ���죬����$n" HIY "����ǰ��Ѩ��"NOR"\n";

	ap = me->query_skill("finger");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -150);
		me->start_busy(2);
		damage = skill + random(skill);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
					   HIR "$n" HIR "�мܲ�ס�������ꡱһ�±�$P"
					   HIR "��һָ��������ǰ����Ѫֱ����"NOR"\n");
	} else
	{
		me->add("neili",-50);
		msg += CYN "����$n" CYN "������$N" CYN "����ʽ��"
		       "����ĵ�ס��$N" CYN "�Ĺ�����"NOR"\n";
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
