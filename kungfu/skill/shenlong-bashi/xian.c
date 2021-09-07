// xian.c ��������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }
string *pfm_type() { return ({ "hand", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("shenlong-bashi", 1) < 100)
		return notify_fail("���������ʽ�ַ���������죬����ʹ���������֡�\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹�������ʹ���������֡�\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("��������������������ʹ���������֡�\n");

	if (me->query_skill_mapped("hand") != "shenlong-bashi")
		return notify_fail("��û�м���������ʽ�ַ�������ʹ���������֡�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIG "$N" HIG "�����ḡ���������ģ��Ƶ��ǵ�������ײײ�ĳ���$n"
	      HIG "��ͬʱ���־���һ�У�����֮����"NOR"\n";

	me->start_busy(2);
	if (random(me->query_skill("hand")) > target->query_skill("parry") / 2)
	{
		damage = (int)me->query_skill("force");
		damage = damage / 2 + random(damage / 2);
		me->add("neili", -125);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35,
					   HIR "$p" HIR "�����ҵ���ȴû�ܵ�ס$P" HIR "�⿴������"
					   "�������������$P" HIR "���صĻ��У��۵�����һ����Ѫ��"NOR"\n");
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ������ĵ�ס��$P"
		       CYN "�Ľ�����"NOR"\n";
		me->add("neili", -30);
	}
	message_combatd(msg, me, target);

	return 1;
}
