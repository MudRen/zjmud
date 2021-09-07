// beidou.c  �������ǽ�

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
		return notify_fail("���������ǽ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("ʩչ���������ǽ������б�������һ�ѽ���\n");

	if ((int)me->query("neili") < 220)
		return notify_fail("��������������޷�ʩչ���������ǽ�����\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹����޷�ʩչ���������ǽ�����\n");

	if ((int)me->query_skill("sword") < 150)
		return notify_fail("���Ľ�ݽ����������ң��޷�ʹ�þ������������ǽ�����\n");

	if (me->query_skill_mapped("sword") != "murong-sword")
		return notify_fail("��û�м���Ľ�ݽ������޷�ʹ�á��������ǽ�����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIM "$N" HIM "ʹ��Ľ�ݼҾ������������ǽ���������" + weapon->name() +
	      HIM "���ϱ������Ƿ�λ������������仯Ī�⣡"NOR"\n";

	message_combatd(msg, me);
	me->add("neili", -140);

	for (i = 0; i < 7; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->start_busy(1 + random(7));

	return 1;
}
