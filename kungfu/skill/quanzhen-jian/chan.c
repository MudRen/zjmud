// chan.c ȫ�潣���������־�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	int level;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("ȫ�潣���������־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((level = me->query_skill("quanzhen-jian", 1)) < 80)
		return notify_fail("���ȫ�潣��������죬����ʹ�á������־���\n");

	if (me->query_skill_mapped("sword") != "quanzhen-jian")
		return notify_fail("����뼤��ȫ�潣������ʹ�á������־���\n");

	if (me->query("neili") < 60)
		return notify_fail("�����������������޷�ʹ�á������־���\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ʹ��ȫ�潣���������־��������´̣�" +
	      weapon->name() + HIY "�����������������������������˷�"
	      "Ϯ��$n" HIY "��"NOR"\n";

	me->add("neili", -45);
	ap = me->query_skill("sword");
	dp = target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR "$p" HIR "ֻ����$P" HIR
		       "����ѹ��һ��ǿ��һ�㣬ֻ��ʹ����������˹��ֵ���"NOR"\n";
		target->start_busy(level / 28 + 2);
	} else
	{
		msg += CYN "$p" CYN "��$P" CYN "���з����Ͻ�������С��Ի���"
		       "�ڹ�Ϊ����������Ĳ��$P" CYN "�����У���¶���������"NOR"\n";
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}

