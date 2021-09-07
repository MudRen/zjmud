// shield.c �����޼���

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount);

string query_name() { return "�޼�"ZJBR"����"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;
	string msg;

	if ((int)me->query_skill("xiantian-gong", 1) < 100)
		return notify_fail("������칦������񣬲���ʹ�������޼�����\n");

	if ((int)me->query("neili") < 200) 
		return notify_fail("�����ڵ�����������\n");

	if ((int)me->query_temp("shield"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	msg = HIY "$N" HIY "��������һ������˫��һ��һ�ɻ�"
	      "���������ʱ������������ܡ�"NOR"\n";
	message_combatd(msg, me);

	me->add_temp("apply/armor", skill / 2);
	me->set_temp("shield", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);

	me->add("neili", -100);
	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
	if (me->query_temp("shield"))
	{
		me->add_temp("apply/armor", -amount);
		me->delete_temp("shield");
		tell_object(me, "�㽫�����޼�����ת��һ�����죬�������ջص��\n");
	}
}

