// juemi.c ��ؾ���
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
string query_name() { return "���"ZJBR"����"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ؾ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (me->query_skill("never-defeated", 1) < 120)
		return notify_fail("��Ĳ����񹦻�������죬����ʹ����ؾ���\n");

	if (! objectp(weapon = me->query_temp("weapon")))
		return notify_fail("������ֱֳ��в���ʩչ��ؾ���\n");

	if (me->query("neili") < 200)
		return notify_fail("�����������������ʹ����ؾ���\n");
 
       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "������˼�������Ȼһ�����е�" + weapon->name() +
	      HIC "��Ѹ���ޱȵ�ɨ��$n" HIC "���仯����֮��������˼�飡"NOR"\n";
 
	ap = me->query_skill("never-defeated", 1) * 3 / 2 + me->query("int") * 20 +
	     me->query_skill("martial-cognize", 1);
	dp = target->query_skill("dodge") + target->query("dex") * 20 +
	     target->query_skill("martial-cognize", 1);

	me->start_busy(2);
	me->add("neili", -50);
	if (ap / 2 + random(ap) < dp)
	{
		msg += HIG "ֻ��$n" HIG "�������ţ�ֻ������һ�����Ͷ����$N"
		       HIG "��һ����"NOR"\n";
	} else
	{
		me->add("neili",-70);
		damage = ap / 2 + random(ap / 3);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
					   HIR "$n" HIR "��æ�񵲣�������һ��ʵ���ǹ���Ī"
					   "�⣬������ĥ��͸����ʱ����$P" HIR "���ش���"NOR"\n");
	}

	message_combatd(msg, me, target);
	return 1;
}
