// san.c  ��Ůɢ��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "��Ů"ZJBR"ɢ��"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int i;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����Ůɢ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("tianyu-qijian", 1) < 100)
		return notify_fail("��������潣������죬����ʹ�á�\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ�ʵ��̫�û���á���Ůɢ������\n");

	if ((int)me->query("neili", 1) < 300)
		return notify_fail("����������̫��������ʹ�á���Ůɢ������\n");

	if (me->query_skill_mapped("sword") != "tianyu-qijian")
		return notify_fail("��û�м��������潣��û���á���Ůɢ������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "����Ϣ�������󼲶������ǧ�������������ǵط���$n"
	      HIY "��"NOR"\n";

	message_combatd(msg, me, target);
	me->add("neili", -100);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->start_busy(1 + random(5));

	return 1;
}
