// fen.c ����
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }

int perform(object me)
{
	string msg;
	object weapon, target;
	int skill, ap, dp;
	int damage;

	if (userp(me) && ! me->query("can_perform/huoyan-dao/fen"))
		return notify_fail("�㻹�������á�������һ������\n");

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	skill = me->query_skill("huoyan-dao", 1);

	if (skill < 120)
		return notify_fail("��Ļ��浶�ȼ�������������ʹ����������\n");

	if (me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹�������ʹ������������\n");

	if (me->query("neili") < 400)
		return notify_fail("��������������޷��˹���\n");
 
       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIR "$N" HIR "�������ƣ�ʹ��һ�С����������ε�����$n"
	      HIR "���ؿڻ�ȥ��"NOR"\n";

	ap = me->query_skill("force") + skill / 5;
	dp = target->query_skill("force");

	if (dp < 1) dp = 1;
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -300);
		damage = 150 + skill / 4 + random(skill);
		msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70,
					   HIR "$p" HIR "ǿ��������ͼ�ֿ���Ȼ���޷�����$P"
					   HIR "�����ı仯�������$P"
					   HIR "�����ε����ش����ؿڣ�"NOR"\n");
		me->start_busy(2);

	} else
	{
		msg += HIC "ȴ��$p" HIC "���Ų�æ������һ���������$P"
		       HIC "�ı�ɱһ����"NOR"\n";
		me->add("neili", -150);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
