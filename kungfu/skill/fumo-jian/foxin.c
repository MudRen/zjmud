// foxin.c ���Ľ�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "���Ľ�"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����Ľ���ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

	if (me->query_skill("fumo-jian", 1) < 135)
		return notify_fail("��ķ�ħ������Ϊ������Ŀǰ����ʹ�÷��Ľ���\n");

	if (me->query("neili") < 250)
		return notify_fail("�����������������ʹ�÷��Ľ���\n");

	if (me->query_skill_mapped("sword") != "fumo-jian")
		return notify_fail("��û�м�����Ħ��������ʹ�÷��Ľ���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "����" + weapon->name() +
	      HIC "�����������ס��$n" + HIC "����·����"
	      "��һ��������������������$p" HIC "��"NOR"\n";

	ap = me->query_skill("sword");
	dp = target->query_skill("parry");

	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap);
		me->add("neili", -150);
		me->start_busy(1);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
					   HIR "���$p" HIR "һ����������$P" HIR
					   "һ���������ţ���Ϣ���緭������һ"
					   "�㣬����ҡҡ��׹��"NOR"\n");
	} else
	{
		me->add("neili", -60);
		me->start_busy(3);
		msg += CYN "����$p" CYN "�������ң����ȵĽ�$P"
		       CYN "����һһ���⡣"NOR"\n";
	}

	message_combatd(msg, me, target);

	return 1;
}

