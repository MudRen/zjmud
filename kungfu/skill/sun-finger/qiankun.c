// qiankun.c һ��ָ ��һָǬ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "һָ"ZJBR"Ǭ��"; }
string *pfm_type() { return ({ "finger", }); }

int perform(object me, object target)
{
	string msg;
	int ap, dp;
	int damage;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��һָǬ����ֻ����ս����ʹ�á�\n");

	if ((int)me->query_skill("sun-finger", 1) < 100)
		return notify_fail("���һ��ָ��Ϊ������Ŀǰ������ʩչһָǬ��������\n");

	if ((int)me->query_skill("force") < 160)
		return notify_fail("���ڹ���򲻹�������ʩչһָǬ����\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("��������������޷�ʩչ��һָǬ������\n");

	if (me->query_skill_mapped("finger") != "sun-finger") 
		return notify_fail("��û�м���һ��ָ�����޷�ʹ�á�һָǬ������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ʹ��һ��ָ������һָǬ����������$n"
	      HIY "��ҪѨ����ʽ�仯����֮����\n" HIY;

	ap = me->query_skill("finger") + me->query_skill("force");
	dp = target->query_skill("parry") + target->query_skill("force");
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 3 + random(ap / 4);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 66,
					   HIR "���$p" HIR "û�ܱܿ�$P"
					   HIR "��һָ����������̴�д�Ѩ������"
					   "��Ѫ��ʱ�������������¼�����Ѫ��"NOR"\n");
		me->add("neili", -200);
		me->start_busy(1);
	} else
	{
		msg += CYN "����$p" CYN "������$P"
		       CYN "��æ��������������㿪����һ����"NOR"\n";
		me->start_busy(3);
		me->add("neili", -50);
	}
	message_combatd(msg, me, target);

	return 1;
}
