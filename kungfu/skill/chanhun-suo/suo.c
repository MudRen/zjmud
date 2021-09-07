#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "�����"; }
string *pfm_type() { return ({ "whip", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "whip")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("chanhun-suo", 1) < 50)
		return notify_fail("��Ĳ���������̫ǳ��ʹ���˾������ꡣ\n");

	if (me->query_skill_mapped("whip") != "chanhun-suo")
		return notify_fail("��û�м�������������ʹ���˾������ꡣ\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹���ʹ���˾������ꡣ\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "һ����Ц��ʹ�����������꣬����������Ӱ����$n"
	      HIR "ȫȫ���֣�"NOR"\n";

	ap = me->query_skill("whip");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIY "���$n" HIY "������ɽ������Ĺ������˸����ֲ�����������������ȫ�޷�����"NOR"\n";
		target->start_busy((int)me->query_skill("whip") / 22 + 1);
		me->start_busy(1 + random(2));
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ������һ�ݣ��ӿ��˹��ơ���"NOR"\n";
		me->start_busy(4);
	}
	message_combatd(msg, me, target);
	return 1;
}
