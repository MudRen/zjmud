// lei.c �������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "���"ZJBR"����"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("�������ֻ����ս���жԶ���ʹ�á�\n");

	if (me->query_skill("never-defeated", 1) < 150)
		return notify_fail("��Ĳ����񹦻�������죬����ʹ�����������\n");

	if (! objectp(weapon = me->query_temp("weapon")))
		return notify_fail("������ֱֳ��в���ʩչ���������\n");

	if (me->query("neili") < 300)
		return notify_fail("�������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "���һ�������е�" + weapon->name() +
	      HIC "�������£����Ƽ򵥣���Ȼ��ס��$n"
	      HIC "���е���·��"NOR"\n";

	ap = me->query_skill("never-defeated", 1);
	dp = target->query("combat_exp") / 10000;
	me->add("neili", -60);
	me->start_busy(1 + random(2));

	me->want_kill(target);
	if (dp >= 100)
	{
		msg += HIY "$n" HIY "ʹ��ƽ����ѧ���������⣬û��һ����"NOR"\n";
	} else
	if (random(ap) > dp)
	{
		msg += HIR "$n" HIR "ƽ����������������������ȫȻ�޷����⣬"
		       HIR "��ʱ����������Ҫ������Ȼ���أ�"NOR"\n";
		message_combatd(msg, me, target);
		target->die(me);
		return 1;
	} else
	{
		msg += HIM "$n" HIM "���һ������æ���ҵֵ�����"
		      "Ȼû��һ���˺������ҵ��ѣ�"NOR"\n";
	}

	message_combatd(msg, me, target);

	return 1;
}
