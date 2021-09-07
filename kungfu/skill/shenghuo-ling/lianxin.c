// lianxin.c

#include <ansi.h>
#include <combat.h>

#define LIAN "��" HIW "������" NOR "��"

inherit F_SSERVER;

string query_name() { return "������"; }
string *pfm_type() { return ({ "sword", }); }

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

	skill = me->query_skill("shenghuo-ling", 1);

	if (! target || ! me->is_fighting(target))
		return notify_fail(LIAN "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õı������ԣ�����ʹ��ʥ���֮" LIAN "��\n");

	if (skill < 150)
		return notify_fail("���ʥ����ȼ�����, ����ʹ��ʥ���֮" LIAN "��\n");

	if (me->query("max_neili") < 1600)
		return notify_fail("���������Ϊ���㣬����ʹ��ʥ���֮" LIAN "��\n");

	if (me->query("neili") < 300)
		return notify_fail("�����������������ʹ��ʥ���֮" LIAN "��\n");

	if (me->query_skill_mapped("sword") != "shenghuo-ling") 
		return notify_fail("��û�м���ʥ���������ʹ��ʥ���֮" LIAN "��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "һ����ͷ���$n" HIW "��ǰ����Ȼʹ��ʥ��"
	      "�֮���������" + weapon->name() + NOR + HIW "����"
	      "��������ʽ�����ޱȡ�"NOR"\n";

	damage = skill / 2 + random(skill);
	ap = me->query_skill("sword");
	dp = target->query_skill("parry");

	if (ap / 2 + random(ap) > dp)
	{
		me->add("neili", -200);
		me->start_busy(3);
		msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK,
		       damage, 40, HIR "$n" HIR "ֻ����ǰ���������ͻ"
		       "Ȼ$N" HIR "˫�ֳ������Լ���ǰ������̫��Ѩ��"
		       "ʱһ���ʹ��"NOR"\n");
	}
	else
	{
		me->add("neili", -100);
		msg += CYN "$n" CYN "����ǰ�����������æ����������ǿ"
		      "�ֵ���������������ò�����������$N" CYN "��"
		      "����Χ֮�⡣"NOR"\n";
		me->start_busy(3);
	}
	message_combatd(msg, me, target);
	return 1;
}
