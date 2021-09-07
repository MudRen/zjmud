// jie.c ��ɽ����������ʽ��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����ʽ"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	int level;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ɽ����������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((level = me->query_skill("huashan-sword", 1)) < 60)
		return notify_fail("��Ļ�ɽ����������죬����ʹ�á�����ʽ����\n");

	if (me->query("neili") < 80)
		return notify_fail("�����������������޷�ʹ�á�����ʽ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "����$N" HIW "����һ�գ�ʹ����ɽ��������֮"
	      "������ʽ����ת��֮�������޷죬\nһ���ȳ�������"
	      "ԴԴ��к�������Ծ̲����������ѸȻ����$n"
	      HIW "��"NOR"\n";

	me->add("neili", -50);
	if (random(level) > (int)target->query_skill("parry", 1) / 2)
	{
		msg += HIR "���$p" HIR "�᲻��������������"
		       "������һʱ���޷����֣�"NOR"\n";
		target->start_busy(level / 22 + 2);
	} else
	{
		if (objectp(weapon = target->query_temp("weapon")))
			msg += CYN "����$p" CYN "ʶ����$P" CYN "�����⣬"
			       "�Թ˽����е�" + weapon->name() +
			       CYN "���һ�Ź⻨��$P"
			       CYN "һ��֮����Ҳ������ȥ��"NOR"\n";
		else
			msg += CYN "����$p" CYN "˫�ִ�����ģ���$P"
			       CYN "������һһ�ܿ���"NOR"\n";

		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}
