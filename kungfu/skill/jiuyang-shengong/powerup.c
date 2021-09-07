// powerup.c �����񹦼���

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "����"ZJBR"ս��"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���þ������������Լ���ս������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIR "$N" HIR "΢һ������������񹦣�������"
			"�����ڵ���֮�У����澭�����鲼ȫ��"NOR"\n", me);

	me->add_temp("apply/attack", skill * 2 / 5);
	me->add_temp("apply/parry", skill / 3);
	me->add_temp("apply/dodge", skill / 3);
	me->set_temp("powerup", 1);

	me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
	if ((int)me->query_temp("powerup"))
	{
		me->add_temp("apply/attack", - (amount * 2 / 5));
		me->add_temp("apply/parry", - (amount / 3));
		me->add_temp("apply/dodge", - (amount / 3));
		me->delete_temp("powerup");
		tell_object(me, "��ľ�����������ϣ��������ջص��\n");
	}
}

