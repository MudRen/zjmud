
#include <ansi.h>
#include <combat.h>

#define PFM "��" HIW "<������>" NOR "��"

inherit F_SSERVER;

string *weapon_sk = ({
	"sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int count;
	int i, attack_time;

	if (! me->query("can_perform/" + "SKILL" + "/" + "E_NAME"))
		return notify_fail("�㻹û���ܵ�����ָ�㣬����������" PFM "��\n");

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail(PFM "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (member_array("BASE_SKILL", weapon_sk) != -1)
	{
		if (! objectp(weapon = me->query_temp("weapon"))
		   || (string)weapon->query("skill_type") != "BASE_SKILL")
			return notify_fail("����ʹ�õ��������ԣ�����ʩչ" PFM "��\n");
	} else
	{
		if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
			return notify_fail(PFM "ֻ�ܿ���ʹ�á�\n");	     
	}
	
	if ((int)me->query_skill("SKILL", 1) < 400)
		return notify_fail("��" + to_chinese("SKILL") + "������죬����ʩչ" PFM "��\n");

	if (member_array("BASE_SKILL", weapon_sk) == -1)
	{
		if (me->query_skill_prepared("BASE_SKILL") != "SKILL")
			return notify_fail("��û��׼��" + to_chinese("SKILL") + "������ʩչ" PFM "��\n");
	}
	
	if (me->query("neili") < 300)
		return notify_fail("�����ڵ���������������ʩչ" PFM "��\n");

	if (! living(target))
		return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "<PFM��������>" + "\n" + NOR;

	ap = me->query_skill("BASE_SKILL");
	dp = target->query_skill("parry");
	attack_time = 6;

	if (ap * 2 / 3 + random(ap * 2) > dp)
	{
		msg += HIM "<PFM��������>" + ""NOR"\n";
		count = ap / 10;
		me->add_temp("apply/attack", count);
		me->add_temp("apply/damage", count);
	} else
	{
		msg += NOR + CYN "<PFMʧ������>" + ""NOR"\n";
		count = 0;
	}

	message_sort(msg, me, target);

	attack_time += me->query("jieti/times") * 2;
	if (attack_time > 13)
		attack_time = 13;

	me->add("neili", -attack_time * 20);

	for (i = 0; i < attack_time; i++)
	{
		if (! me->is_fighting(target))
			break;

		if (random(2) && ! target->is_busy()) target->start_busy(1);

		COMBAT_D->do_attack(me, target, (member_array("BASE_SKILL", weapon_sk) == -1 ? 0 : weapon), 0);
	}
	me->add_temp("apply/attack", -count);
	me->add_temp("apply/damage", -count);
	me->start_busy(3 + random(attack_time/ 3));

	return 1;
}


