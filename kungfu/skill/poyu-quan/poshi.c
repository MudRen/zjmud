// poshi.c ��ʯһ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "��ʯ"ZJBR"һ��"; }
string *pfm_type() { return ({ "cuff", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int ap, dp;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (! target || ! me->is_fighting(target))
		return notify_fail("����ʯһ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("poyu-quan", 1) < 120)
		return notify_fail("�������ȭ������죬����ʹ�á���ʯһ������\n");
				
	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���Ϊ�������ߣ��������á���ʯһ������\n");
			
	if ((int)me->query("neili") < 300)
		return notify_fail("��������������������ʹ�á���ʯһ������\n");

	if (me->query_skill_mapped("cuff") != "poyu-quan")
		return notify_fail("��û�м�������ȭ������ʹ�á���ʯһ������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "���һ����ȭͷ������һ�����صĻ���$n" HIY "��"NOR"\n";

	ap = me->query_skill("force") + me->query_str() * 10;
	dp = target->query_skill("force") + target->query_str() * 10;
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap + (int)me->query_skill("cuff");
		damage = damage / 5;
		damage += random(damage);

		me->add("neili", -200);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
					   HIR "ֻ��$P" HIR "��һȭ��$p" HIR
					   "����˳�ȥ�����ص�ˤ�ڵ��ϣ���Ѫ��ֹ��"NOR"\n");
		me->start_busy(2);
	} else 
	{
		msg += HIC "����$p" HIC "�����мܣ�Ӳ�����ĵ�����$P"
		       HIC "��һ�С�"NOR"\n";
		me->add("neili", -100);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
