// powerup.c ���칦����

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ�������칦�������Լ���ս������\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	me->add("neili", -100);
	message_combatd(HIY "$N΢һ��������������������׳�������ȫ����"
			"�����������"NOR"\n",me);
	me->add_temp("apply/attack", skill * 2 / 5);
	me->add_temp("apply/dodge", skill * 2 / 5);
	me->add_temp("apply/parry", skill * 2 / 5);
	me->set_temp("powerup", 1);

	me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill * 2 / 5 :), skill);
	if (me->is_fighting()) me->start_busy(3);
	return 1;
}

void remove_effect(object me, int amount)
{
	if (me->query_temp("powerup"))
	{
		me->add_temp("apply/attack", -amount);
		me->add_temp("apply/dodge", -amount);
		me->add_temp("apply/parry", -amount);
		me->delete_temp("powerup");
		tell_object(me, "������칦������ϣ��������ջص��\n");
	}
}
