// bafang.c ����˷�
	 
#include <ansi.h>
#include <combat.h> 
	 
inherit F_SSERVER; 
	 
string query_name() { return "����"ZJBR"�˷�"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target) 
{ 
	object weapon; 
	string msg; 
	int ap, dp; 
	int damage; 
	
	if (! target) target = offensive_target(me); 
	
	if (! target || ! me->is_fighting(target)) 
		return notify_fail("������˷���ֻ����ս���жԶ���ʹ�á�\n"); 
	 
	if (me->query_temp("weapon") || 
	    me->query_temp("secondary_weapon")) 
		return notify_fail("�������ֲ���ʹ�á�����˷�����\n"); 
	 
	if (me->query_skill("force") < 300) 
		return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n"); 
	
	if (me->query_skill("shenzhang-bada", 1) < 200) 
		return notify_fail("������ư˴���Ϊ������Ŀǰ����ʹ�á�����˷�����\n"); 
	 
	if (me->query("neili") < 700) 
		return notify_fail("��������������޷�ʹ�á�����˷�����\n"); 
	 
	if (me->query_skill_mapped("strike") != "shenzhang-bada") 
		return notify_fail("��û�м������ư˴򣬲���ʹ�á�����˷�����\n"); 

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "���������һ���������һ����ȫ�������޷��Թģ�" 
		   HIY "Ȼ����������һ�ݣ��Ӹ����£�˫�Ʒ������£�ɲ�Ǽ䣬�ھ����������"
		   "����$n" + HIY "��"NOR"\n"; 
	 
	ap = me->query_skill("strike") + me->query_skill("shenzhang-bada");
	dp = target->query_skill("dodge") + target->query_skill("parry"); 
	 
	if (ap / 3 + random(ap) > dp / 2) 
	{ 
		damage = ap / 2;
		damage += random(damage); 
		me->add("neili", -350); 
	 
		msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 45,
					   HIR "ֻ��$p" HIR "��ܲ������м�ʧ�룬��$P"
					   HIR "�������д��������ת����Ѫ������"NOR"\n"); 
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
