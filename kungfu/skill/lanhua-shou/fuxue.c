// fuxue.c ������Ѩ�� ��������Ѩ��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"��Ѩ"; }

int perform(object me, object target)
{
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("������Ѩֻ�ܶ�ս���ж���ʹ�á�\n");

	if ((int)me->query_dex() < 25)
		return notify_fail("��������������ʹ����һ������\n");

	if ((int)me->query_skill("force") < 140)
		return notify_fail("��̲��񹦵Ĺ�����������ʹ��������Ѩ��\n");

	if ((int)me->query_skill("hand") < 140)
		return notify_fail("����ַ���Ϊ������Ŀǰ������ʹ����"
				   "����Ѩ������\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("���������ڲ���, ����ʹ���黨��Ѩ��\n");

	if (target->is_busy())
		return notify_fail(target->name() +
				   "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIB "$N" HIB "���ַ������������ָͷ��ת��һ��ʢ����"
	      "��������ӯ����$n" HIB "��в��ҪѨ��\n";

	ap = me->query_skill("hand");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		msg +=  HIB "���$p" HIB "��$P" HIB "������ţ���ʱ����"
			"�޴룬�������أ�"NOR"\n";
		target->start_busy((int)me->query_skill("lanhua-shou", 1) / 45 + 2);
		me->add("neili", -100);
	} else
	{
		msg += HIY "����$p" HIY "������$P" HIY
		       "����ͼ������һԾ�����˿�ȥ��"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
