// wang.c ���޵���

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	object weapon;
	int level;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����޵�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon"))
		return notify_fail("�������ֲ���ʩչ�����޵�������\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((level = me->query_skill("tianluo-diwang", 1)) < 60)
		return notify_fail("������޵�����������죬����ʹ�þ��С�\n");

	if (me->query_skill_mapped("strike") != "tianluo-diwang")
		return notify_fail("����뼤�����޵����Ʒ�����ʹ�þ��С�\n");

	if (me->query("neili") < 60)
		return notify_fail("�����������������޷�ʹ�á����޵�������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "˫��������û���������Ӱ����$n" HIG "�������֡�"NOR"\n";

	me->add("neili", -35);
	if (random(level) > (int)target->query_skill("dodge", 1) / 2)
	{
		msg += HIR "���$p" HIR "��$P" HIR "ѹ�Ƶ����Է�����"
		       "ֻ�ܽ����ֵ���"NOR"\n";
		target->start_busy(level / 16 + 2);
	} else
	{
		msg += CYN "����$p" CYN "����һ����Ծ��$P" CYN "������"
		       "�����ķ�Χ��"NOR"\n";
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}
