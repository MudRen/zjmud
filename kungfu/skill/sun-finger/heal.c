// heal.c

#include <ansi.h>

string query_name() { return "һ��"ZJBR"����"; }

int perform(object me, object target)
{
	string force;

	if (! target)
		return notify_fail("��Ҫ������Ϊ˭���ˣ�\n");

	if (target == me)
		return notify_fail("��ֻ����������ˡ�\n");

	if (me->is_fighting() || target->is_fighting())
		return notify_fail("ս�����޷��˹����ˣ�\n");

	if (target->query("not_living"))
		return notify_fail("�㲻�ܸ�" + target->name() + "���ˡ�\n");

	if (! (force = me->query_skill_mapped("force")))
		return notify_fail("����뼤��һ���ڹ������˹����ˡ�\n");

	if ((int)me->query("max_neili") < 1500)
		return notify_fail("���������ǳ�������˹����ˡ�\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("����������ڲ���������óȻ�й���\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("��������ڲ�������ҪóȻ�й���\n");

	if ((int)me->query("jing") < 100)
		return notify_fail("��ľ����ڲ�������ҪóȻ�й���\n");

	if (target->query("eff_qi") >= target->query("max_qi") &&
	    target->query("eff_jing") >= target->query("max_jing"))
		return notify_fail("�Է�û�����ˣ�����Ҫ�������ơ�\n");

	message_combatd(HIY "$NĬ��" + to_chinese(force) +
			"��ʩչ��һ��ָ����˲ʱ�����$n����"
			"��ҪѨ....\n\n" HIC
			"$N����һ������ͷ������ð������$n"
			"���ۡ���һ���³���Ѫ����ɫ��ʱ����"
			"���ˡ�"NOR"\n", me, target);

	me->add("neili", -1000);
	me->receive_damage("qi", 150);
	me->receive_damage("jing", 80);

	target->receive_curing("qi", 100 + (int) me->query_skill("force") +
					   (int) me->query_skill("sun_finger", 1) * 3);

	if (target->query("qi") <= 0) target->set("qi", 1);
	target->receive_curing("jing", 100 + (int) me->query_skill("force") / 3 +
					   (int) me->query_skill("sun_finger", 1));

	if (target->query("jing") <= 0) target->set("jing", 1);
	target->stary_busy(2);

	message_vision("\n$N��Ŀڤ������ʼ�˹���Ϣ��\n", me);
	me->start_busy(10);

	return 1;
}
