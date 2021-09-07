#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);

string query_name() { return "����"ZJBR"��Ԫ"; }

int perform(object me, object target)
{
	object weapon;  
	string msg;
	int count, skill;

	if ((int)me->query_temp("gui_yuan"))
		return notify_fail("���Ѿ����𡸾�����Ԫ���ˡ�\n");

	if ((int)me->query_skill("shexing-lifan", 1) < 150)
		return notify_fail("��Ļ�������������죬����ʩչ���������\n");

	if ((int)me->query_dex() < 30)
		return notify_fail("���������ʹ�á�������Ԫ��������\n");

	if ((int)me->query_skill("force", 1) < 150)
		return notify_fail("����ڹ���򲻹�������ʩչ���������\n");

	if ((int)me->query_skill("dodge", 1) < 150)
		return notify_fail("����Ṧ��Ϊ����������ʹ�ô��������\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("���������Ϊ����ʹ�á�������Ԫ����\n");

	if ((int)me->query("neili") < 250)
		return notify_fail("���ʱ���������㣡\n");

	msg = HIW "$N" HIW "�������������˫�۹���һ���죬����һչ����"
		  "���˶�ʱ���Ʈ���ٶȱ���쳣���ݡ�"NOR"\n";
	
	message_combatd(msg, me, target);
	skill = me->query_skill("shexing-lifan", 1);

	count = skill / 30;

	if (me->is_fighting())
		me->start_busy(2);

	//me->add_temp("str", count);
	me->add_temp("dex", count);
	me->set_temp("gui_yuan", 1);
	me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

	me->add("neili", -200);
	return 1;
}

void remove_effect(object me, int amount, int amount1)
{
	if ((int)me->query_temp("gui_yuan"))
	{
		//me->add_temp("str", -amount);
		me->add_temp("dex", -amount);
		me->delete_temp("gui_yuan");
		tell_object(me, "��ġ�������Ԫ���˹���ϣ��������ջص��\n");
	}
}
