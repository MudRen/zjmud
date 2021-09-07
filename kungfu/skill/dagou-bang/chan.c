// chan.c �򹷰����������־�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }
string *pfm_type() { return ({ "staff", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;

	if (! target ) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�򹷰����������־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	if ((int)me->query_skill("dagou-bang", 1) < 70)
		return notify_fail("��Ĵ򹷰���������죬����ʹ�á������־���\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ�������񣬲���ʹ�á������־���\n");

	if (me->query("neili") < 100)
		return notify_fail("�����ڵ������������޷�ʹ�á������־���\n");

	if (me->query_skill_mapped("staff") != "dagou-bang")
		return notify_fail("��û�м����򹷰���������ʹ�á������־���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "ʹ���򹷰����������־�����ͷ�ڵ�"
	      "�����㣬���಻��������$n" HIG "��С�Ⱥͽ��ס�\n";

	me->add("neili", -50);
	ap = me->query_skill("staff");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR " ���$p" HIR "��$P" HIR "���ı�����ͣ����æ���ң�"NOR"\n";
		target->start_busy((int)me->query_skill("dagou-bang") / 20);
	} else
	{
		msg += "����$p" HIG "������$P" HIG
		       "����ͼ���򶨽��У�һ˿���ҡ�"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
