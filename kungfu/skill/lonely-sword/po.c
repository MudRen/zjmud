// po.c ���¾Ž�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "�Ʊ�ʽ"; }

int perform(object me, object target)
{
	string msg;
	string *learned;
	object weapon, weapon2;
	string type;
	mapping prepare;
	int n;
	int skill, ap, dp, damage, ss;

	me->clean_up_enemy();
	if (! target) target = me->select_opponent();

	skill = me->query_skill("lonely-sword", 1);

	if (! me->is_fighting(target))
		return notify_fail("���¾Ž�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (skill < 50)
		return notify_fail("��Ķ��¾Ž��ȼ�������������������\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	weapon2 = target->query_temp("weapon");
	prepare = target->query_skill_prepare();
	if (weapon2) type = weapon2->query("skill_type");
	else if (! prepare || sizeof(prepare) == 0) type = "unarmed";
	else if (sizeof(prepare) == 1) type = (keys(prepare))[0];
	else if (sizeof(prepare) == 2) 
		type = (keys(prepare))[target->query_temp("action_flag")];

	ap = skill + me->query_skill("sword", 1) / 2;
	learned = me->query("can_perform/lonely-sword");
	if (arrayp(learned) && member_array(type, learned) != -1)
		ap *= 2;
      ap +=	me->query_skill("sword-cognize", 1)*2;

      if (me->query("family/family_name")=="��ɽ����")
            ap += skill;

	ss = target->query_skill("never-defeated", 1) * 11 / 10;
	if (ss < target->query_skill("lonely-sword", 1))
		  ss = target->query_skill("lonely-sword", 1);

	dp = target->query_skill(type, 1) * 2 + ss * 2 + target->query_skill("sword-cognize", 1) * 2;

	if (ap / 2 + random(ap) > dp)
	{
		msg = HIC "$N" HIC "����������е�" + weapon->name() + HIC
		      "�����дӳ��䲻��ķ�λֱָ$n" HIC +
		      to_chinese(type)[4..<1] + "�е�������"NOR"\n";
		n = 3 + random(5);
		if (target->is_busy() || ap / 3 + random(ap) > dp)
		{
			msg += HIY "$n" HIY "���һ��������֮������������$N" HIY "������" +
			       chinese_number(n) + "����"NOR"\n";
			message_combatd(msg, me, target);
			me->start_busy(1 + random(n));
			while (n-- && me->is_fighting(target))
			{
				if (! target->is_busy() && random(2))
					target->start_busy(1);
				COMBAT_D->do_attack(me, target, weapon, 0);
			}

			if (weapon2 && random(ap) > dp && type != "pin")
			{
				msg = HIW "\n$n" HIW "������ǰ�ۻ����ң����е�" + weapon2->name() +
				      HIW "һʱ��Ȼ����ס�����ֶ�����"NOR"\n";
				weapon2->move(environment(me));
			} else
			{
				msg = HIY "\n$n" HIY "�Եÿ�϶��Ϣ��һʱ��ȴҲ����������"NOR"\n";
			}
		} else
		{
			msg += HIY "$n" HIY "��æ�ֵ���һʱ�䲻����æ���ң���Ͼ������"NOR"\n";
			me->start_busy(1);
			target->start_busy(1 + random(skill / 20));
		}
	} else
	{
		msg = HIC "$N" HIC "�������е�" + weapon->name() + HIC "��������ָ��"
		      "����$n" HIC "���ص��쳣���ܣ�$N" HIC "һʱ��Ȼ�޷��ҵ�������"NOR"\n";
		me->start_busy(3 + random(2));
	}

	message_combatd(msg, me, target);
	return 1;
}
