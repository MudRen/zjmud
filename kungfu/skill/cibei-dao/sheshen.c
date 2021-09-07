// sheshen.c ������ιӥ��

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount, int d_amount);

string query_name() { return "����"ZJBR"ιӥ"; }

int perform(object me)
{
	object weapon;
	int skill;
	string msg;

	if ((int)me->query_skill("cibei-dao", 1) < 60)
		return notify_fail("��Ĵȱ�����������죬����ʹ�á�����ιӥ����\n");

	if ((int)me->query("neili") < 200 )
		return notify_fail("��������������޷�ʹ�á�����ιӥ����\n");

	if ((int)me->query_temp("cbd_sheshen"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	skill = me->query_skill("cibei-dao", 1);
	msg = HIR "$N" HIR "ʹ���ȱ�����������ιӥ��������ȫ������"NOR"\n";
	message_combatd(msg, me);

	me->add_temp("apply/attack", skill / 3);
	me->add_temp("apply/dodge", -skill / 5);
	me->set_temp("cbd_sheshen", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect",
			   me, skill / 3, skill / 5 :), skill / 4);

	me->add("neili", -100);
	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int a_amount, int d_amount)
{
	if (me->query_temp("cbd_sheshen"))
	{
		me->add_temp("apply/attack", -a_amount);
		me->add_temp("apply/dodge", d_amount);
		me->delete_temp("cbd_sheshen");
		tell_object(me, "��ġ�����ιӥ��������ϣ��������ջص��\n");
	}
}
