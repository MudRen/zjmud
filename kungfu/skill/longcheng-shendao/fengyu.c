// fengyu.c ���꽻��

#include <ansi.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int count;
	int lvl;
	int i;
 
	if (userp(me) && ! me->query("can_perform/longcheng-shendao/fengyu"))
		return notify_fail("�㲻��ʹ�á����꽻�ӡ���\n");

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����꽻�ӡ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
	if (!objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("ʩչ�����꽻�ӡ����б�������һ�ѵ���\n");

	if ((int)me->query("neili") < 270)
		return notify_fail("��������������޷�ʩչ�����꽻�ӡ���\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹����޷�ʩչ�����꽻�ӡ���\n");

	if ((lvl = (int)me->query_skill("longcheng-shendao", 1)) < 120)
		return notify_fail("��������񵶻������ң��޷�ʹ�þ��������꽻�ӡ���\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "���һ�������е�" + weapon->name() +
	      HIC "�����һ����$n" HIC "��ȥ��$n" HIC "��ͬС��һ���ڵ�����Ư��������"NOR"\n";

	if (lvl / 2 + random(lvl) > target->query_skill("parry") * 2 / 3)
	{
		msg += HIY "�����Ʊ仯Ī�⣬$n" HIY "��ʱ�����ۻ����ң��޷��ֵ���"NOR"\n";
		count = lvl / 5;
		me->add_temp("apply/attack", count);
	} else
	{
		msg += HIC "$n" HIC "����������Ȼ�������а��С�ʹ����������ֵ���"NOR"\n";
		count = 0;
	}

	message_combatd(msg, me, target);
	me->add("neili", -120);

	for (i = 0; i < 5; i++)
	{
		if (! me->is_fighting(target))
			break;
		COMBAT_D->do_attack(me, target, weapon, 0);
	}

	me->start_busy(1 + random(5));
	me->add_temp("apply/attack", -count);

	return 1;
}
