// ���ɷ�

#include <ansi.h>

string query_name() { return "����"ZJBR"����"; }

int perform(object me)
{
	int skill;
	string msg;

	if (! me->is_fighting())
		return notify_fail("���ɷ�ֻ����ս����ʹ�á�\n");

	if ((int)me->query_skill("shedao-qigong", 1) < 80)
		return notify_fail("����ߵ��湦������죬����ʹ�ó��ɷ���\n");

	if ((int)me->query_temp("chang") <= -20)
		return notify_fail("���Ѿ�����̫���ˣ������ٳ��ˡ�\n");

	message_combatd(HIR "ֻ��$N" HIR "���������дʣ����֮���������ǣ�"NOR"\n", me);
	me->add_temp("apply/attack", -1);
	me->add_temp("apply/dodge", -1);
	me->add_temp("apply/defense", -1);
	me->add_temp("chang", -1);
	me->add("neili", 100);

	return 1;
}
