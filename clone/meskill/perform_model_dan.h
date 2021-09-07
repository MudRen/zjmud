
#include <ansi.h>
#include <combat.h>

#define PFM "��" HIW "<������>" NOR "��"

inherit F_SSERVER;
#include <balance.h>

string *weapon_sk = ({
	"sword", "blade", "staff", "whip", "club", "hammer", "axe"
});

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
	int attack;

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
		attack = WEAPON_ATTACK;
		if (! objectp(weapon = me->query_temp("weapon"))
		   || (string)weapon->query("skill_type") != "BASE_SKILL")
			return notify_fail("����ʹ�õ��������ԣ�����ʩչ" PFM "��\n");
	} else
	{
		attack = UNARMED_ATTACK;
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
	 
	if (ap * 2 / 3 + random(ap * 2) > dp)
	{
		damage = da_power(me, "BASE_SKILL") * 3;
		msg += COMBAT_D->do_damage(me, target, attack, damage, 100, HIM "<PFM��������>" + ""NOR"\n");
		me->add("neili", -200);
		me->start_busy(1);
		if (! target->is_busy())
			target->start_busy(2);
	} else
	{
		msg += NOR + CYN "<PFMʧ������>" + ""NOR"\n";
		me->add("neili", -100);
		me->start_busy(2);
	}
		
	message_sort(msg, me, target);
	return 1;
}


