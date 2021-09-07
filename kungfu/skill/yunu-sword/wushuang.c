// wushuang.c ��Ů���� ��˫�޶�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me, int a_amount, int d_amount);

string query_name() { return "��˫"ZJBR"�޶�"; }

int perform(object me, object target)
{
	object weapon;
	int damage;
	int skill;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��˫�޶�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("yunu-sword", 1) < 80)
		return notify_fail("�����Ů����������죬����ʹ�á���˫�޶ԡ���\n");
	
	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ�������죬����ʹ�á���˫�޶ԡ���\n");
	
	if ((int)me->query("neili") < 300)
		return notify_fail("�������������\n");

	if ((int)me->query_temp("hsj_wu"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "˫������" + weapon->name() + HIY
	      "����â������һʽ����˫�޶ԡ���Ԧ�����Ҿ��׵���$n"
	      HIY "��̣�"NOR"\n";

	if (random(me->query_skill("sword")) > target->query_skill("parry") / 2)
	{
		me->start_busy(2);

		damage = (int)me->query_skill("sword");
		damage += random(damage / 4);
		me->add("neili", -250);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
					   HIR "$n" HIR "����$N" HIR "��һ������ۣ�ȫȻ��"
					   "���ֵ���һ���֮���Ѿ�����һ���̵���Ѫ�ɽ���" NOR);
	} else
	{
		me->start_busy(3);
		msg += CYN "����$p" CYN "������$P"
		       CYN "����ͼ������һԾ�����˿�ȥ��" NOR;
	}

	message_combatd(msg, me, target);
	return 1;
}
