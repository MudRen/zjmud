// jumie.c  ���ֶ���Ҷָ���������
	 
#include <ansi.h>
#include <combat.h>
	 
inherit F_SSERVER; 
	 
string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "finger", }); }

int perform(object me, object target) 
{ 
	object weapon; 
	string msg; 
	int ap, dp; 
	int damage; 
	
	if (! target) target = offensive_target(me); 
	
	if (! target || ! me->is_fighting(target)) 
		return notify_fail("���������ֻ����ս���жԶ���ʹ�á�\n"); 
	 
	if (me->query_temp("weapon") || 
	    me->query_temp("secondary_weapon")) 
		return notify_fail("�������ֲ���ʹ�á�������𡹣�\n"); 
	 
	if (me->query_skill("force") < 200) 
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n"); 
	
	if (me->query_skill("duoluoye-zhi", 1) < 180) 
		return notify_fail("��Ķ���Ҷָ��Ϊ������Ŀǰ����ʹ�á�������𡹣�\n");
	 
	if (me->query("neili") < 800 || me->query("max_neili") < 2500) 
		return notify_fail("��������������޷�ʹ�á�������𡹣�\n"); 
	 
	if (me->query_skill_mapped("finger") != "duoluoye-zhi") 
		return notify_fail("��û�м�������Ҷָ������ʹ�á�������𡹣�\n"); 

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIB "$N" HIB "����ȫ������ֱ����$n" + HIB "��˫��һȦ����һ���ھ�" +
	      "��ס$n��\n" + HIB "�漴ȫ��һָ��������ϧ�ķѴ�����Ԫ������һ���еУ�"NOR"\n";
	 
	ap = me->query_skill("finger", 1) + me->query_skill("duoluoye-zhi", 1);
	dp = target->query_skill("dodge", 1) + target->query_skill("force", 1);
	damage = ap + random(ap / 4);
	 
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -500);
		
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 66,
					   HIR "ֻ��$p" HIR "һ���Һţ��ѱ�$P" +
					   HIR "һָ���У�һ�ɰԵ���������$P" + 
					   HIR "��ָ�⴫�����˼�������"NOR"\n");
	} else 
	{ 
		me->add("neili", -200);
		me->start_busy(3);
		msg += CYN "����$p" CYN "������񣬼�ʱ������" 
		       CYN "$P" CYN "������ǣ�����㿪����һ����"NOR"\n"; 
	}
	
	msg += HIR "��$P" + HIR "���������������ȣ��������ɲ�" +
	       "�ˣ����˲�������ˣ�"NOR"\n";

	me->receive_damage("qi", damage / 4);

	message_combatd(msg, me, target);
       
	return 1; 
}
