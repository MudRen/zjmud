// he.c ���ϡ��־�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }
string *pfm_type() { return ({ "whip", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int count;
	int i, attack_time;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���±޷����ϡ��־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "whip")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("riyue-bian", 1) < 135)
		return notify_fail("������±޷�������죬����ʹ�á��ϡ��־���\n");

	if (me->query("neili") < 350)
		return notify_fail("��������������޷�ʹ�á��ϡ��־���\n");

	if (me->query_skill_mapped("whip") != "riyue-bian")
		return notify_fail("��û�м������±޷����޷�ʹ�á��ϡ��־���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "�����е�" + weapon->name() +
	      HIY "һ����ʹ�����±޷����ϡ��־������������Ӱ��"NOR"\n";

	ap = me->query_skill("whip") + me->query_skill("force");
	dp = target->query_skill("force") + target->query_skill("parry");
	attack_time = 4;
	if (ap / 2 + random(ap * 2) > dp)
	{
		msg += HIC "���$p" HIC "��$P" HIC
		       "���˸����ֲ�����Ŀ�Ӳ�Ͼ��ƣ�ڱ�����"NOR"\n";
		count = ap / 20;
		me->add_temp("apply/attack", count);
		attack_time += random(ap / 60);
	} else
	{
		msg += HIC "$n" HIC "��$N" HIC "���ƻֺ룬������Ȼ������Ӧ����"NOR"\n";
		count = ap / 40;
		me->add_temp("apply/attack", count);
		attack_time += random(ap / 40);	}
		
	message_combatd(msg, me, target);

	if (attack_time > 8)
		attack_time = 8;

	me->add("neili", -attack_time * 10);

	for (i = 0; i < attack_time; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(5));
	return 1;
}

