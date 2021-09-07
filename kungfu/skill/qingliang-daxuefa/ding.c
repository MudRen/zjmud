#include <ansi.h>
#include <combat.h>

#define DING "��" HIC "͸�Ƕ�" NOR "��"

inherit F_SSERVER;
 
string query_name() { return "͸�Ƕ�"; }
string *pfm_type() { return ({ "dagger", }); }

int perform(object me)
{
	string msg;
	object weapon, target;
	int skill, ap, dp, damage;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! me->is_fighting(target))
		return notify_fail(DING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	weapon = me->query_temp("weapon");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "dagger")
		return notify_fail("����ʹ�õ��������ԣ�����ʩչ" DING "��\n");

	skill = me->query_skill("qingliang-daxuefa", 1);

	if (me->query_skill("force") < 150)
		return notify_fail("����ڹ���Ϊ����������ʩչ" DING "��\n");

	if (me->query("neili") < 500)
		return notify_fail("�����ڵ��������㣬����ʩչ" DING "��\n");

	if (skill < 100)
		return notify_fail("��������Ѩ����Ϊ���ޣ�����ʩչ" DING "��\n");

	if (me->query_skill_mapped("dagger") != "qingliang-daxuefa")
		return notify_fail("��û�м���������Ѩ��������ʩչ" DING "��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "��������" + weapon->name() + HIC "б�̶�����һʽ��"
	      HIR "͸�Ƕ�" NOR + HIC "������ź�����������$n" HIC "��Χ������"NOR"\n";
 
	ap = me->query_skill("dagger");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -200);
		damage = 100 + ap / 3 + random(ap / 3);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
					   HIR "��ʱֻ���á����͡�һ����$n" HIR
					   "�ؿڱ�$N" HIR "��һ�д��У�����һ����Ѫ��"NOR"\n");
		me->start_busy(1);
		if (ap / 3 + random(ap) > dp && ! target->is_busy())
			target->start_busy(ap / 25 + 1);
	} else
	{
		msg += CYN "����$p" CYN "�Ŀ�����$P" CYN
		       "����ʽ�������һһ��⣬û¶���"
		       "������"NOR"\n";
		me->add("neili", -50);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}

