// yi.c ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "sword", }); }

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
		return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�þ��С�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("�޽�������ý��⣿\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�����ڵ������������޷�ʹ�ý��⣡\n");

	if ((int)me->query_skill("lonely-sword", 1) < 120)
		return notify_fail("��Ķ��¾Ž��������ң��޷�ʹ�ý��⣡\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("��û�м������¾Ž����޷�ʹ�ý��⣡\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	switch (random(3))
	{
	case 0:
		msg = HIM "$N" HIM "һ���̳���������Ҳ��֪��Ҫ�����δ���"NOR"\n";
		break;

	case 1:
		msg = HIM "$N" HIM "���ֻ������е�" + weapon->name() +
		       HIM "������Ŀ�ģ������κ���ʽ��"NOR"\n";
		break;

	default:
		msg = HIM "$N" HIM "бб�̳�һ����׼ͷ֮����˷�����˼��"NOR"\n";
		break;
	}

	ap = me->query_skill("lonely-sword", 1) + me->query_skill("martial-cognize", 1) / 2;
	dp = target->query_skill("parry", 1) + target->query_skill("martial-cognize", 1) / 2 +
	     target->query_skill("lonely-sword", 1);
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap * 2 + random(ap);
		me->add("neili", -180);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
					   HIR "$n" HIR "ȫȻ�޷����$P"
					   HIR "��Ī�������������һ�����񣬵�ʱ�ܴ���"NOR"\n");
		me->start_busy(2);
	} else
	if (target->query_skill("martial-cognize", 1) + target->query_skill("lonely-sword", 1) > 150)
	{
		msg += CYN "Ȼ��$n" CYN "��ͨ���а�����в��У���$N"
		       CYN "�Ĺ���ȫȻ���ܷ������á�\n";
		me->add("neili", -80);
		me->start_busy(3);
	} else
	{
		msg += CYN "$n" CYN "��Ȼ��֮����û�н�$P"
		       CYN "���з������ϣ����ּܿ�����©���������"NOR"\n";
		me->add("neili", -60);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
