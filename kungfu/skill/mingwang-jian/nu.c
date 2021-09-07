// nu.c ����ŭ

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"֮ŭ"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int damage;
	int i;
	int count;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("������ŭ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("������н�����ʩչ������ŭ����\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("��������������޷�ʩչ������ŭ����\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹�������ʩչ������ŭ����\n");

	if ((int)me->query_skill("mingwang-jian", 1) < 50)
		return notify_fail("��Ĳ������������������ң��޷�ʹ������ŭ��\n");

	if (me->query_skill_mapped("sword") != "mingwang-jian")
		return notify_fail("��û�м��������������޷�ʹ�á�����ŭ����\n");

       if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "���һ��������" + weapon->name() +
	      HIR "����������ˮ������Ȼ����ɱ������$n" HIR "��"NOR"\n";
	message_combatd(msg, me, target);
	me->add("neili", -120);

	count  = me->query_skill("sword") / 12;
	damage = me->query_skill("force") / 10;
	me->add_temp("apply/attack", count);
	me->add_temp("apply/damage", damage);

	for (i = 0; i < 4; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->add_temp("apply/damage", -damage);
	me->start_busy(1 + random(4));
	return 1;
}
