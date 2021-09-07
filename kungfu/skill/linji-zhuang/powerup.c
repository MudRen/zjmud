// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount, int di);

string query_name() { return "�ټ�"ZJBR"׮��"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int skill;
	int di;
	object weapon;

	if (target != me)
		return notify_fail("��ֻ�����ټ�ׯ�����Լ���ս������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("powerup"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("force");

	me->add("neili", -100);
	me->receive_damage("qi", 0);

	if (me->query("sex")) di = 0; else di = skill / 2;
	if (di > 100) di = 100;

	message_combatd(MAG "$N" MAG "΢һ���������ټ�ׯ��һ�����ȣ�"
			"���ܵĿ����·������ˣ�"NOR"\n", me);

	if (objectp(weapon = me->query_temp("weapon")))
	{
		if (di >= 95)
			message_combatd(HIR "$N" HIR "��ɫһ���������ټ�ׯ��ͨ����ʱ��" +
					weapon->name() + HIR "�⻪���䣬�����ޱ�ɱ�⡣"NOR"\n", me);
		else
		if (di >= 80)
			message_combatd(HIR "$N" HIR "Ǳ��������ֻ��" +
					weapon->name() + HIR "����һ���⻪���������ˣ��������¡�"NOR"\n", me);
		else
		if (di >= 30)
			message_combatd(HIR "$N" HIR "Ĭ���������ͼ���" +
					weapon->name() + HIR "����͸��һ�ɹ�â����˸������"NOR"\n", me);
	}

	me->add_temp("apply/attack", skill / 3);
	me->add_temp("apply/dodge", skill / 3);
	me->add_temp("apply/damage", di);
	me->set_temp("powerup", 1);
	me->start_call_out((: call_other,__FILE__, "remove_effect", me, skill / 3, di :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount, int di)
{
	if (me->query_temp("powerup"))
	{
		me->add_temp("apply/attack", -amount);
		me->add_temp("apply/dodge", -amount);
		me->add_temp("apply/damage", -di);
		me->delete_temp("powerup");
		tell_object(me, "����ټ�ׯ������ϣ��������ջص��\n");
	}
}
