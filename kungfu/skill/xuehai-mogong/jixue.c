// jixue.c Ѫ��ħ����Ѫ��

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

string query_name() { return "��Ѫ"ZJBR"��"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	object weapon;  
	string msg;
	int skill;

	if ((int)me->query_temp("jixue"))
		return notify_fail("���Ѿ������Ѫ���ˡ�\n");

	if (! me->is_fighting())
		return notify_fail("����Ѫ�󷨡�ֻ����ս����ʹ�á�\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("���Ѫ��ħ������Ϊ����������ʹ�ü�Ѫ�󷨣�\n");

	msg = HIR "$N" HIR "ʹ��Ѫ��ħ������Ѫ�󷨡���ɲʱ����ɫ���"
	      "Ѫ�죬"HIR "$N" HIR "����ҧ����⣬���һ����Ѫ��"NOR"\n";

	skill = (int)me->query_skill("xuehai-mogong", 1);

	if (me->query("qi") > me->query("max_qi") * 6 / 10)
	{       
		me->add_temp("apply/damage", skill);
		me->add_temp("apply/unarmed_damage", skill);
		me->set_temp("jixue", 1);
		me->start_call_out((: call_other, __FILE__, "remove_effect",
				   me, skill :), skill/30);
		me->add("neili", -150);
		me->receive_damage("qi", me->query("max_qi") / 2);
	} else
		msg = HIR "$N" HIR "�����Լ��������ã�û�������Ѫ�󷨡�"NOR"\n";

	message_combatd(msg, me);
	return 1;
}

void remove_effect(object me, int amount)
{
	if ((int)me->query_temp("jixue"))
	{
		me->add_temp("apply/damage", -amount);
		me->add_temp("apply/unarmed_damage", -amount);
		me->delete_temp("jixue");
		tell_object(me, "��ļ�Ѫ��������ϣ��������ջص��\n");
	}
}
