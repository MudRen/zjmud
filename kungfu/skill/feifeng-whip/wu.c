// jing.c ����һ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "�ɷ�"ZJBR"����"; }
string *pfm_type() { return ({ "whip", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int damage;
	int i;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (! target || ! me->is_fighting(target))
		return notify_fail("���ɷ����衹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "whip")
		return notify_fail("��ʹ�õ��������ԡ�\n");
		
	if ((int)me->query_skill("feifeng-whip", 1) < 60)
		return notify_fail("��ķɷ�޷�������죬����ʹ�á��ɷ����衹��\n");
				
	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���Ϊ�����ߡ�\n");
			
	if ((int)me->query("neili") < 200)
		return notify_fail("��������������������ʹ�á��ɷ����衹��\n");

	if (me->query_skill_mapped("whip") != "feifeng-whip")
		return notify_fail("������û�м����ɷ�޷�������ʹ�á��ɷ����衹��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "����һ�Σ����е�" + weapon->name() +
	      HIY "����һ��Ȧ�ӣ�����$n" HIY "��"NOR"\n";

	if (random(me->query_skill("whip")) > target->query_skill("force") / 2)
	{
		damage = (int)me->query_skill("force") + (int)me->query_skill("whip");
		damage = damage / 8;
		damage += random(damage);
		me->add("neili", -50);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
					   HIR "$n" HIR "ֻ���û���һ����Ϣ����"
					   "��ӿ��һʱ����ȫ�������������һ����"NOR"\n");
		msg += HIY "\n$N" HIY "��״������" + weapon->name() + HIY +
		       "���ӣ�һ�����й���$n" HIY "��"NOR"\n";
		message_combatd(msg, me, target);

		for (i = 0; i < 3; i++)
		{
			if (! me->is_fighting(target))
				break;
			COMBAT_D->do_attack(me, target, weapon, 0);
		}

		me->start_busy(1 + random(3));
	} else 
	{
		msg += CYN "����$p" CYN "����ܿ�$P" CYN
		       "��һ�У��ƺ���û�з϶���������"NOR"\n";
		me->add("neili", -70);
		me->start_busy(3);
		message_combatd(msg, me, target);
	}

	return 1;
}
