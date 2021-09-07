// zhan.c ӭ��һ��ն

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "ӭ��"ZJBR"һ��"; }

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
		return notify_fail("��ӭ��һ��ն��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");
		
	if ((int)me->query_skill("dongyang-dao", 1) < 70)
		return notify_fail("��Ķ��󵶷�������죬����ʹ�á�ӭ��һ��ն����\n");
				
	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���Ϊ�����ߣ��������á�ӭ��һ��ն����\n");
			
	if ((int)me->query("neili") < 300)
		return notify_fail("��������������������ʹ�á�ӭ��һ��ն����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "\n$N" HIC "���һ���������׹��¶�����е�" +
	      weapon->name() + HIC "����һ���⻡ֱ�����£����Ƿ�ɣ��ѧ��ӭ��һ��ն����"NOR"\n";

	ap = me->query_skill("blade");
	dp = target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap);
		me->add("neili", -100);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
					   HIR "$n" HIR "ֻ�������к��һ�£���"
					   "��Ѫ����ʱ�������������ۡ�������һ����Ѫ��"NOR"\n");
		me->start_busy(2);
	} else 
	{
		msg += HIC "Ȼ��$p" HIC "����������Ӳ��������һ����˿�����ˡ�"NOR"\n";
		me->add("neili", -50);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
