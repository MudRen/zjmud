// pi.c Ⱥа����

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return HIR"Ⱥа"ZJBR"����"NOR; }

int perform(object me, object target)
{
	string msg;
	object weapon;
	int i;
	int skill;
	int count;
	int isGhost;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! me->is_fighting(target))
		return notify_fail("��Ⱥа���ס�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	skill = me->query_skill("pixie-jian", 1);

	if (skill < 120)
		return notify_fail("��ı�а������Ϊ���ޣ����ڲ���ʹ�á�Ⱥа���ס���\n");

	if (me->query("neili") < 100)
		return notify_fail("��������������޷����á�Ⱥа���ס���\n");

	weapon = me->query_temp("weapon");

	if (weapon && weapon->query("skill_type") != "sword" &&
	    weapon->query("skill_type") != "pin")
		return notify_fail("�㲻��ʹ�����ֱ���ʩչ��Ⱥа���ס���\n");

	if (! weapon &&
	    sizeof(me->query_skill_prepare()) &&
	    me->query_skill_prepared("unarmed") != "pixie-jian")
		return notify_fail("��û��׼��ʹ�ñ�а����������ʩչ��Ⱥа���ס���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	if (weapon)
	{
		msg = HIR "$N" HIR "���κ�Ȼ��죬��ĳ���$n"
		      HIR "�����е�" + weapon->name() + HIR "ָָ��㣬��ͬ"
		      HIR "��ҹ����һ�㣬����â����$p" HIR "��"NOR"\n";
	} else
	{
		msg = HIR "$N" HIR "��Ȼ����$n" HIR "�������"
		      HIR "����˼�飬�������ȣ����־�����������$n" HIR "��"NOR"\n";
	}

	message_combatd(msg, me, target);
	count = skill / 8;
	isGhost = me->query("special_skill/ghost");

	if (isGhost && random(2))
		count *= 4;

	me->add_temp("apply/attack", count);

	for (i = 0; i < 7; i++)
	{
		if (! me->is_fighting(target))
			break;
		if ((random(3) == 0 || (isGhost && random(2))) && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	if (me->query("special_skill/ghost") && random(2))
		me->start_busy(1 + random(4));
	else
		me->start_busy(1 + random(7));

	me->add_temp("apply/attack", -count);

	return 1;
}

