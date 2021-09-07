// ci.c �̽�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"�̽�"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int ap, dp;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}
	if (! target || ! me->is_fighting(target))
		return notify_fail("���̽���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");
		
	if ((int)me->query_skill("xiyang-jian", 1) < 70)
		return notify_fail("���������������죬����ʹ�á��̽�����\n");
				
	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���Ϊ�����ߣ��������á��̽�����\n");
			
	if ((int)me->query("neili") < 300)
		return notify_fail("��������������������ʹ�á��̽�����\n");

	if (me->query_skill_mapped("sword") != "xiyang-jian")
		return notify_fail("��û�м���������������죬����ʹ�á��̽�����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "\n$N" HIC "һ�����ڣ����е�" +
	      weapon->name() + HIC "����һ���������$n" HIC "����ǰ��"NOR"\n";

	ap = me->query_skill("sword");
	dp = target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap * 2 / 3);
		me->add("neili", -70);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
					   HIR "$n" HIR "��æ�мܣ�ȴ������һ��������"
					   "һ�����ô����ؿڣ���Ѫ�ɽ���"NOR"\n");
		me->start_busy(2);
	} else 
	{
		msg += CYN "Ȼ��$p" CYN "�����ֿ죬���Ų�æ�Ľ�$P"
		       CYN "�Ľ��мܿ���"NOR"\n";
		me->add("neili", -30);
		me->start_busy(3);
	}
	message_combatd(msg, me, target);

	return 1;
}
