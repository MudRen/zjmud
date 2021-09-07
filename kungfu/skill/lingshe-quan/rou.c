// rou.c ���־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (! target || ! me->is_fighting(target))
		return notify_fail("�����־���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("��Ҫʩչȭ������ʹ��������\n");
		
	if ((int)me->query_skill("lingshe-quan", 1) < 120)
		return notify_fail("�������ȭ��������죬���ڻ��޷�ʹ�á����־�����\n");
				
	if ((int)me->query("neili") < 200)
		return notify_fail("�����������������޷����á����־�����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "һȭ�������;���ֱۺ�Ȼ����˼���ת�˸�Ȧ�ӣ�����$n"
	      HIG "����$p" HIG "����ʤ����"NOR"\n";

	ap = me->query_skill("cuff");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		damage = (int)me->query_skill("force") + (int)me->query_skill("cuff");
		damage = damage / 3;
		damage += random(damage);

		me->add("neili", -100);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
					   HIR "ֻ��$n" HIR "���һ�����ֻ�֮�²������㣬��$N"
					   HIR "һȭ���˸����У��ƺ�һ��������������"NOR"\n");
		me->start_busy(2);
	} else 
	{
		msg += HIC "����$p" HIC "�����Ŀ죬��æʩչ�����ܿ���ȭ��"NOR"\n";
		me->add("neili", -50);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
