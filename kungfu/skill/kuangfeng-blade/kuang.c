// kuang.c -������ʮһʽ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "���"ZJBR"����"; }

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á�����ʮһʽ����\n");

	if ((int)me->query_skill("kuangfeng-blade", 1) < 70)
		return notify_fail("��Ŀǰ������ʹ����������ʮһʽ����\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	me->add("neili", -60);
	msg = HIC "$N" HIC "��ȻһЦ�����Ϳ�ݾ��׵ĵ�����Ȼ��"
	      "�ø���������������һ˲֮�䣬$N" HIC "��������ʮ"
	      "һ����\n�������ŷ磬���ﺬ�ŵ�Ӱ��$n"
	      HIC "ֻ����������ֹͣ�ˣ�"NOR"\n";
	me->start_busy(2);

	ap = me->query_skill("blade");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		me->start_busy(2);
		damage = ap / 2 + random(ap / 2);

		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40, 
					   HIR "ֻ��$n" HIR "�ѱ�$N" HIR
					   "�е����������Ѫ�������ȫ�����������"NOR"\n");
	} else
	{
		me->start_busy(1);
		msg += HIC "����$p" HIC "��æ����㿪��ʹ$P"
		       HIC "����û�еóѡ�"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
