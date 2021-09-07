// wuse.c  ��ɫ����
	 
#include <ansi.h>
#include <combat.h> 
	 
inherit F_SSERVER; 
	 
string query_name() { return "��ɫ"ZJBR"����"; }
string *pfm_type() { return ({ "finger", }); }

int perform(object me, object target) 
{ 
	object weapon; 
	string msg; 
	int ap, dp; 
	int damage; 
	
	if (! target) target = offensive_target(me); 
	
	if (! target || ! me->is_fighting(target)) 
		return notify_fail("����ɫ���ࡹֻ����ս���жԶ���ʹ�á�\n"); 
	 
	if (me->query_temp("weapon") || 
	    me->query_temp("secondary_weapon")) 
		return notify_fail("�������ֲ���ʹ�á���ɫ���ࡹ��\n"); 
	 
	if (me->query_skill("force") < 100) 
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n"); 
	
	if (me->query_skill("wuxiang-zhi", 1) < 150) 
		return notify_fail("�������ָ��Ϊ������Ŀǰ����ʹ�á���ɫ���ࡹ��\n"); 
	 
	if (me->query("neili") < 400) 
		return notify_fail("��������������޷�ʹ�á���ɫ���ࡹ��\n"); 

	if (me->query_skill_mapped("finger") != "wuxiang-zhi")
		return notify_fail("��û�м�����������ָ������ʹ�á���ɫ���ࡹ��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "����ȫ�������������ָ��������ϣ�"
	      HIY "��$n" HIY "��ȥ��ͬʱһָ��������ͬ����һ�����$n" + HIY "��"NOR"\n";

	ap = me->query_skill("finger") + me->query_skill("force");
	dp = target->query_skill("dodge") + target->query_skill("parry");

	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 3 + random(ap / 4);
		me->add("neili", -200);
		me->start_busy(2 + random(2));

		msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 72,
					   HIR "ֻ��$p" HIR "һ���ҽУ��ѱ������ؿ�ҪѨ��$p"
					   HIR "ֻ�����ؿ���Ѫ��ӿ��ȫ����Ѫ"
					   "�������۵�һ���³�һ����Ѫ���಻���ԣ�"NOR"\n");
	} else
	{
		me->add("neili", -100);
		me->start_busy(3);
		msg += CYN "����$p" CYN "������$N" CYN "����ͼ������"
		       CYN "���Ʈ�����ɣ��������һ������һ����"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
