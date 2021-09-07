// xixueqingfu.c ��Ѫ����
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"��Ѫ"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me)
{
	string msg;
	object weapon, target;
	int damage;
	int skill;
	int ap, dp;

	me->clean_up_enemy();
	target = me->select_opponent();

	skill = me->query_skill("hanbing-mianzhang", 1);

	if (! (me->is_fighting(target)))
		return notify_fail("����Ѫ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (objectp(weapon = me->query_temp("weapon")))
		return notify_fail("��ʹ����������\n");

	if (skill < 60)
		return notify_fail("��ġ��������ơ��ȼ�����, ����ʹ�á���Ѫ���𡹣�\n");

	if (me->query_skill("dodge", 1) < 200)
		return notify_fail("����Ṧ������û�д�ã��޷����á���Ѫ���𡹣�\n");

	if (me->query_skill_mapped("strike") != "hanbing-mianzhang")
		return notify_fail("��û�м����������ƣ��޷����á���Ѫ���𡹣�\n");
 
       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "ͻȻ��ͬ����һ����ٿ���۽�$n"
	      HIR "����ǰ���������$n" HIR "���ʺ�ҧȥ��"NOR"\n";
 
	ap = me->query_skill("dodge") + me->query_dex() * 10;
	dp = target->query_skill("dodge") + target->query_dex() * 10;
	if (ap / 4 + random(ap / 2) > dp)
	{
		me->add("neili", -300);
		damage = skill * 5 + random(skill);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
					   HIG "$n" HIG "ֻ����ͷһʹ����֫������"
					   HIG "������Ѫ�ڲ�����ʧ��\n"  NOR);
		me->start_busy(4);
	} else
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -200);
		damage = skill + random(skill);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 66,
					   HIG "$n" HIG "ֻ�����ʺ�һ���ʹ��ԭ����$P" HIG
					   "Ҫ�˸����У�ֻ��$N" HIG "����ҧס����$n" HIG "����Ѫ��"NOR"\n");
		me->start_busy(3);
	} else
	{
		msg += CYN "ֻ��$n" CYN "���Ų�æ������һ���������$N"
		      CYN "�����ݣ�"NOR"\n";
		me->add("neili", -50);
		me->start_busy(2);
	}
	message_combatd(msg, me, target);

	return 1;
}

