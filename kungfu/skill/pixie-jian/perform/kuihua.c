// cimu.c  ��а������������ʽ��
// add by Chenzzz 2004-06-04
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"��ʽ"; }

int perform(object me, object target)
{
	int damage;
	string msg;
	object weapon, weapon2;
	int lvl;
	int ap, dp;
	int busy_time;
	int cost_neili;
	int no_exert;
	int point;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! me->query("special_skill/ghost"))
		return notify_fail("�����ǰ�����������������ʽ����ǳ�������óȻʹ�á�\n");
		
	if (target->query_temp("block_msg/all"))
		return notify_fail("�Է�����ʲôҲ������������ĵļ��������ɣ�\n");

	if ((int)me->query_skill("pixie-jian", 1) < 200 )
		return notify_fail("���а����������죬ʹ������������ʽ����\n");

	if (me->query_skill_mapped("force") != "pixie-jian")
		return notify_fail("��û�м�����а����Ϊ�ڹ�������ʩչ��������ʽ����\n");
	if ((int)me->query("max_neili") < 2500)
		return notify_fail("��������Ϊ���㣬�޷�����������\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail(HIC"����������������û�ܽ�����Ŀ��ʹ�꣡"NOR"\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		msg = HIC "$N" HIC "һ����Ц��������ָ��£���ֱ۱�����Ѹ���쳣�ִ�$n"
		      HIC "˫Ŀ��"NOR"\n";
	else
		msg = HIC "$N" HIC "һ����Ц������" + weapon->name() +
		      HIC "һ�񣬽���һ�㱩�����ִ�$n"
		      HIC "����˫Ŀ��"NOR"\n";
		      
	ap = (int)me->query_skill("force");
	dp = (int)target->query_skill("force");
	lvl = (int)me->query_skill("pixie-jian", 1);
	busy_time = 1;
	cost_neili = 100;
	
	if (random(ap) > dp / 2)
	{
		busy_time += 1;		
		cost_neili += 150;
		damage = lvl + (int)me->query_skill("sword", 1) / 2;
		damage = damage / 2 + random(damage);
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage / 2, me);
		msg += HIC "$n" HIC "ֻ��������һ�㣬˫Ŀһ���ʹ����ǰһ"
		       "�ڣ���ʲôҲ�������ˣ���ʱ����ʹ��������"NOR"\n";
		msg += HIC "\n$N" HIC "һ�е��֣��漴�������Ц�����Ц��$n"
		       HIC "���ɾ���һ��͸�Ǻ��⡣"NOR"\n";
		ap += ap * 3 / 10;
		message_combatd(msg, me, target);
		target->set_temp("block_msg/all", 1);
		call_out("cimu_end", (int) 5 + random(lvl / 25), me, target);
	} else
	{
		busy_time += random(3);
		cost_neili += 100;
		msg += HIY "$p" HIY "�鼱������̧��Ҳ��$P"
		       HIY "�����۴�ȥ���ȵ�$P" HIY "�ؽ�Ծ����"NOR"\n";
		message_combatd(msg, me, target);
	}
	
	if (objectp(weapon2 = target->query_temp("weapon")) && ! random(3))
	{
		if (! objectp(weapon = me->query_temp("weapon")) ||
		    (string)weapon->query("skill_type") != "sword")
			msg = HIC "ͻȻ$N" HIC "��ָ���һָ��һ������ָ��ֱ��$n"
			      HIC "����" +weapon2->name() + NOR HIC "������"NOR"\n";				 
		else
			msg = HIC "ͻȻ$N" HIC "����" + weapon->name() + NOR
			      HIC "�й�ֱ����ֱ��$n" HIC "����" +weapon2->name() + NOR 
			      HIC "������"NOR"\n";  
		if (ap / 3 + random(ap) > dp && random(2))
		{
			busy_time += 1;
			cost_neili += 150;
			msg += HIM "$n" HIM "ֻ������һ���ʹ������" + weapon2->name() + 
			       HIM "��Ҳ����ס�����ֶ��ɣ�"NOR"\n";
			weapon2->move(environment(target));
		}
		else
		{
			busy_time += random(3);
			cost_neili += 100;
			msg += CYN "����$n" CYN "������$N" CYN "����ͼ�������б��л�"
			       "����ܲ�͸�磬������$N" CYN "��һ�С�"NOR"\n";	 
		}
		message_combatd(msg, me, target);
	}
	else if (!target->is_busy() && random(2))
	{
		msg = HIC "$N" HIC "���Ӻ������ˣ��������ȣ����ι����쳣����$n"
		      HIC "���Ʈ��������"NOR"\n";
		if (ap / 2 + random(ap) > dp)
		{
			msg += HIC "$p" HIC "��ʱֻ���ۻ����ң�ֻ�ܽ����Ż�����"
			       "�����Գ�����"NOR"\n";
			target->start_busy(ap / 22 + 2);
			cost_neili += 150;
		} else
		{
			msg += CYN "����$p" CYN "������$P" CYN "��������û����"
			       "���κ�Ӱ�졣"NOR"\n";
			busy_time += random(3);
			cost_neili += 100;
		}
		message_combatd(msg, me, target);	       
	}
	else
	{
		msg = HIC "����$n" HIC "��æ����֮ʱ��$N"
		      HIC "��Ȼת�����һָ����$n"
		      HIC "�ı��ġ�"NOR"\n";  
		if (ap / 2 + random(ap) > dp)
		{
			damage = ap / 2 + random(ap);
			msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
					   HIC "$n" HIC "ȫȻ�޷���ܣ�$N"
					   HIC "����ָ�˶�����������$p" 
					   HIC "�ı��ģ���Ѫ��ʱ�ɽ�"
					   "������"NOR"\n");
			busy_time += 1;
			cost_neili += 150;
		} else
		{
			msg += CYN "����$p" CYN "������$P" CYN "��һ�У���æ֮�б任��ʽ��"
			       "û�ܵ��κ��˺���"NOR"\n";
			busy_time += random(3);
			cost_neili += 100;
		}
		message_combatd(msg, me, target);	   
	}

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		msg = HIC "ֻ��$N" HIC "���˼�����������ָ���һ����ָ����$n"
		      HIC "�����Ѩ����������"NOR"\n";			     
	else
		msg = HIC "��Ȼ$N" HIC "Ʈǰ������" NOR + weapon->name() + NOR
		      HIC "�����֣�������ָ��Ȼ����$n"
		      HIC "�����Ѩ����������"NOR"\n";   
		      
	if (ap / 4 + random(ap) > dp && target->query_temp("shield") && random(2))
	{
		point = target->query_temp("apply/armor") / 2;
		target->add_temp("apply/armor", - point);
		me->start_call_out((: call_other, __FILE__, "remove_effect_shield", target, point :), me->query_skill("force") / 3);
		busy_time += 1;
		cost_neili += 100;
		msg += HIW "$n" HIW "ֻ���õ���һ˿��ʹ��������������ɢ�õ�Ȼ�޴棡"NOR"\n";
		message_combatd(msg, me, target);
	}
	else if (ap / 4 + random(ap) > dp && target->query_temp("powerup") && random(2))
	{
		point = target->query_temp("apply/attack") / 2;
		target->add_temp("apply/attack", - point);
		target->add_temp("apply/defense", - point);
		me->start_call_out((: call_other, __FILE__, "remove_effect_powerup", target, point :), me->query_skill("force") / 3);
		busy_time += 1;
		cost_neili += 100;
		msg += HIW "$n" HIW "ֻ���õ���һ˿��ʹ��һ��������Ȼ����$n"
		       HIW "����֮�ڣ���ʱ�������ڵ����ڵ������ݻ٣�"NOR"\n";
		message_combatd(msg, me, target);
	}
	else if (ap / 3 + random(ap) > dp && random(2))
	{
		msg += HIW "$n" HIW "ֻ���õ���һ˿��ʹ������������Ȼ���ܿ��ƣ�"
		       HIW "�ӵ���ԴԴ��й��"NOR"\n";
		target->add("neili", - ap * 2);
		if (target->query("neili") < 0)
			target->set("neili", 0);

		if (random(2) &&  target->query("no_exert/until") < time() + ap / 10)
		{
			no_exert = ap / 40 + random(ap / 40);
			if (target->query("no_exert/until") > 0)
				target->add("no_exert/until", 
					    no_exert);
			else target->set("no_exert/until", time() +
					 no_exert);
						
			target->set("no_exert/msg", "���ڹ�Ϊ��а�������ƣ��޷�"
						    "����������\n");
		}
		message_combatd(msg, me, target);
	}
	else
	{
		msg += CYN "����$p" CYN "ʶ������������������˼���������$P" 
		       CYN "�Ĺ��ơ�"NOR"\n";  
		message_combatd(msg, me, target);		
	}
	me->start_busy(busy_time);
	me->add("neili", -cost_neili);
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
		tell_object(target, HIR "������Ĩ������ǰ����Ѫ���ܿ����ˡ�"NOR"\n");
	}
	return;
}

void remove_effect_shield(object target, int amount)
{
	if (target && living(target))
	{
		target->add_temp("apply/armor", amount);
		tell_object(target, "���ù�����Ļ����������������ˡ�\n");
	}
}

void remove_effect_powerup(object target, int amount)
{
	if (target && living(target))
	{
		target->add_temp("apply/attack", amount);
		target->add_temp("apply/defense", amount);
		tell_object(target, "���ù����㵤���ڵ��������������ˡ�\n");
	}
}

