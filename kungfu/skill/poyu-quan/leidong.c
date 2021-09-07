// leidong �׶�����
// by winder 98.12

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "�׶�"ZJBR"����"; }

int perform(object me)
{
	int skill, count, count1;

	if ((int)me->query_temp("leidong"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�����ڵ�����������\n");

	skill = me->query_skill("cuff");
	if (skill < 135)
		return notify_fail("�������ȭ��Ϊ��������\n");

	me->add("neili", -400);
	message_combatd(HIM "$N" HIM "��������һ���������϶�ʱ"
			"������ʢ������Խ��Խ�أ�"NOR"\n", me);

	count = skill / 10;

	if (me->is_fighting())
		me->start_busy(2);

	me->add_temp("str", count);
	me->add_temp("dex", count);
	me->set_temp("leidong", 1);
	me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 3);

	return 1;
}

void remove_effect(object me, int amount)
{
	if ((int)me->query_temp("leidong"))
	{
		me->add_temp("str", -amount);
		me->add_temp("dex", -amount);
		me->delete_temp("leidong");
		tell_object(me, CYN "����׶�����������ϣ��������ջص��"NOR"\n");
	}
}
