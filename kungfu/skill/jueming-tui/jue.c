// jue ����һ��
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"һ��"; }
string *pfm_type() { return ({ "unarmed", }); }

int perform(object me, object target)
{
	string msg;
	int ap, dp, pp;
	int damage;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("������һ�ߡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ����һ������\n");

	if (me->query_skill("jueming-tui", 1) < 80)
		return notify_fail("��ġ������ȡ���������죬����ʹ�á�����һ�ߡ���\n");

	if (me->query_str() < 35)
		return notify_fail("�������������С���߶����ȣ�\n");

	if (me->query("neili") < 200)
		return notify_fail("�����������������ʹ�á�����һ�ߡ���\n");

	if (me->query_skill_mapped("unarmed") != "jueming-tui")
		return notify_fail("��û�м��������ȷ�������ʹ�á�����һ�ߡ���\n");
 
       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	switch (random(3))
	{
	case 0:
		msg = HIC "$N" HIC "һ����ߣ�������ߣ����Ⱥ�ɨ$n"
		      HIC "���������Ʋ��ɵ���"NOR"\n";
		break;

	case 1:
		msg = HIC "$N" HIC "���һ���������߳���ֻ����$n"
		      HIC "���ʡ�"NOR"\n";
		break;

	default:
		msg = HIC "$N" HIC "˫�������߳���Ю�������������죬"
		      "��ǧ��֮��ɨ��" HIC "$n��"NOR"\n";
		break;
	}
 
	ap = me->query_skill("unarmed") + me->query("str") * 10;
	dp = target->query_skill("dodge") + target->query("dex") * 10;
	pp = target->query_skill("parry") + target->query("str") * 10;
	
	me->start_busy(2);
	me->add("neili", -50);
	if (ap * 7 / 10 + random(ap) < pp)
	{
		msg += HIG "$n" HIG "����һ�Σ�Ӳ�Ǽ�ס��$N" HIG "��һ����"NOR"\n";
	} else
	if (ap * 7 / 10 + random(ap) < dp)
	{
		msg += HIG "ֻ��$n" HIG "���Ų�æ������һ���������$N" HIG "��һ����"NOR"\n";
	} else
	{
		me->add("neili", -70);
		damage = ap / 3 + random(ap / 3);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 66,
					   HIR "$n" HIR "��æ�񵲣�ֻ����������ó��棬�����"
					   "����ס��ֱ���ߵ÷�������֮�ߣ�"NOR"\n");
	}

	message_combatd(msg, me, target);
	return 1;
}
