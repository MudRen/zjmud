// zhenwu.c ̫�������������а��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string final(object me, object target, int damage);

string query_name() { return "����"ZJBR"��а"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;

	if (userp(me) && ! me->query("can_perform/taiji-jian/zhenwu"))
		return notify_fail("�㻹����ʹ�á������а����һ������\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�������а��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("taiji-jian", 1) < 160)
		return notify_fail("���̫������������죬����ʹ�á������а����\n");

	if (me->query("neili") < 300)
		return notify_fail("�����������������޷�ʹ�á������а����\n");

	if (me->query_skill_mapped("sword") != "taiji-jian") 
		return notify_fail("��û�м���̫���������޷�ʹ�á������а����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "ƽƽ�ӳ�һ������ɨ$n" HIY "��"NOR"\n";

	ap = me->query_skill("sword");
	dp = target->query_skill("parry");
	if (target->is_bad()) ap += ap / 10;

	me->start_busy(2);
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap + random(ap / 3);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
					   (: final, me, target, damage :));
		me->add("neili", -210);
	} else
	{
		msg += HIG "����$p" HIG "������$P" HIG "����ͼ����"
		       "����㣬ȫ��Ӧ�����硣"NOR"\n";
		me->add("neili", -100);
	}
	message_combatd(msg, me, target);

	return 1;
}

string final(object me, object target, int damage)
{
	target->receive_damage("jing", damage / 4, me);
	target->receive_wound("jing", damage / 8, me);
	return  HIY "���$p" HIY "û�а����������ϣ���"
		"��Ӧ��һ�У�ȴ��$P" HIY "���ƺ�Ȼһ��"
		"��\n������ǧ���������������߷緶��\n"
		HIR "$p" HIR "����ʧ�룬���ڵ�������$P"
		HIR "��һ������Ҫ������Ѫ�������Ҳ��̶ã�"NOR"\n";
}

