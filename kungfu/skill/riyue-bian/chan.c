// chan.c ���±޷������ơ���

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }
string *pfm_type() { return ({ "whip", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("ǣ�ƹ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    weapon->query("skill_type") != "whip")
		return notify_fail("��û�����ű��ӡ�\n");
		
	if (me->query("neili") < 80)
		return notify_fail("�����������������޷�ʩչ�����ơ�����\n");

	if (me->query_skill_mapped("whip") != "riyue-bian")
		return notify_fail("��û�м������±޷����޷�ʩչ�����ơ�����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "ʹ�����±޷������ơ���������������ͼ��$n"
	      HIC "��ȫ�����������\n";

	ap = me->query_skill("whip");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR "���$p" HIR "��$P" HIR "���˸����ֲ�����"NOR"\n";
	target->start_busy((int)me->query_skill("riyue-bian", 1) / 20 + 2);
		target->start_busy((int)me->query_skill("riyue-bian") / 20 + 2);
	} else
	{
		msg += CYN "����$p" CYN "������$P"
		       CYN "����ͼ��С��Ӧ�ԣ���û���ϵ���"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
