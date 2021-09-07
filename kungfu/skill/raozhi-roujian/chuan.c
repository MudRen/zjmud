#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
string query_name() { return "����"ZJBR"����"; }

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
	int damage;
 
	if (! target) target = offensive_target(me);

	if (userp(me) && ! me->query("can_perform/raozhi-roujian/chuankong"))
		return notify_fail("�����ڻ�����ʹ�á����´��ա���һ�У�\n");

	if (! target || ! me->is_fighting(target))
		return notify_fail("�����´��ա�ֻ����ս���жԶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	      (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("force") < 150)
		return notify_fail("����ڹ�����Ϊ������ʹ���������´��ա���һ�У�\n");

	if (me->query_skill("raozhi-roujian", 1) < 90)
		return notify_fail("�����ָ�ὣ��Ϊ������ʹ���������´��ա���һ�У�\n");

	if (me->query("neili") < 250)
		return notify_fail("�������������ʹ���������´��ա���һ�У�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIM "$N" HIM "�͵���һ����Х���������䣬�Ǳ�" + weapon->name() + HIM
		  "���Ƴ���һ��������������ۣ�Ʈ�������������䵱�ɵ�\n"
		  "��ʮ���С���ָ�ὣ���е�һ�С����´��ա���ֻ��$N" 
		  HIM + weapon->name() + HIM "���Ƴ��գ�����$n" HIM "���ţ�"
		  "������;��\n����΢������Ȼ���˹�ȥ��б��$p" HIM "�Ҽ硣"NOR"\n";

	ap = me->query_skill("sword");
	dp = target->query_skill("parry");

	if (ap / 2 + random(ap) > dp)
	{
		damage = ap / 2 + random(ap);
		me->add("neili", -150);
		me->start_busy(2);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
					   HIR "���$n" HIR "һ����������$N" HIR
					   "����Ľ��д��У�һ���Һ�����Ѫ�ɽ�������"NOR"\n");
	} else
	{
		me->add("neili", -60);
		me->start_busy(3);
		msg += CYN "����$p" CYN "�������ң�������������񵲿���$P"
		       CYN "�Ľ��С�"NOR"\n";
	}

	message_combatd(msg, me, target);

	return 1;
}
