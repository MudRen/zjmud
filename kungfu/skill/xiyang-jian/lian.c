// lian.c ����������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "������"; }
string *pfm_type() { return ({ "sword", }); }

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
		return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�����ý�����ʩչ������������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("��������������޷�ʩչ������������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹�������ʩչ������������\n");

	if ((int)me->query_skill("xiyang-jian", 1) < 80)
		return notify_fail("����������������ң��޷�ʹ����������\n");

	if (me->query_skill_mapped("sword") != "xiyang-jian")
		return notify_fail("��û�м������������޷�ʹ����������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "\n$N" HIC "���һ����ֻ����һ������һ������һ������һ��������һ����һ�����$n"
	      HIC "��"NOR"\n";
	message_combatd(msg, me, target);
	me->add("neili", -100);

	for (i = 0; i < 5; i++)
	{
		if (random(3) == 0 && ! target->is_busy())
			target->start_busy(1);

		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->start_busy(1 + random(5));
	return 1;
}
