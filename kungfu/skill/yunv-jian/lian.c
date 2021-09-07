// lian.c ��������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
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
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("û�н���ô��ʩչ����������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("��������������޷�ʩչ����������\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹�������ʩչ����������\n");

	if ((int)me->query_skill("yunv-jian", 1) < 70)
		return notify_fail("�����Ů�����������ң��޷�ʹ������������\n");

	if (me->query_skill_mapped("sword") != "yunv-jian")
		return notify_fail("��û�м�����Ů�������޷�ʹ������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "��������һת����ʱ��$n" HIC "������������"NOR"\n";
	message_combatd(msg, me, target);
	me->add("neili", -80);

	for (i = 0; i < 4; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->start_busy(1 + random(4));
	return 1;
}
