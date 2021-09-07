// san.c ��Ůɢ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "��Ů"ZJBR"ɢ��"; }
string *pfm_type() { return ({ "strike", }); }

int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("��Ůɢ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if ((int)me->query_skill("sanhua-zhang", 1) < 135)
		return notify_fail("���ɢ���Ʒ�������죬����ʹ����Ůɢ����\n");

	if ((int)me->query_skill("force") < 180)
		return notify_fail("����ڹ���Ϊ����������ʩչ��Ůɢ����\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�����������������޷�ʹ����Ůɢ����\n");

	if (me->query_skill_mapped("strike") != "sanhua-zhang") 
		return notify_fail("��û�м���ɢ���ƣ��޷�ʹ����Ůɢ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "����һЦ��˫��һ����Ȼ��������"
	      "��Ӱ������ǧ��ֻ����һ�빥��$n" HIY "��"NOR"\n";

	if (random(me->query_skill("strike")) > target->query_skill("dodge") / 2)
	{
		me->start_busy(2);
		damage = me->query_skill("strike");
		damage = damage / 2 + random(damage / 2);
		me->add("neili", -150);
		msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
					   HIR "���$p" HIR "û�ܱܿ�$P" HIR
					   "���Ī����Ʒ�����������������ƣ�"
					   "����ÿ�����Ѫ������ˤ����"NOR"\n");
	} else
	{
		me->start_busy(3);
		me->add("neili", -50);
		msg += CYN "����$p" CYN "ʶ����$P"
		       CYN "��һ�У�ббһԾ�ܿ���"NOR"\n";
	}
	message_combatd(msg, me, target);

	return 1;
}
