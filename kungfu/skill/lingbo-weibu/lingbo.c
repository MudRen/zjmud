// lingbo.c  �����貨

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"�貨"; }

int perform(object me, object target)
{
	string msg;
	int level;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����貨ֻ����ս���в���ʹ�á�\n");

	if ((level = me->query_skill("lingbo-weibu", 1)) < 120)
		return notify_fail(HIY "����貨΢��������������"NOR"\n");

	if ((int)me->query("neili") < 400)
		return notify_fail(HIY "�������������㡣\n" HIY);

	if (target->is_busy())
		return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ŵ������ɣ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	if( me->query("gender") == "Ů��")
	       msg = HIW "$N" HIW "�����������������������ʮ"
		     "���ԣ�����$n" HIW "��γ��У��Թ��ԵĽ�"
		     "�貨΢\n����ͷ��βѸ���ޱȵ�����һ�Ρ�"
		     "$N" HIW "��������������΢���貨��$n" HIW
		     "ȴ��һ��\nƤëҲմ���ϡ�$N" HIW "�����"
		     "��ң���ַ��ӵ����쾡����"NOR"\n";

	else   msg = HIC "$N" HIC "�����������������������ʮ"
		     "���ԣ�����$n" HIC "��γ��У��Թ��ԵĽ�"
		     "�貨΢\n����ͷ��βѸ���ޱȵ�����һ�Ρ�"
		     "ֻ��$N" HIC "��̬Ʈ�ݣ�Ӱ���ҷɣ�$n" HIC
		     "ȴ��һ��\nƤëҲմ���ϡ�$N" HIC "�����"
		     "��ң���ַ��ӵ����쾡����"NOR"\n";

	if (random(level) > (int)target->query_skill("dodge", 1) / 2)
	{
		msg += HIW "���$p" HIW "��$P" HIW "Χ��ת��ͷ���ۻ���"NOR"\n";
		target->start_busy(level / 16);
		me->add("neili", -100);
	} else
	{
		msg += HIY "���$p" HIY "ֻ����ǿ�����˿�ȥ��"NOR"\n";
		me->add("neili", -50);
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}
