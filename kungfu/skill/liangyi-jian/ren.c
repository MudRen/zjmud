// ren.c  ���ǽ��������ͬ�ʡ�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "���"ZJBR"ͬ��"; }

int perform(object me, object target)
{
	int damage;
	string msg;
	object weapon;
	int ap, dp;

	if (! target) target = offensive_target(me);
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("ûװ����Ҳ��ʹ�����ͬ�ʡ���\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����ͬ�ʡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("liangyi-jian", 1) < 60)
		return notify_fail("�����ǽ���������죬ʹ���������ͬ�ʡ���\n");

	if ((int)me->query_skill("taiji-shengong", 1) < 90)
		return notify_fail("��̫���񹦻�򲻹���ʹ���������ͬ�ʡ���\n");

	if ((int)me->query("max_neili") < 400)
		return notify_fail("��������Ϊ���㣬�޷�����������\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("����������������û�ܽ������ͬ�ʡ�ʹ�꣡\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "���г�����âԾ�������Ⱪ������������ƺ������Ҵ���$n"
	      HIC "��\n$n" HIC "��������ƫ�󣬼�������ת����ֻ��һɲ������ɲʱϮ"
	      "�����ף�\n";
	ap = me->query_skill("sword");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		me->start_busy(2);
		damage = (int)me->query_skill("sword");
		damage = damage / 2 + random(damage / 2);

		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
					   HIC "$n" HIC "��æ��ת��ȴ����$N"
					   HIC "�Ľ�����û����ƫ��" + weapon->name() +
					   HIC "��ʱ��$n" HIC "����������һ��Ѫ����"
					   "ѪӿȪ�����"NOR"\n");
		me->add("neili", -180);
	} else
	{
		me->start_busy(2);
		msg += HIY "����$p" HIY "����һЦ��������ת����Ȼ$P"
		       HIY "�Ľ�ʽͻȻ��չ����$p" HIY "��ǰ\n������"
		       "�����硣ȴ��һ����ë��û�˵���"NOR"\n";
	}
	message_combatd(msg, me, target);
	return 1;
}
