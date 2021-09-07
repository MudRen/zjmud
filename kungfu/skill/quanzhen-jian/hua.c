// hua.c ȫ�潣 һ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "������"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int count;

	if (userp(me) && ! me->query("can_perform/quanzhen-jian/hua"))
		return notify_fail("�㻹����ʹ��һ�������塣\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("һ��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("quanzhen-jian", 1) < 100)
		return notify_fail("���ȫ�潣��������죬����ʹ��һ�������塣\n");

	if ((int)me->query_skill("xiantian-gong", 1) < 100)
		return notify_fail("������칦������죬�޷����һ��������İ��ء�\n");

	if ((int)me->query("neili", 1) < 500)
		return notify_fail("��������������������ʹ��һ�������塣\n");

	if (me->query_skill_mapped("sword") != "quanzhen-jian")
		return notify_fail("��û�м���ȫ�潣��������ʹ��һ�������塣\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "վ������������ȫȻ�˵����ϣ�һ�����ȣ�" +
	      weapon->name() + HIC "��" HIM "��â" HIC "��ҫ��������"
	      "����������$n��"NOR"\n";

	ap = me->query_skill("xiantian-gong", 1) + me->query_skill("sword");
	dp = target->query_skill("force") + target->query_skill("parry", 1) * 2 / 3;
	if (dp < 1) dp = 1;
	if (ap / 2 + random(ap) > dp)
	{
		me->start_busy(3);
		if (! target->is_busy())
			target->start_busy(1);
		me->add("neili", -200);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, ap / 2 + random(ap / 2), 66,
					   HIR "$n" HIR "һ���ҽУ�������������"
					   "��ʱð������Ѫ����"NOR"\n");
		message_combatd(msg, me, target);
		if (ap / 3 + random(ap) > dp)
		{
			if (! target->is_busy())
				target->start_busy(1);
			count = me->query_skill("xiantian-gong", 1) / 5;
			me->add_temp("apply/attack", count);
			message_combatd(HIC "$N" HIC "����$n" HIC
					"����һ��֮��������������"
					"��ǰԾ������ৡ�����������"NOR"\n",
					me, target);
			COMBAT_D->do_attack(me, target, weapon);
			COMBAT_D->do_attack(me, target, weapon);
			COMBAT_D->do_attack(me, target, weapon);
			me->add_temp("apply/attack", -count);
		}
	} else
	{
		me->start_busy(2);
		msg += CYN "����$n" CYN "������$N" CYN "����ͼ��бԾ�ܿ���"NOR"\n";
		message_combatd(msg, me, target);
	}

	return 1;
}
