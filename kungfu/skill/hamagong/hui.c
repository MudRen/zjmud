// hui.c ��󡹦��Ϣ

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount);

string query_name() { return "���"ZJBR"��Ϣ"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;
	string msg;

	if (! (skill = me->query_temp("hmg_dzjm")))
		return notify_fail("�㲢û�е�ת��������\n");

	msg = HIB "$N" HIB "�����³�һ��������ɫ���˱䣬����������"NOR"\n";
	message_combatd(msg, me);

	me->add_temp("apply/dodge", -skill / 4);
	me->add_temp("apply/parry", -skill / 4);
	me->add_temp("apply/armor", -skill / 2);
	me->add_temp("apply/dispel_poison", -skill / 2);
	me->delete_temp("hmg_dzjm");

	me->set("neili", 0);
	return 1;
}
