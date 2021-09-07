// bafang.c �˷��ص�ʽ

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "�˷�"ZJBR"�ص�"; }
string *pfm_type() { return ({ "blade", }); }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count;
	int i;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("���˷��ص�ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("����û����ʹʲô���˷��ص�ʽ����\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("hujia-daofa", 1) < 100)
		return notify_fail("��ĺ��ҵ����������ң��޷�ʹ�á��˷��ص�ʽ����\n");

	if (me->query_skill_mapped("blade") != "hujia-daofa")
		return notify_fail("��û�м������ҵ������޷�ʹ�á��˷��ص�ʽ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "����Գ�ۣ����е�" + weapon->name() +
	      HIW "�������£��仯Ī�⣬������$n" HIW "����Ҫ����"NOR"\n";

	if (random(me->query_skill("blade")) > target->query_skill("parry") / 2)
	{
		msg += HIY "$n" HIY "������ʵ���Ǳ��Ī�⣬���ɵ���"
		       "�����⣬��ʽ��ʱ����������"NOR"\n";
		count = me->query_skill("hujia-daofa", 1) / 6;
	} else
	{
		msg += HIC "$n" HIC "�ĵ�΢΢һ����������С�Ľ��С�"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);
	me->add("neili", -150);
	me->add_temp("apply/attack", count);

	for (i = 0; i < 4 + random(4); i++)
	{
		if (! me->is_fighting(target))
			break;
		if (random(3) == 1 && ! target->is_busy())
			target->start_busy(1);
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->add_temp("apply/attack", -count);
	me->start_busy(1 + random(6));
	return 1;
}
