// zhi.c ������ָ

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"��ָ"; }

int perform(object me, object target)
{
	string msg;
	object weapon;
	mapping prepare;
	string type;
	int n;
	int skill, ap, dp, damage;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	skill = me->query_skill("jiuyin-shengong", 1);

	if (! me->is_fighting(target))
		return notify_fail("������ָֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (skill < 150)
		return notify_fail("��ľ����񹦵ȼ��������޷�ʩչ������ָ��\n");

	if (me->query("neili") < 150)
		return notify_fail("��������������������ʩչ������ָ��\n");

	prepare = me->query_skill_prepare();
	if (! sizeof(prepare) || ! stringp(type = keys(prepare)[0]))
		type = "unarmed";

	if (me->query_skill_mapped(type) != "jiuyin-shengong")
		return notify_fail("��û�н������񹦼�����" + to_chinese(type) +
				   "�ϣ��޷��Դ�ʩչ�����񹦣�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	me->add("neili", -100);

	ap = skill * 3 / 2 + me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);

	msg = HIY "$N" HIY "���ֳ�ָ�����������ƺ�������$n"
	      HIY + "��ʽ�е�������"NOR"\n";
	if (ap / 2 + random(ap * 2) > dp)
	{
		n = 4 + random(4);
		if (target->is_busy() || ap / 2 + random(ap) > dp)
		{
			msg += HIY "$n" HIY "����ָ�����ޱȣ�ȫȻ�޷��ֵ�������֮������������$N"
			       HIY "��������" + chinese_number(n) + "ָ��"NOR"\n";
			message_combatd(msg, me, target);
			me->start_busy(1 + random(n));
			while (n-- && me->is_fighting(target))
			{
				if (random(2) && ! target->is_busy())
					target->start_busy(1);
				COMBAT_D->do_attack(me, target, 0, 0);
			}

			weapon = target->query_temp("weapon");
			if (weapon && random(ap) / 2 > dp && weapon->query("type") != "pin")
			{
				msg = HIW "$n" HIW "������ǰ�ۻ����ң����е�" + weapon->name() +
				      HIW "һʱ��Ȼ����ס�����ֶ�����"NOR"\n";
				weapon->move(environment(me));
			} else
			{
				msg = HIY "$n�����ֵ���һʱ����Ҳ����������"NOR"\n";
			}
		} else
		{
			msg += HIY "$n" HIY "�������룬��æ�ֵ���ȫȻ�޷�������"NOR"\n";
			me->start_busy(1);
			target->start_busy(4 + random(skill / 30));
		}
	} else
	{
		msg += HIC "����$n" HIC "�����Ż�����¶���������"NOR"\n";
		me->start_busy(3 + random(2));
	}

	message_combatd(msg, me, target);
	return 1;
}
