// ding.c ȫ�潣 ������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "������"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("quanzhen-jian", 1) < 50)
		return notify_fail("���ȫ�潣��������죬����ʹ�ö����롣\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹�������ʹ�ö����롣\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("����������̫��������ʹ�ö����롣\n");

	if (me->query_skill_mapped("sword") != "quanzhen-jian")
		return notify_fail("��û�м���ȫ�潣��������ʹ�ö����롣\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "�������Ҽ�����������������"
	      "������һʽ�������롹бб�̳���"NOR"\n";

	me->start_busy(2);
	if (random(me->query_skill("force")) > target->query_skill("force") / 2)
	{
		damage = (int)me->query_skill("quanzhen-jian", 1) +
			 (int)me->query_skill("force", 1) +
			 (int)me->query_skill("xiantian-gong", 1);

		damage = damage / 3 + random(damage / 3);

		me->add("neili", -100);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
					   HIR "$n" HIR "����$N" HIR "������ǧ����һ��������"
					   "֪����мܣ���ʱ�����ش���"NOR"\n");
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ��бԾ�ܿ���"NOR"\n";
		me->add("neili", -30);
	}
	message_combatd(msg, me, target);

	return 1;
}
