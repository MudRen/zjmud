// he.c ��Ů��-˫�����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "˫��"ZJBR"���"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("˫�����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ�������񣬲���ʹ��˫����赡�\n");

	if (me->query_skill("zuoyou-hubo", 1) < 150)
		return notify_fail("������һ���֮����δ�������ң����Է�ʹ�����ֽ��С�\n");

	if ((int)me->query_skill("yunv-jian", 1) < 120)
		return notify_fail("�����Ů����������죬����ʹ��˫����赡�\n");

	if ((int)me->query_skill("quanzhen-jian", 1) < 120)
		return notify_fail("���ȫ�潣��������죬����ʹ��˫����赡�\n");

	if ((int)me->query("neili", 1) < 400)
		return notify_fail("����������̫��������ʹ��˫����赡�\n");

	if (me->query_skill_mapped("sword") != "yunv-jian")
		return notify_fail("��û�м�����Ů����������ʹ��˫����赡�\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "������ȫ�潣�����⣬���ֻ���Ů������"
	      "�У�˫�����ͬʱ�̳���"NOR"\n";

	ap = me->query_skill("zuoyou-hubo", 1) + me->query_skill("sword", 1) +
	     (me->query_skill("yunv-jian", 1) + me->query_skill("quanzhen-jian", 1)) / 2;
	dp = target->query_skill("parry") * 2 + target->query_skill("zuoyou-hubo", 1);
	me->start_busy(3);
	if (ap / 2 + random(ap) > dp)
	{
		damage = 100 + ap / 2 + random(ap / 2);
		me->add("neili", -250);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 58,
					   HIR "$n" HIR "����$N" HIR "˫�����裬��ʽ������"
					   "������Ϊ��һ����ȥ������֪����Ǻã�\n"
					   HIR"һ��֮�£�$N" HIR "�Ľ����Ѿ���ʽ���룡$n"
					   HIR "һ���ҽ�֮�£���ʱ�����ش���"NOR"\n");
	} else
	if (target->query_skill("zuoyou-hubo", 1) >= 100)
	{
		msg += CYN "����$p" CYN "˿�����ң������ַ�ʹ�����书�мܣ���$P"
		       CYN "�Ĺ���ȫȻ���⡣"NOR"\n";
	} else
	{
		msg += CYN "����$p" CYN "������$P" CYN "����ͼ����"
		       "�Լ���ȫ�����»����ܲ�͸�磬��$P" CYN "�޼ƿ�ʩ��"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
