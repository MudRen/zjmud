// wanshi.c �����ȷ���ǧ�����ɡ�
// by jeeny

#include <ansi.h>
#include <combat.h>

#define LINGSHE_ZHANG    "/clone/weapon/lingshe"

inherit F_SSERVER;

string final(object me, object target, int damage, object weapon);

string query_name() { return "ǧ��"ZJBR"����"; }
string *pfm_type() { return ({ "staff", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;

	if (userp(me) && ! me->query("can_perform/lingshe-zhangfa/wanshi"))
		return notify_fail("�㻹����ʹ�á�ǧ�����ɡ���һ������\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��ǧ�����ɡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");


	if ((int)me->query_skill("lingshe-zhangfa", 1) < 160)
		return notify_fail("��������ȷ�������죬����ʹ�á�ǧ�����ɡ���\n");

	if (me->query("neili") < 400)
		return notify_fail("�����������������޷�ʹ�á�ǧ�����ɡ���\n");

	if (me->query_skill_mapped("staff") != "lingshe-zhangfa") 
		return notify_fail("��û�м��������ȷ����޷�ʹ�á�ǧ�����ɡ���\n");

	if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIB "$N" HIB "�ֳ�" + weapon->name() + HIB "��ֱ��$n�й�" HIB "��"NOR"\n";

	ap = me->query_skill("staff");
	dp = target->query_skill("parry");
	if (target->is_good()) ap += ap / 10;

	me->start_busy(2 + random(6));
	if (ap / 3 + random(ap) > dp)
	{
		damage = ap + random(ap / 5);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
					   (: final, me, target, damage, weapon :));
		me->add("neili", -350);
		if (LINGSHE_ZHANG->query("du") > 0 && weapon == find_object("/clone/weapon/lingshe"))
		{
			target->apply_condition("snake_poison", ap / 2, me);
			LINGSHE_ZHANG->add("du", -1);
		}
	} else
	{
		msg += HIG "����$p" HIG "������$P" HIG "����ͼ��һ"
		       "���أ������������ܿ�����һ�С�"NOR"\n";
		me->add("neili", -100);
	}
	message_combatd(msg, me, target);

	return 1;
}

string final(object me, object target, int damage, object weapon)
{
	target->receive_damage("jing", damage / 4, me);
	target->receive_wound("jing", damage / 8, me);
	return HIW "��֪" HIW + weapon->name() + HIW "ͻȻ���䣬�Ƶ�$p" HIW "����"
		"���صػ�����$p" HIW "�ľ������ϣ�\n"
		HIB "$p" HIB "���ۡ����³�һ����Ѫ����"
		HIB "��ֻ������һ��������"NOR"\n";
}
