// you.c ��Ůȭ-��Ĺ�ľ�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "��Ĺ"ZJBR"�ľ�"; }
string *pfm_type() { return ({ "unarmed", }); }

int perform(object me, object target)
{
	int damage;
	string msg;
	string pmsg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��Ĺ�ľ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("meinv-quan", 1) < 80)
		return notify_fail("�����Ůȭ���𲻹�������ʹ�ù�Ĺ�ľӡ�\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���δ��죬�����������˵С�\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("��������������������ʹ�ù�Ĺ�ľӡ�\n");

	if (me->query_skill_mapped("unarmed") != "meinv-quan")
		return notify_fail("��û�м�����Ůȭ��������ʩչ��Ĺ�ľӡ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "����֧�ã���������ӳ�����̾һ����ʹ"
	      "������Ĺ�ľӡ���һ�����ּ���֮�⡣"NOR"\n";

	if (random(me->query_skill("force")) > target->query_skill("force") / 2)
	{
		me->start_busy(random(3));

		damage = (int)me->query_skill("unarmed");
		damage = damage / 2 + random(damage / 2);

		me->add("neili", -100);

		if (damage < 30)
			pmsg = HIY "���$n" HIY "��$N��"
			       HIY "��һ�����ƺ�һ����"NOR"\n";
		else if(damage < 55)
			pmsg = HIY "���$n" HIY "��$N"
			       HIY "������һ���������ڡ����˳�������"NOR"\n";
		else if (damage < 80)
			pmsg = HIR "���$n" HIR "��$N"
			       HIR "������һ�����ؿ������ܵ�һ����"
			       "������ѪΪ֮һ�ϣ�"NOR"\n";
		else
			pmsg = RED "���$n" RED "��$N" RED
			       "������һ������ǰһ�ڣ�������Ѫ���ڣ�"
			       "���������¯һ�㣡"NOR"\n";
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30, pmsg);
	} else
	{
		me->start_busy(3);
		msg += CYN "����$p" CYN "������$P" CYN
		       "����ͼ������̩ɽ��̧��һ�ܸ���$P"
		       CYN "��һȭ��"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
