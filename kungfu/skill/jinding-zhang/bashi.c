// bashi.c ������ ��ʽ��һ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "��ʽ"ZJBR"��һ"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int count, d_count, qi, maxqi, skill;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ʽ��һ��ֻ����ս���жԶ���ʹ�á�\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("��������������ߣ�\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ�����Ϊ����������ʹ�ð�ʽ��һ��\n");

	if ((int)me->query_skill("jinding-zhang", 1) < 100)
		return notify_fail("��Ľ����Ƶ���ϰ�������޷�ʹ�ð�ʽ��һ��\n");

	if (me->query_skill_mapped("strike") != "jinding-zhang")
		return notify_fail("��û�м��������ƣ��޷�ʹ�ð�ʽ��һ��\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "��������һ����������ȫ��Ĺ�����"
	      "˫�ƣ�ֻ����$P" HIY "����һ���죡"NOR"\n";
	ap = me->query_skill("strike");
	dp = target->query_skill("dodge");
	if (ap / 2 + random(ap) > dp)
	{
		damage  = (int)me->query_skill("linji-zhuang", 1);
		damage += (int)me->query_skill("jinding-zhang", 1);
		damage /= 3;
		damage += random(damage);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
					   HIR "ֻ��$N" HIR "�ڿն���ʹ���ˡ���ʽ"
					   "��һ�����������Ӱ��Ʈ������������$n"
					   HIR "ȫ�������λ������ž��$p"
					   HIR "�������˺ö��ƣ�"NOR"\n");
		me->add("neili", -100);
		me->start_busy(2);
	 } else
	 {
		msg += CYN "����$p" CYN "�͵����һԾ��������$P"
		       CYN "�Ĺ�����Χ��"NOR"\n";
		me->start_busy(3);
	 }
	 message_combatd(msg, me, target);
	 return 1;
}
