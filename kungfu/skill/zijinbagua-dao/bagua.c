// bagua.c ������

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"��â"; }
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
		return notify_fail("��������â��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ı������ԡ�\n");

	if ((int)me->query("max_neili") < 2000)
		return notify_fail("���������Ϊ������\n");

	if ((int)me->query("neili") < 400)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 220)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("zijinbagua-dao", 1) < 200)
		return notify_fail("����Ͻ���Ե��������ң��޷�ʹ�á�������â����\n");

	if (me->query_skill_mapped("blade") != "zijinbagua-dao")
		return notify_fail("��û�м����Ͻ���Ե����޷�ʹ�á�������â����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = MAG "$N" MAG "һ�����ȣ����е�" + weapon->name() +
	      MAG "��â��������ʱֻ����������ĵ�â���հ������"
	      "��λֱӿ$n" MAG "��"NOR"\n";

	if (random(me->query_skill("blade")) > target->query_skill("parry") / 2)
	{
		msg += HIR "$n" HIR "������ʵ���Ǳ��Ī�⣬���ɵ���"
		       "�����⣬��ʽ��ʱ����������"NOR"\n";
		count = me->query_skill("zijinbagua-dao", 1) / 6;
	} else
	{
		msg += HIY "$n" HIY "�ĵ�΢΢һ����������С�Ľ��С�"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);
	me->add("neili", -300);
	me->add_temp("apply/attack", count);

	for (i = 0; i < 5 + random(3) ; i++)
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
