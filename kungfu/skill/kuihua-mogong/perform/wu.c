// wu.c Ⱥħ����

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "Ⱥħ"ZJBR"����"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count;
	int lvl;
	int i;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("Ⱥħ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (me->query("neili") < 200)
		return notify_fail("��������������޷�ʩչȺħ���裡\n");

	if ((lvl = me->query_skill("kuihua-mogong", 1)) < 150)
		return notify_fail("��Ŀ���ħ����򲻹����޷�ʩչȺħ���裡\n");

	if (weapon = me->query_temp("weapon"))
	{
		if (weapon->query("skill_type") != "sword" &&
		    weapon->query("skill_type") != "pin")
			return notify_fail("�������õĲ��ǽ�����ôʩ"
					   "չȺħ���裿\n");
	} else
	{
		if (sizeof(me->query_skill_prepare()) &&
		    me->query_skill_prepared("finger") != "kuihua-mogong" &&
		    me->query_skill_prepared("unarmed") != "kuihua-mogong")
			return notify_fail("�㲢û��׼��ʹ�ÿ�"
					   "��ħ�������ʩչȺħ���裿\n");
	}

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "Ĭ�˿���ħ�������α������ޱȣ�������$n"
	      HIR "�������У�"NOR"\n";
	i = 5;
	if (lvl / 2 + random(lvl) > (int)target->query_skill("dodge", 1))
	{
		msg += HIR "$n" HIR "ֻ������ǰһ�����������ܶ���$N"
		       HIR "����Ӱ�����ɰ������⣬�������ˡ�"NOR"\n";
		count = me->query_skill("kuihua-mogong", 1) / 7;
		me->add_temp("apply/attack", count);
		i += random(6);
	} else
	{
		msg += CYN "$n" CYN "��$N" CYN "���ÿ죬����"
		       "�ҵ�������æ������С��Ӧ�ԡ�"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);
	me->add("neili", -i * 20);

	while (i--)
	{
		if (! me->is_fighting(target))
			break;
		if (i > 5 && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(7));
	return 1;
}
