// hengchen.c С�����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "С��"ZJBR"���"; }
string *pfm_type() { return ({ "hand", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("С�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("shenlong-bashi", 1) < 150)
		return notify_fail("���������ʽ�ַ���������죬����ʹ��С����¡�\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹�������ʹ��С����¡�\n");

	if ((int)me->query("neili") < 400)
		return notify_fail("��������������������ʹ��С����¡�\n");

	if (me->query_skill_mapped("hand") != "shenlong-bashi")
		return notify_fail("��û�м���������ʽ�ַ�������ʹ��С����¡�\n");

	if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "˳���ڵ���һ�������$n���������"
	      HIG "���ֳ�ȭ������һȭ����$n�Ĵ��ġ�"NOR"\n";
	      
	me->start_busy(1 + random(4));

	if (random(me->query_skill("hand")) > target->query_skill("dodge") / 2 )
	{
		damage = (int)me->query_skill("hand") + (int)me->query_skill("force");
		damage = damage / 2 + random(damage);
		me->add("neili", -210);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35,
					   HIR "$p" HIR "��æ����������ȴ����û��" 
					   "���$P" HIR "������������ÿ�����Ѫ��"NOR"\n");
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ��һŤ��������$P"
		       CYN "�Ľ�����"NOR"\n";
		me->add("neili", -80);
	}
	message_combatd(msg, me, target);

	return 1;
}
