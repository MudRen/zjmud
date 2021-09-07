#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "staff", }); }

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
		return notify_fail("����������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("������ֳ�һ���Ȳ���ʩչ������������\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹�������ʩչ������������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("��������������޷�ʩչ������������\n");

	if ((lvl = (int)me->query_skill("xiangmo-zhangfa", 1)) < 120)
		return notify_fail("��Ľ�ħ�ȷ��������ң��޷�ʹ�õ�������\n");

	if (me->query_skill_mapped("staff") != "xiangmo-zhangfa")
		return notify_fail("��û�м�����ħ�ȷ����޷�ʹ�õ�������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "��Хһ������ȫ����ע�����е�" + weapon->name() +
	      HIW "��ʱ��" HIR "ϼ������" HIW "���յ�$n��������" HIW "��"NOR"\n";

	if (lvl / 2 + random(lvl) > target->query_skill("parry",1) * 2 / 3)
	{
		msg += HIY "$n" HIY "��$N" HIY "�����е�" + weapon->name() +
		       HIY "����һƬǹ������,��ʱ��������������������ȫ��ʧȥ���·���"NOR"\n";
		count = lvl / 6;
		me->add_temp("apply/attack", count);
	} else
		count = 0;

	message_combatd(msg, me, target);
	me->add("neili", -100);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(2) && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(5));
	return 1;
}

