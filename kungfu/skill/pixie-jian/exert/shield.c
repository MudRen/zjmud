// shield.c ������
//

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "а��"ZJBR"����"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���ñ�а�����������Լ��ķ�������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("pixie-jian", 1) < 50)
		return notify_fail("��ı�а������Ϊ������\n");

	if ((int)me->query_temp("shield"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIW "$N" HIW "���Ӻ�ǰ���󣬺�����ң�һ"
			"������˵�崷�ӿ����סȫ��"NOR"\n", me);

	me->add_temp("apply/armor", skill *2 / 2);
	me->add_temp("apply/armor1", skill *1 / 2);
	me->set_temp("shield", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill * 2 / 2 :), skill);

	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int amount)
{
        if (!me) return;

	me->add_temp("apply/armor", -amount);
	me->add_temp("apply/armor1", -amount/2);
	me->delete_temp("shield");
	tell_object(me, "��ı�а����������ϣ��������ջص��\n");
}

