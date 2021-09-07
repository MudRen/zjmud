// huixiang.c �������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }

int perform(object me)
{
	string msg;
	object weapon2, target;
	int skill, ap, dp, mp, np, damage;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (userp(me) && ! me->query("can_perform/shenlong-bashi/huixiang"))
		return notify_fail("�㻹����ʹ�á�������衹��\n");

	if (! me->is_fighting(target))
		return notify_fail("��������衹ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	skill = me->query_skill("shenlong-bashi", 1);

	if (! objectp(weapon2 = target->query_temp("weapon")))
		return notify_fail("�Է�û��ʹ�ñ���������ʹ�á�������衹��\n");

	if (skill < 160)
		return notify_fail("���������ʽ�ȼ�����, ����ʹ�á�������衹��\n");

	if (me->query("max_neili") < 1500)
		return notify_fail("���������Ϊ���㣬����ʹ�á�������衹��\n");

	if (me->query("neili") < 500)
		return notify_fail("�����������������ʹ�á�������衹��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIM "ͻȻ$N" HIM "������ǰ���ߣ�����˳��һ��" +
	      weapon2->name() + HIM "�������ڱ���һ�㡣"NOR"\n";
	message_combatd(msg, me, target);

	ap = me->query_skill("dodge", 1) / 3 + skill;
	dp = target->query_skill("dodge", 1);
	mp = me->query_skill("hand", 1);
	np = target->query_skill("parry", 1);

	if (mp / 2 + random(mp) > np)
	{
		if (ap / 2 + random(ap) > dp)
		{
			me->add("neili", -300);
			target->receive_damage("qi", ap + random(ap), me);
			target->receive_wound("qi", ap / 2 + random(ap) / 2, me);

			msg = HIM "$N" HIM "��������һ����ֻ���׹�һ����" +
			      weapon2->name() + HIM "����$n"
			      HIM "�ؿڣ�$n" HIM "������������" +
			      weapon2->name() + HIM "�������ţ�"NOR"\n";
			me->start_busy(2 + random(4));
			weapon2->move(environment(me));
	   
		} else
		{
			me->add("neili", -100);
			msg = CYN "$n" CYN "��һ����" + weapon2->name() + "���ֶ�"
			      "��������$n" CYN "���Ų�æ������һ�������ţ��˵�һ"
			      "����" + weapon2->name() +" �����ؿ��ӹ���"NOR"\n"; 
			me->start_busy(3);
			weapon2->move(environment(me));
		}
	} else
	{       
		me->add("neili", -80);
		msg = CYN "$n" CYN "�����ֿ죬����һĨ" +
		      weapon2->name() + CYN "�ܿ�����һ�С�"NOR"\n"; 
		me->start_busy(1 + random(2));
	}

message_combatd(msg, me, target);
return 1;
}

