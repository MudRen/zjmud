// pai.c ����ʮ���ơ���ɽ������

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "��ɽ"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	int level;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ʮ������ɽ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon"))
		return notify_fail("�������ֲ���ʩչ��ɽ������\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((level = me->query_skill("dragon-strike", 1)) < 120)
		return notify_fail("��Ľ���ʮ���Ʋ�����죬����ʹ����ɽ������\n");

	if (me->query_skill_mapped("strike") != "dragon-strike")
		return notify_fail("����뼤������ʮ���Ʋ���ʹ����ɽ������\n");

	if (me->query("neili") < 100)
		return notify_fail("�����������������޷�ʹ����ɽ������\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "���һ������ǰ̤һ�󲽣�����ŭ�ӣ�һ���ۻ��ޱȵ�����"
	      "��ϯ���ȥ����̤һ�󲽣�\n�����漴�ݳ��������Ҷ���裬����"
	      "�з���֮����ѹ��$n" HIR "��"NOR"\n";

	me->add("neili", -60);
	ap = me->query_skill("strike");
	dp = target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR "���$p" HIR "��$P" HIR "�������壬һʱ��ֻ���ú���������"
		       "ȫ�����ް������������"NOR"\n";
		target->start_busy(level / 21 + 2);
	} else
	{
		msg += CYN "Ȼ��$p" CYN "������񣬺�$P" CYN
		       "΢һ���֣��漴������������Ȼ���������������Χ��"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
