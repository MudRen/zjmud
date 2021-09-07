// jingmo.c ��ħһָ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "��ħ"ZJBR"һָ"; }
string *pfm_type() { return ({ "finger", }); }

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
		return notify_fail("����ħһָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("yizhi-chan", 1) < 120)
		return notify_fail("���һָ����������죬���ڻ��޷�ʹ�á���ħһָ����\n");

	if ((int)me->query_skill("force") < 180)
		return notify_fail("����ڹ���򲻹�������ʩչ����ħһָ����\n");
				
	if ((int)me->query("neili") < 200)
		return notify_fail("�����������������޷����á���ħһָ����\n");
			
	if (me->query_skill_mapped("finger") != "yizhi-chan") 
		return notify_fail("��û�м���һָ�����޷�ʹ�þ�ħһָ��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "���һ������ָ������һ��������ɱ������$n"
	      HIY "�����ƻֺ�֮����"NOR"\n";

	ap = me->query_skill("finger");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap / 3);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
					   HIR "ֻ��$p" HIR "������������$P"
					   HIR "��һָ��������ǰ�����ɵ�����"
					   "�ҽУ��ؿ���Ѫֱ����"NOR"\n");
		me->add("neili", -150);
		me->start_busy(2);
	} else 
	{
		msg += CYN "����$p" CYN "��æԾ�����㿪��$P"
		       CYN "��һָ��"NOR"\n";
		me->add("neili", -60);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
