// jing.c ����һ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"һ��"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (! target || ! me->is_fighting(target))
		return notify_fail("������һ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
		
	if ((int)me->query_skill("duanjia-sword", 1) < 70)
		return notify_fail("��Ķμҽ���������죬����ʹ�á�����һ������\n");
				
	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���Ϊ�����ߡ�\n");
			
	if ((int)me->query("neili") < 300)
		return notify_fail("��������������������ʹ�á�����һ������\n");

	if (me->query_skill_mapped("sword") != "duanjia-sword")
		return notify_fail("������û�м����μҽ�������ʹ�á�����һ������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "һԾ��������һ�������һ�������Ľ���������$n" HIC "��"NOR"\n";

	if (random(me->query_skill("force")) > target->query_skill("force") / 2)
	{
		damage = (int)me->query_skill("force") + (int)me->query_skill("sword");
		damage = damage / 5;
		damage += random(damage);
		me->add("neili", -damage);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
					   HIR "ֻ��$N" HIR "�˽���һ������$n"
					   HIR "��$n" HIR "ֻ��һ����"
					   "�����Ķ�������ͷһ����Ѫ���������"NOR"\n");
		me->start_busy(2);
	} else 
	{
		msg += HIC "����$p" HIC "�͵������һԾ��������$P" HIC "�Ĺ�����Χ��"NOR"\n";
		me->add("neili", -100);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
