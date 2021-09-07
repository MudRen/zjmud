// yuce.c

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }

int perform(object me, object target)
{
	int skill, i;
	int n;
	int my_exp, ob_exp;
	string pmsg;
	string msg;
	object weapon;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���߾�ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("handing")) ||
	    (string)weapon->query("skill_type") != "throwing" ||
	    weapon->query_amount() < 1)
		return notify_fail("���������в�û�����Ű�������ôʩչ���߾���\n");

	if ((skill = me->query_skill("never-defeated", 1)) < 100)
		return notify_fail("��Ĳ����񹦻�򲻹�������ʩչ���߾���\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("�����������ˡ�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	me->add("neili", -120);
	weapon->add_amount(-1);

	msg = HIC "$N" HIC "��ָһ��һ����ֻ����Х�ƿ���������������һ" +
	     weapon->query("base_unit") + weapon->name() + HIC "��������" +
	     "����$n" HIC "��"NOR"\n";

	me->start_busy(1);
	my_exp = me->query_skill("throwing");
	ob_exp = target->query_skill("parry");
	if (random(my_exp) > ob_exp * 2 / 3)
	{
		msg += HIR + "ֻ����" + weapon->name() + HIR "ȥ��ǡ��������磡$n"
		       HIR + "�������ܣ������˸����У��ҽ�һ"
		       "�������˼�����"NOR"\n";
		target->receive_wound("qi", skill / 2 + random(skill / 2), me);
		COMBAT_D->clear_ahinfo();
		weapon->hit_ob(me, target,
			       me->query("jiali") + 150);
		if (stringp(pmsg = COMBAT_D->query_ahinfo()))
			msg += pmsg;
		message_combatd(msg, me, target);
	} else
	{
		msg += CYN "����$p" CYN "��æһ���������$P" HIG "������" +
		       weapon->name() + CYN "��"NOR"\n";
		message_combatd(msg, me, target);
	}

	me->reset_action();
	return 1;
}
