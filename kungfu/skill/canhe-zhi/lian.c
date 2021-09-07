// lian.c ����ָ

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����ָ"; }
string *pfm_type() { return ({ "finger", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int skill;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! me->is_fighting(target))
		return notify_fail("������ָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

	skill = me->query_skill("canhe-zhi", 1);

	if (skill < 80)
		return notify_fail("��Ĳκ�ָ��Ϊ����, ����ʹ�á�����ָ����\n");

	if (me->query("neili") < 70)
		return notify_fail("��������������޷����á�����ָ����\n");

	if (me->query_skill_mapped("finger") != "canhe-zhi")
		return notify_fail("��û�м����κ�ָ, ����ʹ�á�����ָ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "��ָ���������һ��ʢ������������ƮƮ�ķ���$n"
	      HIC "��"NOR"\n";

	me->add("neili", -30);
	ap = me->query_skill("finger");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		msg += HIR "���$p" HIR "��$P"
		       HIR "�Ƶ��мܲ�������Ͼ�Թˡ�"NOR"\n";
		target->start_busy(ap / 20 + 2);
	} else
	{
		msg += CYN "����$p" CYN "������$P"
		       CYN "����ͼ������һԾ���㿪����һ�С�"NOR"\n";
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}

