// xiang.c ��ħ

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "��ħ"ZJBR"һ��"; }

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
		return notify_fail("����ħ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("����������Ʋ���ʩչ����ħ����\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("xiangmo-chu", 1) < 80)
		return notify_fail("��Ľ�ħ�Ʒ��������ң��޷�ʹ�þ�������ħ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "һ���Ϻȣ�����ׯ�ϣ�������ǧ�����е�" + weapon->name() + 
	      HIY "��ͷ��$n" HIY "���£�"NOR"\n";
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
