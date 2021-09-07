// sanjue.c  ��Ħ�� ��Ħ������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "������"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����Ħ��������ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_dex() < 30)
		return notify_fail("�����������Ŀǰ������ʹ�����������\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

	if (me->query_skill("dodge") < 200)
		return notify_fail("����Ṧ��Ϊ����������ʹ�ô�Ħ��������\n");
 
	if (me->query_skill("sword") < 200)
		return notify_fail("��Ľ�����Ϊ������Ŀǰ����ʹ�ô�Ħ��������\n");

	if (me->query("neili") < 150)
		return notify_fail("�����������������ʹ�ô�Ħ��������\n");

	if (me->query_skill_mapped("sword") != "damo-jian")
		return notify_fail("��û�м�����Ħ��������ʹ�ô�Ħ��������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "ʹ����Ħ���ľ�������Ħ��������������Ȼ�ӿ죡"NOR"\n";
	message_combatd(msg, me);

	me->add("neili", -75);

	// The first attack
      	COMBAT_D->do_attack(me, target, weapon, 0);

	// The second attack
	me->add_temp("apply/attack", 40);
	COMBAT_D->do_attack(me, target, weapon, 0);

	// The third attack
	me->add_temp("apply/attack", 40);
	COMBAT_D->do_attack(me, target, weapon, 0);

	// Back
	me->add_temp("apply/attack", -80);

	me->start_busy(1 + random(3));

	return 1;
}
