// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "��ϼ"ZJBR"����"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ������ϼ�������Լ���ս������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");

	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(MAG "$N" MAG "΢һ����������ϼ�񹦣���ת"
			"��ȥ������ͻȻ������ʢ��ֻ��������һ�ּ�����\n"
			"ת�������������ֻظ��糣��"NOR"\n", me);

	me->add_temp("apply/attack", skill / 3);
	//me->add_temp("apply/armor", skill / 3);
	me->add_temp("apply/defense", skill / 3);
	me->set_temp("powerup", 1);
	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 3 :), skill);
	if (me->is_fighting()) me->start_busy(3);
	return 1;
}

void remove_effect(object me, int amount)
{

        if (!me) return;

	if (me->query_temp("powerup"))
	{
		me->add_temp("apply/attack", -amount);
	        //me->add_temp("apply/armor", -amount);
		me->add_temp("apply/defense", -amount);
		me->delete_temp("powerup");
		tell_object(me, "�����ϼ��������ϣ��������ջص��\n");
	}
}