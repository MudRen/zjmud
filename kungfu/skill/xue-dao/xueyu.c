// xueyu.c Ѫ��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"Ѫ��"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count;
	int i;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (! target || ! me->is_fighting(target))
		return notify_fail("��Ѫ�꡹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");
		
	if ((int)me->query_skill("xue-dao", 1) < 70)
		return notify_fail("���Ѫ������������죬����ʹ�á�Ѫ�꡹��\n");
				
	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���Ϊ�����ߡ�\n");
			
	if ((int)me->query("neili") < 100)
		return notify_fail("��������������������ʹ�á�Ѫ�꡹��\n");

	if (me->query_skill_mapped("blade") != "xue-dao")
		return notify_fail("��û�м���Ѫ������������ʹ�á�Ѫ�꡹��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "��Ŀ��ȣ�����һ����" + weapon->name() +
	      HIR "������һ�㿳��$n" HIR "��"NOR"\n";

	message_combatd(msg, me, target);
	me->add("neili", -100);

	count = me->query_skill("blade") / 12;
	me->add_temp("apply/attack", count);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(5));
	return 1;
}
