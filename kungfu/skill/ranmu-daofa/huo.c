#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"ʴ��"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	int ap, dp;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("������ʴ�¡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("ranmu-daofa", 1) < 180)
		return notify_fail("���ȼľ����������죬����ʹ�û���ʴ�¡�\n");

	if ((int)me->query_skill("force") < 250)
		return notify_fail("����ڹ���򲻹�������ʹ�û���ʴ�¡�\n");

	if ((int)me->query("max_neili") < 3000 )
		return notify_fail("���������Ϊ̫��������ʹ�û���ʴ�¡�\n");

	if ((int)me->query("neili") < 600 )
		return notify_fail("����������̫��������ʹ�û���ʴ�¡�\n");

	if (me->query_skill_mapped("blade") != "ranmu-daofa")
		return notify_fail("��û�м���ȼľ����������ʩչ����ʴ�¡�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "ֻ��$N" HIR "����" + weapon->name() + HIR "һ���������ʱ����"
			"�������棬��ԡ������һ��ϯ��$n" HIR "ȫ��"NOR"\n";

	me->start_busy(2 + random(2));
	ap = me->query_skill("ranmu-daofa", 1) + me->query_skill("force");
	dp = target->query_skill("force", 1) + target->query_skill("force");

	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 3 + random(ap / 3);
		me->add("neili", -400);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 42,
					   RED "ֻ��һ�ɽ�����$n" RED "���������ѱ�"
					   "$P" RED "�⾫������һ"
					   "�����У���Ѫ�ɽ�������"NOR"\n");
	} else
	{
		msg += CYN "$p" CYN "��$P" CYN "�������ڣ����ҵֵ�����æбԾ�ܿ���"NOR"\n";
		me->add("neili", -200);
	}
	message_combatd(msg, me, target);

	return 1;
}
