// po.c ���־�

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"���"; }

int perform(object me, object target)
{
	string msg;
	object weapon, weapon2;
	int n,i;
	int skill, skill2, ap, dp, damage;
	string type;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	skill = me->query_skill("never-defeated", 1);

	skill2 = me->query_skill("martial-cognize", 1);

	if (! me->is_fighting(target))
		return notify_fail("���־�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")))
		return notify_fail("������ֱֳ��в���ʩչ���־���\n");

	type = weapon->query("skill_type");
	if (me->query_skill(type, 1) < 150)
		return notify_fail("���" + to_chinese(type) + "ˮƽ���ޣ��޷�ʩչ���־���\n");

	if (me->query_skill_mapped(type) != "never-defeated")
		return notify_fail("��û�м��������񹦣��޷�ʩչ���־���\n");

	if (skill < 100)
		return notify_fail("��Ĳ����񹦵ȼ��������޷�ʩչ���־���\n");

	if (me->query("neili") < 150)
		return notify_fail("����������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	me->add("neili", -100);

	if(userp(target)) ap = me->query_skill(type) + skill2 + me->query_skill("count",1);
	else ap = me->query_skill(type) + me->query_skill("count",1);
	dp = target->query_skill("parry") +
	     target->query_skill("martial-cognize", 1);

	n = 4 + random(4);

	msg = HIC "$N" HIC "����" + weapon->name() +
	      HIC "һ��������ҹ�����ǣ�����" + chinese_number(n) + "�й���$n"
	      HIC "��û�а���ؿ�ѭ��"NOR"\n";
	message_combatd(msg, me, target);

	me->add_temp("apply/damage", skill/5);
	for (i = 0; i < n; i++)
		      {
		            if (! me->is_fighting(target))
			            break;
				if (random(2) && ! target->is_busy())
					target->start_busy(1);
				COMBAT_D->do_attack(me, target, weapon, 0);
			}
	me->add_temp("apply/damage", -skill/5);

      if (living(target)) {
			weapon2 = target->query_temp("weapon");
			if (weapon2 && random(ap) / 2 > dp && weapon2->query("type") != "pin")
			{
				msg = HIW "$n" HIW "������ǰ�ۻ����ң����е�" + weapon2->name() +
				      HIW "һʱ��Ȼ����ס�����ֶ�����"NOR"\n";
				weapon2->move(environment(me));
	                  message_combatd(msg, me, target);
			} 

	msg = HIY "$N" HIY "��" + chinese_number(n) + "�м�����׾����ͬ�������κ���ʽ��"NOR"\n";

	if (ap / 2 + random(ap) > dp) {
			msg += HIY "$n" HIY "������Ϊ���ң�һʱ���������������ڵ���ȫȻ�޷�������"NOR"\n";
			target->start_busy(4 + random(skill / 50));

	} else
	{
		msg += HIC "����$n" HIC "һ˿�����������Ż���û��¶�����������"NOR"\n";

	}
	message_combatd(msg, me, target);
      }
	me->start_busy(3 + random(2));
	return 1;
}
