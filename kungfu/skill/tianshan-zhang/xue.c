// xue.c ��ѩ�׷�

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "��ѩ"ZJBR"�׷�"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int i;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ѩ�׷ɡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("����ѩ�׷ɡ�����������֣�\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("tianshan-zhang", 1) < 90)
		return notify_fail("�����ɽ�ȷ��������ң��޷�ʹ�ñ�ѩ�׷ɣ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "ʹ�����޾�������ѩ�׷ɡ�����ʽ��ù����쳣��"NOR"\n";
	message_combatd(msg, me);
	me->add("neili", -100);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->start_busy(1 + random(4));
	return 1;
}
