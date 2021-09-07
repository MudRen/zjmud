// jiutian.c ����ʽ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����ʽ"; }
string *pfm_type() { return ({ "strike", }); }

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
		return notify_fail("������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("liuyang-zhang", 1) < 120)
		return notify_fail("��������Ʒ�������죬����ʹ�á�����ʽ����\n");
				
	if ((int)me->query_skill("force") < 250)
		return notify_fail("����ڹ���Ϊ�����ߣ��������á�����ʽ����\n");
			
	if ((int)me->query("neili") < 300)
		return notify_fail("��������������������ʹ�á�����ʽ����\n");
			
	if (me->query_skill_mapped("strike") != "liuyang-zhang")
		return notify_fail("��û�м�����ɽ�����ƣ�����ʹ�á�����ʽ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "˫��һ�񣬻���������Ӱ����������ס$n" HIC "��"NOR"\n";

	ap = me->query_skill("force");
	dp = target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		damage = me->query_skill("strike") +
			 ap - dp;
		damage += random(damage / 2);

		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
					   HIR "$p" HIR "���Σ�ֻ��Ӳ��һ�У������$P"
					   HIR "���������������Ѫ��ֹ��"NOR"\n");
	me->add("neili", -200);
		me->start_busy(2);
	} else
	{
		msg += HIC "����$p" HIC "ǿ��������Ӳ�����ĵ�ס$P"
		       HIC "��һ�ƣ�û���ܵ��κ��˺���"NOR"\n";
	me->add("neili", -80);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
