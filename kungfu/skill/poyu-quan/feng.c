// feng.c ����ȭ������֡�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "�����"; }
string *pfm_type() { return ({ "cuff", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ȭ������֡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if( objectp(me->query_temp("weapon")) )
		return notify_fail("��������ʹ�á�����֡���\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");
		
	if ((int)me->query_skill("poyu-quan", 1) < 120)
		return notify_fail("�������ȭ��������죬����ʹ�á�����֡���\n");

	if (me->query_skill_mapped("cuff") != "poyu-quan")
		return notify_fail("��û�м�������ȭΪȭ�����޷�ʹ�á�����֡���\n");

	if (me->query_skill_prepared("cuff") != "poyu-quan")
		return notify_fail("������û��׼��ʹ������ȭ���޷�ʹ�á�����֡���\n");


	if (me->query("neili") < 500)
		return notify_fail("�����������������޷�ʹ�á�����֡���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "ֻ��$N" HIC "������̽����ȭ쬵�һ�����Ʒ���"
	      "�ʹ���������������ȭ���ľ���֮һ������֡���"NOR"\n";

	me->add("neili", -30);
	if (random(me->query_skill("cuff")) > (int)target->query_skill("force") / 2)
	{
		msg += HIR "���$p" HIR "�����мܣ�һʱȴ����"
		       "�������ã���$P" HIR "��ס����һ������ʱ����"
		       "���ȣ��������������Ȧ�ӡ�"NOR"\n";
		target->start_busy((int)me->query_skill("cuff") / 50 +1);
	} else
	{
		msg += CYN "����$p" CYN "����һ�ܣ�Ӳ��������$P"
		       CYN "��һȭ��"NOR"\n";
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}
