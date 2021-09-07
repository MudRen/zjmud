#include <ansi.h>
#include <combat.h>

#define MAN "��" HIY "��������" NOR "��"

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "cuff", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(MAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail(MAN "ֻ�ܿ���ʩչ��\n");

	if ((int)me->query_skill("jinyu-quan", 1) < 80)
		return notify_fail("��Ľ���ȭ��������죬����ʩչ" MAN "��\n");

	if (me->query_skill_mapped("cuff") != "jinyu-quan")
		return notify_fail("��û�м�������ȭ��������ʩչ" MAN "��\n");

	if (me->query_skill_prepared("cuff") != "jinyu-quan")
		return notify_fail("��û��׼������ȭ��������ʩչ" MAN "��\n");

	if (me->query("neili") < 200)
		return notify_fail("�����ڵ���������������ʩչ" MAN "��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "˫ȭ�׷ɣ�������磬��ʱ�ó�һƬȭӰ���ƺ�$n"
	      HIY"��ȫ����ȭӰ�����֡�"NOR"\n";

	if (random(me->query_skill("cuff")) > target->query_skill("dodge") / 2)
	{
		me->start_busy(2);
		damage = me->query_skill("cuff");
		damage = damage / 2 + random(damage / 2);
		me->add("neili", -150);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
					   HIR "���ֻ�����������顱�������죬$p"
					   HIR "ǰ�ر�$P" HIR "������ȭ����ʱŻ��"
					   "һ����Ѫ��"NOR"\n");
	} else
	{
		me->start_busy(3);
		me->add("neili", -50);
		msg += CYN "����$p" CYN "ʶ����$P"
		       CYN "��һ�У�ббһԾ�ܿ���"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}

