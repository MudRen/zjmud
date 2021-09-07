// hengshao.c ��ɨǧ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string final(object me, object target, int ap, int dp);
 
string query_name() { return "��ɨ"ZJBR"ǧ��"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("����ɨǧ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("���á���ɨǧ�����������гֵ���\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("baisheng-daofa", 1) < 150)
		return notify_fail("��İ�ʤ�����������ң��޷�ʹ�á���ɨǧ������\n");

	if (me->query_skill_mapped("blade") != "baisheng-daofa")
		return notify_fail("��û�м�����ʤ�������޷�ʹ�á���ɨǧ������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	ap = me->query_skill("blade") + me->query_str() * 10;
	if (me->query("character") == "��������")
	{
		msg = HIR "$N" HIR "��Ŀ��ȣ�ɱ����Ȼ�����ֳ�" + weapon->name() +
		      HIR "���޷��˵���Ȼ��ɨ$n" HIR "��ȫȻ����������������Ȼ��"NOR"\n";
		ap += ap * 3 / 10;
	} else
		msg = HIR "$N" HIR "����������" + weapon->name() +
		      HIR "���棬��ৡ���һ��ɨ��$n��"NOR"\n";

	dp = target->query_skill("parry") + target->query_str() * 10;
	damage = 0;
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap + random(ap / 3);
	      me->add("neili", -350);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 48,
					   (: final, me, target, ap, dp :));
		me->start_busy(3);
	} else 
	{
		msg += HIC "$n" HIC "�����мܣ�Ӳ�����ĵ�ס���������ʧɫ֮��ɱһ����"NOR"\n";
	      me->add("neili", -150);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}

string final(object me, object target, int ap, int dp)
{
	object weapon;
	string msg;

	msg = HIR "$n" HIR "��æ�ֵ���ȴ�����мܵ�ס��������"
	      "����һ����÷������Զ��ƽɳ��";
	if (ap / 3 > dp)
	{
		msg += "�ʹ˱�����"NOR"\n";
		call_out("char_killed", 0, target, me);
	} else
	if ((ap / 2 > dp) && objectp(weapon = target->query_temp("weapon")))
	{
		msg += "���е�" + weapon->name() + HIR "��Ҳ����ס��Ӧ��������"NOR"\n";
		weapon->move(environment(me));
	} else
		msg += ""NOR"\n";
	return msg;
}

void char_killed(object ob, object me)
{
	if (objectp(ob) && objectp(me) && me->is_fighting(ob) &&
	    environment(ob) == environment(me))
		ob->die(me);
}
