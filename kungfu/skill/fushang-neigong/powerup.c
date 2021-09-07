// powerup.c ��ɣ�ڹ�

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "��ɣ"ZJBR"ս��"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���÷�ɣ�ڹ��������Լ���ս������\n");

	if ((int)me->query("neili") < 100 )
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	me->add("neili", -90);
	me->receive_damage("qi", 0);

	message_combatd(HIR "$N" HIR "���һ���������ɣ�ڹ���"
			"ȫ��ǽڷ���һ�󱬶�������죡"NOR"\n", me);

	me->add_temp("apply/attack", skill / 3);
	me->add_temp("apply/defense", skill / 3);
	me->set_temp("powerup", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill/3 :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
	if ((int)me->query_temp("powerup"))
	{
		me->add_temp("apply/attack", -amount);
		me->add_temp("apply/defense", - amount);
		me->delete_temp("powerup");
		tell_object(me, "��ķ�ɣ�ڹ�������ϣ��������ջص��\n");
	}
}
