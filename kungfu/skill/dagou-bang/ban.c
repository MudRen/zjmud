// ban.c �򹷰��������־�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }
string *pfm_type() { return ({ "staff", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count;
	int i;

	if (! target ) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�򹷰��������־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("dagou-bang", 1) < 100)
		return notify_fail("��Ĵ򹷰���������죬����ʹ�á����־���\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ������������ʹ�á����־���\n");

	if (me->query("neili") < 100)
		return notify_fail("�����ڵ������������޷�ʹ�á����־���\n");

	if (me->query_skill_mapped("staff") != "dagou-bang")
		return notify_fail("��û�м����򹷰���������ʹ�á����־���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "ʹ���򹷰��������־������е�" + weapon->name() +
	      HIG "����ұƣ���ʱ�������С�"NOR"\n";

	message_combatd(msg, me);
	me->add("neili", -180);
	count = me->query("int") * 2;
	me->add_temp("apply/attack", count);

	for (i = 0; i < 4; i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(2) && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}
	target->interrupt_busy(target, 1);

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(4));

	return 1;
}
