// reserve.c ��󡹦������ת

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount);

string query_name() { return "����"ZJBR"��ת"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	object weapon;
	int skill;
	string msg;

	if ((int)me->query_skill("hamagong", 1) < 120)
		return notify_fail("��ĸ�󡹦������죬���ᾭ����ת��\n");

	if ((int)me->query("neili") < 200) 
		return notify_fail("�����ڵ�����������\n");

	if ((int)me->query_temp("hmg_dzjm"))
		return notify_fail("���Ѿ���ת�����ˡ�\n");

	skill = me->query_skill("hamagong", 1);
	msg = HIB "$N" HIB "����˫�ֳŵص��������˾�������ʱ"
	      "��Ϣ������������������"NOR"\n";
	message_combatd(msg, me);

	me->add_temp("apply/dodge", skill / 4);
	me->add_temp("apply/parry", skill / 4);
	me->add_temp("apply/armor", skill / 2);
	me->add_temp("apply/dispel_poison", skill / 2);
	me->set_temp("hmg_dzjm", skill);

	me->add("neili", -100);
	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

