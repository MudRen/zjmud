// muyeyingyang.c ��Ұӥ��

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "��Ұ"ZJBR"ӥ��"; }

int perform(object me, object target)
{
      int num;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��Ұӥ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_str() < 30)
		return notify_fail("���������,����ʹ����Ұӥ�\n");

	if ((int)me->query_skill("sougu",1) < 150)
		return notify_fail("����ѹ�ӥצ����Ϊ����,Ŀǰ������ʹ����Ұӥ�\n");

	if ((int)me->query("neili") < 800)
		return notify_fail("���������ڲ���, ����ʹ����Ұӥ�\n");

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ʹ���ѹ�ӥצ����������Ұӥ���˫צ���ץ��$n"
	      HIY "��ȫ��ҪѨ��"NOR"\n";

	if (random(me->query("combat_exp"))/10000 * me->query_skill("sougu", 1) > (int)target->query("combat_exp") / 20000 * target->query_skill("dodge", 1) )
	{
		msg += HIR "���$p" HIR "��$P" HIR "ץסҪѨ����ʱ�������ã�"NOR"\n";
            num = me->query_skill("sougu", 1) / 30;
            if (num>10) num=10;
		target->start_busy( num );
		me->add("neili", -150);
	} else
	{
		msg += HIG "����$p" HIG "������$P" HIG "����ͼ����û���ϵ���"NOR"\n";
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
