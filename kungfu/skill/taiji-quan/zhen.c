// zhen.c ̫��ȭ�����־�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "���־�"; }
string *pfm_type() { return ({ "unarmed", }); }

int perform(object me, object target)
{
	int damage;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʹ�á����־���\n");		
		
	if ((int)me->query_skill("taiji-quan", 1) < 50)
		return notify_fail("���̫��ȭ������죬����ʹ�á����־���\n");
				
	if ((int)me->query("neili", 1) < 100)
		return notify_fail("����������̫��������ʹ�á����־���\n");

	if (me->query_skill_mapped("unarmed") != "taiji-quan")
		return notify_fail("������û�м���̫��ȭ������ʹ�á����־���\n");

	if (me->query_skill_prepared("unarmed") != "taiji-quan")
		return notify_fail("������û��׼��ʹ��̫��ȭ���޷�ʹ�á��𡹣�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = CYN "$N" CYN "Ĭ���񹦣�ʹ��̫��ȭ�����־�����ͼ����������$n"
	      CYN "��"NOR"\n";
	me->add("neili", -50);

	ap = me->query_skill("force");
	dp = target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		me->start_busy(3);
		damage = ap + random(ap / 3);
		
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
					   damage, 50,
					   CYN "��һȭ�仯�޷�����������$n"
					   CYN "���е���·��һȭ�������У�\n"
					   ":����@?");
	} else 
	{
		me->start_busy(3);
		msg += CYN "����$p" CYN "������$P"
		       CYN "����ͼ����û���ϵ���"NOR"\n";
	}
	message_combatd(msg, me, target);
	return 1;
}
