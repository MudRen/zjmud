// ruo.c ��������

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "unarmed", }); }

int perform(object me, object target)
{
	int level;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ȭ��������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�㲻��ʹ�õ�������\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((level = me->query_skill("kongming-quan", 1)) < 100)
		return notify_fail("��Ŀ���ȭ��������죬����ʹ�á�������������\n");

	if (me->query_skill_mapped("unarmed") != "kongming-quan")
		return notify_fail("����뼤������ȭ������ʹ�á�������������\n");

	if (me->query_skill_prepared("unarmed") != "kongming-quan")
		return notify_fail("������û��׼��ʹ�ÿ���ȭ���޷�ʹ�á�������������\n");

	if (me->query("neili") < 100)
		return notify_fail("�����������������޷�ʹ�á�������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "ʹ����������������˫�����²�������ת���⣬"
	      "���಻������ͼ����$n" HIW "�Ĺ��ơ�"NOR"\n";

	me->add("neili", -50);
	if (random(level) > (int)target->query_skill("parry", 1) / 2)
	{
		msg += HIR "���$p" HIR "��$P" HIR "�ָ���æ���ң�"
		       "���мܲ�����ȫȻ�޷�������"NOR"\n";
		target->start_busy(level / 50 + 2);
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ����"
		       "����㣬ȫ��Ӧ�����硣"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
