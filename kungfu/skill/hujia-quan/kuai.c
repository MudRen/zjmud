// kuai.c ����ȭ��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"��ȭ"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ȭ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((int)me->query_skill("hujia-quan", 1) < 80)
		return notify_fail("��ĺ���ȭ��������죬����ʹ�á���ȭ����\n");

	if (me->query("neili") < 80)
		return notify_fail("�����������������޷�ʹ�á���ȭ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "�ݲ���ǰ��ȭ�е�������ʱ��$n"
	      HIG "��������ʮ�С�"NOR"\n";

	me->add("neili", -40);
	ap = me->query_skill("cuff");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR "���$p" HIR "�޷�����$P" HIR "��ʽ�е���ʵ��"
		       "������æ���ң������ֵ���"NOR"\n";
		target->start_busy((int)me->query_skill("cuff") / 25 + 2);
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "�����У�����һ����"
		       "�ܿ����Ⱪ������һ��ȭӰ��"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
