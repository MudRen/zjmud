// haishi.c ������¥

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"��¥"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
	int delta;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (userp(me) && ! me->query("can_perform/sanfen-jianshu/haishi"))
		return notify_fail("�㲻��ʹ�á�������¥����һ������\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������¥��ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("sword", 1) < 150)
		return notify_fail("��Ľ�����Ϊ������Ŀǰ����ʹ�á�������¥����\n");

	if (me->query_skill("sanfen-jianshu", 1) < 150)
		return notify_fail("������ֽ�������Ϊ����������ʹ����һ������\n");

	if (me->query_skill("dodge") < 150)
		return notify_fail("����Ṧ��Ϊ�������޷�ʹ�á�������¥����\n");
 
	if (me->query("neili") < 200)
		return notify_fail("�������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "���һ��������" + weapon->name() +
	      HIW "����֮�ʣ�ͻȻȦת��ʹ�����ֽ����Ķ���֮��"
	      "��������¥����һ��֮��\n�����̺����У���ʽ������"
	      "������������ʵʵ���������⾶ֱ����$n"
	      HIW "��"NOR"\n";

	me->add("neili", -150);
	ap = me->query_skill("sword");
	dp = target->query_skill("dodge");
	me->start_busy(1 + random(2));
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap);
		msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
					   HIR "$n" HIR "��ȫ�޷�������ʵ��ֻ��һ���ĵĴ�ʹ��һ���ҽУ��ѱ�$N"
					   HIR "�����Ľ��д��С�"NOR"\n");
		if (ap / 4 + random(ap) > dp)
		{
			damage /= 2;
			msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75,
						   HIR "\n$N" HIR "��$n" HIR "�ش�֮�²�������������"
						   HIR "��Цһ��������" + weapon->name() +
						   HIR "�������ֹ���һ��������$p" HIR "�ؿڡ�"NOR"\n");
		}
	} else
	{
		msg += HIC "$n" HIC "��״���μ��ˣ��ܿ���$N"
		       HIC "�����Ĺ�����"NOR"\n";
	}

	message_combatd(msg, me, target);

	return 1;
}
