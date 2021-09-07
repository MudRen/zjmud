// fugu.c ��������

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���������ǡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ���������ǡ���\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((int)me->query_skill("tianshan-zhang", 1) < 80)
		return notify_fail("�����ɽ�ȷ�������죬����ʹ�á��������ǡ���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "�����Ц�����е�" + weapon->name() +
	      HIG "����Ӱ��һ��Ϯ��$n��"NOR"\n";

	ap = me->query_skill("staff");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR "���$p" HIR "��$P" HIR "�ŵþ���ʧ�룬"
		       "һʱ����æ���ң�����Ӧ�ԣ�"NOR"\n";
		target->start_busy((int)me->query_skill("staff", 1) / 25 + 2);
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ��"
		       "����һ�ˣ���ȥ��$P" CYN "��׷����"NOR"\n";
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}
