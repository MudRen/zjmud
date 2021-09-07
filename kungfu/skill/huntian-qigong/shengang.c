// shengang.c ���������������

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

string query_name() { return "����"ZJBR"���"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	object weapon;  
	string msg;
	int skill;

	if ((int)me->query_temp("shengang"))
		return notify_fail(HIG"���Ѿ����˻�������ˡ�\n");

	if (! me->is_fighting())
		return notify_fail("���������ֻ����ս����ʹ�á�\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("��Ļ�����������Ϊ����������ʹ�û������\n");

	msg = HIY "$N" HIY "ʹ�����������������������������ע�����ģ�"NOR"\n";

	skill = (int)me->query_skill("huntian-qigong", 1);

	if (me->query("qi") > me->query("max_qi") * 4 / 10)
	{       
		me->add_temp("apply/damage", skill / 2);
		me->add_temp("apply/unarmed_damage", skill / 2);
		me->set_temp("shengang", 1);
		me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);
		me->add("neili", -150);
		me->receive_damage("qi", me->query("max_qi") / 5);
	} else
		msg = HIR "$N" HIR "ƴ�����������������"
		      "��������Լ��������ã�û�ܳɹ���"NOR"\n";

	message_combatd(msg, me);
	return 1;
}

void remove_effect(object me, int amount)
{
	if ((int)me->query_temp("shengang"))
	{
		me->add_temp("apply/damage", -amount);
		me->add_temp("apply/unarmed_damage", -amount);
		me->delete_temp("shengang");
		tell_object(me, "��Ļ������������ϣ��������ջص��\n");
	}
}
