#include <ansi.h>
#include <combat.h> 
	 
inherit F_SSERVER; 
	 
string query_name() { return "����"ZJBR"һָ"; }
string *pfm_type() { return ({ "finger", }); }

int perform(object me, object target) 
{ 
	object weapon; 
	string msg; 
	int ap, dp; 
	int damage; 
	
	if (! target) target = offensive_target(me); 
	
	if (! target || ! me->is_fighting(target)) 
		return notify_fail("�����޾���ָ��ֻ����ս���жԶ���ʹ�á�\n"); 
	 
	if (me->query_temp("weapon") || 
	    me->query_temp("secondary_weapon")) 
		return notify_fail("�������ֲ���ʹ�á����޾���ָ����\n"); 
	 
	if (me->query_skill("force") < 250) 
		return notify_fail("����ڹ�����Ϊ����������ʹ�á����޾���ָ����\n"); 
	
	if (me->query_skill("xiuluo-zhi", 1) < 150) 
		return notify_fail("�������ָ��Ϊ������Ŀǰ����ʹ�á����޾���ָ����\n"); 
	 
	if (me->query("neili") < 500) 
		return notify_fail("��������������޷�ʹ�á����޾���ָ����\n"); 
	 
	if (me->query_skill_mapped("finger") != "xiuluo-zhi") 
		return notify_fail("��û�м�������ָ������ʹ�á����޾���ָ����\n"); 

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIB "$N" HIB "��Ȼ��¶�׹⣬���α���쳣Ʈ�죬��$n"
	      HIB "����������\n����ͣ��$n" HIB "����ãʱ��$N" HIB
	      "ͻȻ����������Ϣ��һָ��\n����"NOR"\n"; 
	 
	ap = me->query_skill("finger") + me->query_skill("force"); 
	dp = target->query_skill("dodge") + target->query_skill("parry"); 
	 
	if (ap / 2 + random(ap) > dp) 
	{ 
		damage = ap / 4 + random(ap / 3); 
		me->add("neili", -350);
		me->start_busy(1);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
					   HIR "ֻ��$n" HIR "һ���ҽУ��ѱ�$N" HIR
					   "����Ҫ����λ��ֻ����ǰһƬ\n��ڣ�����"
					   "ҡҡ��׹��"NOR"\n");
	} else 
	{ 
		me->add("neili", -150); 
		me->start_busy(3);
		msg += CYN "����$n" CYN "������$N" CYN "����ͼ����"
		       "�����Ʈ�����ɣ��������\nһ������һ����\n"
		       NOR; 
	} 
	message_combatd(msg, me, target); 
	 
	return 1; 
}

