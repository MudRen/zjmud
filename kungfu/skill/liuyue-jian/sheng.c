#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"һ��"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int i;

	if (! target) target = offensive_target(me);

	if (userp(me) && ! me->query("can_perform/liuyue-jian/sheng"))
		return notify_fail("�����ڻ�����ʹ�á���������һ�У�\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("liuyue-jian", 1) < 150)
		return notify_fail("�����Ӱ���½���������죬����ʹ�á���������\n");

	if ((int)me->query_skill("force") < 140)
		return notify_fail("����ڹ�ʵ��̫�û���á���������\n");

	if ((int)me->query("neili", 1) < 300)
		return notify_fail("����������̫��������ʹ�á���������\n");

	if (me->query_skill_mapped("sword") != "liuyue-jian")
		return notify_fail("��û�м�����Ӱ���½�����û���á���������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "����һ�󼲶�������΢��������������ɲ�Ǽ佣â���ǣ�"
	      "����ӵ�кһ������$n"
	      HIW "��"NOR"\n";

	message_combatd(msg, me, target);
	me->add("neili", -100);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->start_busy(1 + random(6));

	return 1;
}

