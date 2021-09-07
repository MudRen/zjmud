// suoming.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("������������ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

	if (me->query_skill("xiuluo-dao", 1) < 135)
		return notify_fail("������޵�����Ϊ������Ŀǰ����ʹ������������\n");

	if (me->query("neili") < 250)
		return notify_fail("�����������������ʹ������������\n");

	if (me->query_skill_mapped("blade") != "xiuluo-dao")
		return notify_fail("��û�м������޵���������ʹ������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "����ɱ����ʢ��һ�����е�" + weapon->name() +
	      HIC "����������$n" + HIC "���Ź�ס��"NOR"\n";

	ap = me->query_skill("blade");
	dp = target->query_skill("parry");

	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap / 3);
		me->add("neili", -180);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
					   HIR "������$p" HIR "�ҽ�������һ����Ѫ����" HIR
					   "���׵ĵ����н�����"NOR"\n");
	} else
	{
		me->add("neili", -60);
		me->start_busy(3);
		msg += CYN "����$p" CYN "�����ֿ죬ֻ����������������һ��"
		       CYN "������$p" CYN "��$P" CYN "����ʽȫ��������"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
