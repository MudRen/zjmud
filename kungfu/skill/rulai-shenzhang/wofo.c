
#include <ansi.h>

inherit F_SSERVER;

string query_name() { return HIW"�ҷ�"ZJBR"�ȱ�"NOR; }

//int query_pcd() { return 1; }

int perform(object me, object target)
{
	int level;
	string msg;
	int ap, dp;

        level = me->query_skill("rulai-shenzhang", 1);

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�������Ƶġ��ҷ�ȱ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! living(target)||target->query("qi")<10)
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "�黨��Ц������һ�����ҷ�ȱ�����������$n�����Ѩ�����ȥ��"
	      "$n������͸��$N" HIY "���ƵĹ켣��ȴ�޴��ɱܡ�"NOR"\n";

	me->add("neili", -60);
	ap = me->query_skill("strike");
	dp = target->query_skill("force");
	if (ap + random(ap) > dp/100)
	{
		msg += HIR "���$p" HIR "��$P" HIR "һ��ӡ�����ϣ�һʱ��ֻ���ú���������"
		       "���������á�"NOR"\n";
		target->start_busy(level / 10 + 2);
                target->receive_damage("qi", target->query("qi")-1);
                target->receive_wound("qi", target->query("max_qi")/5);
	} else
	{
		msg += CYN "Ȼ��$p" CYN "������񣬺�$P" CYN
		       "΢һ���֣��漴������������Ȼ������$N��������Χ��" NOR;
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
