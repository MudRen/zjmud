// break.c ��ݾ�ɱ

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���"ZJBR"��ɱ"; }

int perform(object me, object target)
{
	string msg;
	int count;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ݾ�ɱ��ֻ����ս����ʹ�á�\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("������������޷�ʩչ����ݾ�ɱ����\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹�������ʩչ����ݾ�ɱ����\n");

	if ((int)me->query("neili") < (int)me->query("max_neili") / 2)
		return notify_fail("��������������޷�ʩչ����ݾ�ɱ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "ʹ�����ж��еġ���ݾ�ɱ������"
	      "��Ȼ���ñ��Ī�⣡"NOR"\n";

	message_combatd(msg, me);
	count = (int)me->query_skill("five-avoid") / 30 + 2;
	if (count > 5 ) count = 5;

	while (count--)
	{
		if (! target || (environment(target) != environment(me)) ||
		    ! me->is_fighting(target) ||
		    me->query("qi") < 20 ||
		    me->query("neili") < 20)
		{
			message_combatd(WHT "$N" WHT "������ٿ��һ"
					"ת������ͣס�˽Ų���"NOR"\n", me);
			break;
		} else

		message_combatd(WHT "$N" WHT "����Ӱ��$n"
				WHT "����ʱ��ʱ�� ..."NOR"\n", me, target);
		if (! COMBAT_D->fight(me, target))
			message_combatd(WHT "����$N" WHT "ʼ��û���ҵ�������֣�"NOR"\n", me);
		me->receive_damage("qi", 10);
		me->add("neili", -10);
	}

	me->start_busy(1);
	return 1;
}
