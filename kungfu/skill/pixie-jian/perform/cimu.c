// cimu.c  ��а��������Ŀ��

#include <ansi.h>

inherit F_SSERVER;
string query_name() { return "����"ZJBR"��Ŀ"; }
int perform(object me, object target)
{
	int damage;
	string msg;
	object weapon;
	int lvl;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("����Ŀ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (target->query_temp("block_msg/all"))
		return notify_fail("�Է�����ʲôҲ������������ĵļ��������ɣ�\n");

	if ((int)me->query_skill("pixie-jian", 1) < 80 )
		return notify_fail("���а����������죬ʹ��������Ŀ����\n");

	if ((int)me->query("max_neili")<400)
		return notify_fail("��������Ϊ���㣬�޷�����������\n");

	if ((int)me->query("neili")<200)
		return notify_fail(HIC"����������������û�ܽ�����Ŀ��ʹ�꣡"NOR"\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		msg = HIC "$N" HIC "������ָ��£���ֱ۱�����Ѹ���쳣�ִ�$n"
		      HIC "˫Ŀ��"NOR"\n";
	else
		msg = HIC "$N" HIC "����" + weapon->name() +
		      HIC "һ�񣬽���һ�㱩�����ִ�$n"
		      HIC "����˫Ŀ��"NOR"\n";
	if (random(me->query_skill("force")) > target->query_skill("force") / 2)
	{
		me->start_busy(2);
		lvl = (int)me->query_skill("pixie-jian", 1);
		damage = lvl + (int)me->query_skill("sword", 1) / 2;
		damage = damage / 2 + random(damage / 2);
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage / 2, me);
		msg += HIC "$n" HIC "ֻ��������һ�㣬˫Ŀһ���ʹ����ǰһ"
		       "�ڣ���ʲôҲ�������ˣ���ʱ����ʹ��������"NOR"\n";
		message_combatd(msg, me, target);
		me->add("neili", -damage / 5);
		target->set_temp("block_msg/all", 1);
		call_out("cimu_end", (int) 2 + random(lvl / 25), me, target);
	} else
	{
		me->start_busy(2);
		msg += HIY "$p" HIY "�鼱������̧��Ҳ��$P"
		       HIY "�����۴�ȥ���ȵ�$P" HIY "�ؽ�Ծ����"NOR"\n";
		message_combatd(msg, me, target);
	}
	return 1;
}

void cimu_end(object me, object target)
{
	if (target && living(target) &&
	    target->query_temp("block_msg/all"))
	{
		message_combatd("$NĨ��Ĩ����" HIR "��Ѫ" NOR
				"�������ܿ����ˡ�\n", target);
		target->set_temp("block_msg/all", 0);
		tell_object(target, HIR "������Ĩ������ǰ����"
			    "Ѫ���ܿ����ˡ�"NOR"\n");
	}

	return;
}
