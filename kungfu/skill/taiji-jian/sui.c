// sui.c ̫������ ���桹�־�

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int a_amount, int d_amount);

string query_name() { return "���־�"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	int skill;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("̫���������桹�־�ֻ����ս����ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("taiji-jian", 1) < 60)
		return notify_fail("���̫������������죬����ʹ�á��桹�־���\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("tjj_sui"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	if (me->query_skill_mapped("sword") != "taiji-jian") 
		return notify_fail("��û�м���̫���������޷�ʹ�á��桹�־���\n");

	skill = me->query_skill("taiji-jian", 1);

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIB "$N" HIB "ʹ��̫���������桹�־�����Ȧ����С������ס��"NOR"\n";
	message_combatd(msg, me, target);

	me->add_temp("apply/attack", -skill / 6);
	me->add_temp("apply/dodge", skill / 3);
	me->set_temp("tjj_sui", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect",
			   me, skill / 6, skill / 3 :), skill / 3);

	me->add("neili", -100);
	if (me->is_fighting()) me->start_busy(2);

	return 1;
}

void remove_effect(object me, int a_amount, int d_amount)
{
	if (me->query_temp("tjj_sui"))
	{
		me->add_temp("apply/attack", a_amount);
		me->add_temp("apply/dodge", -d_amount);
		me->delete_temp("tjj_sui");
		tell_object(me, "������־�������ϣ��������ջص��\n");
	}
}

