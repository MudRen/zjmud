// chan.c ��糾�� ���־�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }

int perform(object me, object target)
{
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("qiufeng-chenfa", 1) < 80)
		return notify_fail("����糾������Ϊ����������ʹ�ò��־���\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɡ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = CYN "$N" CYN "ʹ����糾���������־�������������ͼ��$n"
	      CYN "��ȫ���ס��"NOR"\n";

	ap = me->query_skill("whip");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		msg += CYN "���$p" CYN "��$P" CYN "���˸����ֲ�����"NOR"\n";
		target->start_busy((int)me->query_skill("whip") / 28 + 2);
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ����û���ϵ���"NOR"\n";
		me->start_busy(4);
	}
	message_combatd(msg, me, target);
	me->add("neili", -100);
	return 1;
}
