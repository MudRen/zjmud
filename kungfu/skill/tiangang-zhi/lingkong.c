// lingxiao.c ���ָѨ�� �����ָѨ��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���"ZJBR"ָѨ"; }
string *pfm_type() { return ({ "finger", }); }

int perform(object me, object target)
{
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���ָѨ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_dex() < 28)
		return notify_fail("��������������ʹ����һ������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("���ڹ���򲻹���������ʹ�����ָѨ��\n");

	if ((int)me->query_skill("finger") < 100)
		return notify_fail("���ָ����Ϊ������Ŀǰ������ʹ�����ָѨ������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("����������ڲ���������ʹ�����ָѨ��\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	if (me->query_skill_mapped("finger") != "tiangang-zhi")
		return notify_fail("��û�м������ָѨ��������ʩչ�����ָѨ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ʹ�����ָѨ�����������ָѨ��������"
	      "ʳ�ж�ָ��$n" HIY "������ȥ��һ����ָ��ȫ�Ƕ���$n"
	      HIY "����ǰ��Ѩ��\n";
	ap = me->query_skill("finger");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIG "���$p" HIG "�������У�ƴ�����$P"
		       HIG "ָ����ʱ�������ң�"NOR"\n";
		target->start_busy((int)me->query_skill("tiangang-zhi", 1) / 22 + 2);
		me->add("neili", -100);
	} else
	{
		msg += CYN "$p" CYN "�鼱����������һԾ���˳���Զ��"NOR"\n";
		me->start_busy(3);
		me->add("neili", -30);
	}
	message_combatd(msg, me, target);

	return 1;
}

