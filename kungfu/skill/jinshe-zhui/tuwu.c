// tuwu.c

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }

int perform(object me, object target)
{
	int skill;
	string msg;
	object weapon;

	if (me->query_temp("jinshe/tuwu"))
		return notify_fail("����õĽ�������û�����žͳ��С�\n");

	if (! target) target = offensive_target(me);
	if (! target ||	! me->is_fighting(target))
		return notify_fail("��������ֻ����ս����ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("handing")) ||
	    (string)weapon->query("id") != "jinshe zhui" ||
	    weapon->query_amount() < 1)
	   	return notify_fail("������û�ý���׶������ʹ�þ��У�\n");

	if ((skill = me->query_skill("jinshe-zhui", 1)) < 100)
		return notify_fail("��Ľ���׶��������죬����ʹ�ý�������\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("�����������ˡ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	weapon->add_amount(-1);

	msg = HIY "$N" HIY "һ����Х������΢�������н���׶��Ȼ���Ϸ�"
	      "�����˸�Ȧ�����Ѹ��Ϯ��$n" HIY "����ǰ��"NOR"\n";

	if (skill / 2 + random(skill) > target->query_skill("dodge", 1))
	{
		me->add("neili", -200);
		target->receive_damage("qi", (int)skill / 3, me);
		target->receive_wound("qi", (int)skill / 3, me);
	
		msg += HIM "ֻ��һ����ɨҶ��������У�$N" HIM "���е�"
		       "����׶������Ŀ�Ĺ�â����ҫ��$n" HIM "��ð�𻨣�"
		       "\n������ǰһ���ص������⣬$n" HIM
		       "ɶҲ�������ˣ�"NOR"\n";
		message_combatd(msg, me, target);
		me->set_temp("jinshe/tuwu", 1);
		target->set_temp("block_msg/all", 1);
		me->start_call_out((: call_other, __FILE__, "tuwu_me_end", me :),
				   skill / 30);
		target->start_call_out((: call_other, __FILE__, "tuwu_target_end", target :),
				   skill / 30);
	} else
	{
		msg += CYN "$n" CYN "���а���һ������æ��"
		       "�ˣ���������ö����׶��"NOR"\n";
		message_combatd(msg, me, target);
	}

	me->reset_action();
	return 1;
}

void tuwu_me_end(object me)
{
	me->delete_temp("jinshe/tuwu");
}

void tuwu_target_end(object target)
{
	if (living(target))
	{
		message_combatd("$NĨ��Ĩ������" HIR "��Ѫ" NOR "�������������ۡ�\n",
				target);
		target->set_temp("block_msg/all", 0);
		tell_object(target, HIR "������Ĩ������������Ѫ����������Χ���龰��"NOR"\n");
	}
}
