// quan ������ȭ
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"��ȭ"; }

int perform(object me, object target)
{
	string msg;
	int ap, dp;
	int damage;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("������ȭֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (me->query_skill("jiuyin-shengong", 1) < 120)
		return notify_fail("��ľ����񹦻�������죬����ʹ�þ�����ȭ��\n");

	if (me->query("neili") < 200)
		return notify_fail("�����������������ʹ�þ�����ȭ��\n");
 
       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "һ����ߣ���ȭ��������ʽ�ۻ룬��ߪ������"NOR"\n";
 
	ap = me->query_skill("cuff") + me->query("str") * 10 +
	     me->query_skill("martial-cognize", 1);
	dp = target->query_skill("dodge") + target->query("str") * 10 +
	     target->query_skill("martial-cognize", 1);

	me->start_busy(2);
	me->add("neili", -50);
	if (ap / 2 + random(ap) < dp)
	{
		msg += HIG "ֻ��$n" HIG "���Ų�æ������һ���������$N" HIG "��һ����"NOR"\n";
	} else
	{
		me->add("neili",-75);
		damage = ap + random(ap/2) -target->query_gain_armor();
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
					   HIR "$n" HIR "��æ�񵲣�������һȭ�����ε�֮�أ������"
					   "����ס��ֻ�������Ѫ���ߣ�����������"NOR"\n");
	}

	message_combatd(msg, me, target);
	return 1;
}
