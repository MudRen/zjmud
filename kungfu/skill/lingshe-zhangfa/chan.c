// chan.c ���߲���

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����߲�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("���á����߲��������б�����ȣ�\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("staff") < 80)
		return notify_fail("����ȷ��������ң��޷�ʹ�á����߲�������\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "���е�" + weapon->name() +
	      HIG "��ס�Ĳ���������һ�����ߣ�����$n" HIG "������׽����"NOR"\n";

	ap = me->query_skill("staff");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIY "$n" HIY "�ֻ�֮��ֻ�������Ż�����Ͼ������"NOR"\n";
	target->start_busy(ap / 45 + 2);
	} else 
	{
		msg += HIC "����$p" HIC "������$N" HIC
		       "�����У�������������������$P�Ĺ�����"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}