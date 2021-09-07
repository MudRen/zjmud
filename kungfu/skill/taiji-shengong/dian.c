// heal.c

#include <ansi.h>

string query_name() { return "̫��"ZJBR"����"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	if (! target)
		return notify_fail("��Ҫ������Ϊ˭���ˣ�\n");

	if (target == me)
		return notify_fail("��ֻ����������ˡ�\n");

	if (me->is_fighting() || target->is_fighting())
		return notify_fail("ս�����޷��˹����ˣ�\n");

	if (target->query("not_living"))
		return notify_fail("�㲻�ܸ�" + target->name() + "���ˡ�\n");

	if ((int)me->query("max_neili") < 1500)
		return notify_fail("���������ǳ�������˹����ˡ�\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("����������ڲ���������óȻ�й���\n");

	if (target->query("eff_qi") >= target->query("max_qi") &&
	    target->query("eff_jing") >= target->query("max_jing"))
		return notify_fail("�Է�û�����ˣ�����Ҫ�������ơ�\n");

	message_combatd(HIW "ֻ��$N" HIW "˫��ʳָ��Ĵָ���ã��ɡ����쾢���ƣ�"
			    "��ʳָָ�����$n" HIW "�������ִ��ġ���Ծ�ϡ�����"
			    "��\n�ڹ���΢΢�ڶ�����" NOR + HIY "�����쾢����"
			    "Ծ�ϡ�" NOR + HIW "ʹ�������������¶���֮��Ҳ�ܻ�"
			    "��Ƭ�̡�������\n\n"
			    "��һ�ᣬ$n" HIW "��ͷ��ð�������飬ͷ��ð������"
			    "�������ۡ���һ���³���Ѫ����ɫ��ʱ������ˡ�\n"
			    NOR, me, target);

	me->add("neili", -800);
	me->receive_damage("qi", 100);
	me->receive_damage("jing", 50);

	target->receive_curing("qi", 100 + (int) me->query_skill("force") +
					   (int) me->query_skill("taiji-shengong", 1) * 3);

	if (target->query("qi") <= 0) target->set("qi", 1);
	target->receive_curing("jing", 100 + (int) me->query_skill("force") / 3 +
					     (int) me->query_skill("taiji-shengong", 1));

	if (target->query("jing") <= 0) target->set("jing", 1);
	if (! target->is_busy())
		target->stary_busy(2);

	message_vision("\n$N��Ŀڤ������ʼ�˹���Ϣ��\n", me);
	me->start_busy(10);

	return 1;
}
