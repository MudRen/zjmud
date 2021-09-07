// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "ŭ��"ZJBR"��ӿ"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ����ŭ�γ�ӿ�����Լ���ս������\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");

	me->add("neili", -200);
	me->receive_damage("qi", 0);

	message_combatd(HIC "$N" HIC"һ����Х������һ���磬��"
			"�˷���������������ɢ����\n��ʱ֮�䣬��"
			"�Ƴ��綯�����ƾۺϣ������Ȼ�����纣"
			"�����ϡ�"NOR"\n", me);

	me->add_temp("apply/attack", skill * 2 / 5);
	me->add_temp("apply/defense", skill * 2 / 5);
	me->add_temp("apply/damage", skill / 4);
	me->add_temp("apply/unarmed_damage", skill / 4);
	me->set_temp("powerup", 1);
	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
	if (me->is_fighting()) me->start_busy(3);
	return 1;
}

void remove_effect(object me, int skill)
{
	if (me->query_temp("powerup"))
	{
		me->add_temp("apply/attack", -(skill * 2 / 5));
		me->add_temp("apply/defense", -(skill * 2 / 5));
		me->add_temp("apply/damage", -(skill / 4));
		me->add_temp("apply/unarmed_damage", -(skill / 4));
		me->delete_temp("powerup");
		tell_object(me, "���ŭ�γ�ӿ������ϣ��������ջص��\n");
	}
}
