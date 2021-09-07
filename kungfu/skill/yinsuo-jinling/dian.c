// dian.c

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"��Ѩ"; }
string *pfm_type() { return ({ "whip", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��Ѩ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    weapon->query("skill_type") != "whip")
		return notify_fail("����������ԣ��޷���Ѩ��\n");

	if (me->query_skill("yinsuo-jinling", 1) < 50)
		return notify_fail("����������弶�𲻹����޷���Ѩ��\n");

	if (me->query("neili") < 50)
		return notify_fail("�����������������޷���Ѩ��\n");

	if (me->query_skill_mapped("whip") != "yinsuo-jinling")
		return notify_fail("��û�м����������壬�޷���Ѩ��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "����һ��������" + weapon->name() +
	      HIY "�������£��ֵ�$n" HIY "���ϡ�ӭ��"
	      "�������������������С�����Ѩ����\n������"
	      "��Ѩ����֮�졢��λ֮׼��ʵ�����ֺ�����\n";

	ap = me->query_skill("whip");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR "$n" HIR "ֻ��$N" + weapon->name() +
		       HIR "�����������죬���䲻��ȴ��"
		       "ʮ�ֹ��죬�������ҡ�ǣ�һ��\n����"
		       "�������е�����ţ�ȫ��̱����������"
		       "�����ã�"NOR"\n";
		target->start_busy((int)me->query_skill("yinsuo-jinling") / 20 + 2);
	} else
	{
		msg += CYN "����$p" CYN "������$P"
		       CYN "����ͼ��б������������"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
