// mie.c  �ط�����������𽣡�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"; }
string *pfm_type() { return ({ "sword", }); }

int perform(object me, object target)
{
	int damage;
	string msg;
	object weapon;
	int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("���𽣡�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("ûװ������ôʹ�á��𽣡���\n");

	if ((int)me->query_skill("huifeng-jian", 1) < 60 )
		return notify_fail("��Ļط��������������죬��ʹ�������𽣡���\n");

	if (me->query_skill_mapped("sword") != "huifeng-jian")
		return notify_fail("��û�м����ط��������������ʹ�á��𽣡���\n");

	if ((int)me->query_skill("force") < 120)
		return notify_fail("����ڹ���򲻹�������ʩչ���𽣡���\n");

	if ((int)me->query("neili") < 200)
	       return notify_fail("��������������������ʩչ���𽣡���"NOR"\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIC "$N" HIC "���г�����âԾ�������Ⱪ�����ó�������ɫ�ʣ����⽥\n"
	      "���ƽ�$n" HIC "��$p" HIC "�������콣�⣬�����Ծ��ֻ��һɲ�����콣\n"
	      "Ӱ��Ϊһ��ֱ��$n" HIC "ǰ�أ�������ף�ֻ��һ����"NOR"\n";

	ap = me->query_skill("force") + me->query_skill("sword");
	dp = target->query_skill("force") + target->query_skill("parry");
	if (ap / 2 + random(ap) > dp)
	{
		me->start_busy(2);
		damage = (int)me->query_skill("huifeng-jian", 1);
		damage += random(damage);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
					   HIR "$n" HIR "ȫȻ�޷���ܣ�" + weapon->name() +
					   HIR "�˶�����������$n" HIR "�ؿڣ���ʱ��Ѫ�ɽ���"NOR"\n");
		me->add("neili", -150);
	} else
	{
		me->start_busy(3);
		msg += YEL "����$p" YEL "����һЦ��������ת����"
		       "����ָ��������$P" YEL "�Ľ��ϣ�" + weapon->name() +
		       YEL "��$p" YEL "��໮�����о����ա�"NOR"\n";
		me->add("neili", -60);
	}
	message_combatd(msg, me, target);
	return 1;
}
