// guanghua.c

#include <ansi.h>
#include <combat.h>

#define GUANG "��" HIY "�⻪��" NOR "��"

inherit F_SSERVER;

string query_name() { return "�⻪��"; }

int perform(object me, object target)
{
	object weapon;
	int damage, skill;
	string msg;

	if (! target) target = offensive_target(me);

	skill = me->query_skill("shenghuo-ling",1);

	if (! (me->is_fighting()))
		return notify_fail(GUANG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")))
		return notify_fail("��ʹ�õı������ԣ�����ʹ��ʥ���֮" GUANG "��\n");

	if (skill < 140)
		return notify_fail("���ʥ����ȼ�����, ����ʹ��ʥ���֮" GUANG "��\n");

	if (me->query("max_neili") < 1500)
		return notify_fail("���������Ϊ���㣬����ʹ��ʥ���֮" GUANG "��\n");

	if (me->query("neili") < 300)
		return notify_fail("�����������������ʹ��ʥ���֮" GUANG "��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "����һ������ʹ��ʥ���֮�⻪�����"
	      + weapon->name() + NOR + HIY "������ɣ��ó���������"
	      "â����$n" HIY "����������"NOR"\n";

	if (random(me->query_skill("force")) > target->query_skill("force") / 2)
	{
		damage = skill / 3 + me->query_skill("force") / 3;
		damage += random(damage);
		me->add("neili", -200);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
		       HIR "$n" HIR "ֻ�������â����ǵ�ϯ�������"
		       "��ȫ�޷��赲����ʱֻ��ȫ������ʹ����Ѫ��"
		       "��������"NOR"\n");

		me->start_busy(2);
	} else
	{
		msg += CYN "����$n" CYN "��׼$N" CYN "���������͵���"
		       "ǰһԾ��������$N" CYN "�Ĺ�����Χ��"NOR"\n";
		me->add("neili", -50);
		me->start_busy(4);
	}
	message_combatd(msg, me, target);
	return 1;
}
