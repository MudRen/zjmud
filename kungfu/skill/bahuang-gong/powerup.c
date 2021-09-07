#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "�˻�"ZJBR"ս��"; }

string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���ð˻����Ϲ��������Լ���ս������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
		if (skill>800) skill=800;
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIM "$N" HIM "����Ϣ��������˻�����Ψ�Ҷ��𹦣���߳һ������������������"NOR"\n", me);

	me->add_temp("apply/damage", skill/6);
	me->add_temp("apply/unarmed_damage", skill/6);
	me->add_temp("apply/attack", skill / 2);
	me->add_temp("apply/dodge", skill / 3);
	me->add_temp("apply/parry", skill / 3);
	me->set_temp("powerup", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect",me, skill :), skill);

	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
	if (me->query_temp("powerup"))
	{
		me->add_temp("apply/damage", -(amount / 6));
	    me->add_temp("apply/unarmed_damage", -(amount / 6));
		me->add_temp("apply/attack", -(amount / 2));
		me->add_temp("apply/dodge", -(amount / 3));
		me->add_temp("apply/parry", -(amount / 3));
		me->delete_temp("powerup");
		tell_object(me, "��İ˻�����Ψ�Ҷ���������ϣ��������ջص��\n");
	}
}
