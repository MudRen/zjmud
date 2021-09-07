#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"����"; }

int perform(object me)
{
	string msg;
	object weapon, target;
	int skill, ap, dp, neili_wound, jing_wound;

	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("������������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if (me->query_skill("tanqin-jifa", 1) < 120)
		return notify_fail("��ĵ��ټ������Ҳ�������, ��������������������\n");

	if (me->query_skill("kunlun-jian", 1) < 120)
		return notify_fail("������ؽ����ȼ�����, ��������������������\n");

	if (me->query("max_neili") < 800)
		return notify_fail("���������Ϊ�����޷��ﵽʹ�á���������������ľ��磡\n");

	if (me->query("neili") < 300)
		return notify_fail("����������������㡸���������������������\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = MAG "$N΢΢һЦ�����ֺ��ս�����������ָ��׼" + weapon->name() + NOR +
	      MAG "�������ᵯ��������΢��������������\n��ʱ����һ��������������"NOR"\n";

	skill = me->query_skill("kunlun-jian",1);
	ap = me->query_skill("sword");
	dp = target->query_skill("force");
	if (dp < 1) dp = 1;
	if (random(ap) > dp / 2)
	{
		me->add("neili", -200);
		jing_wound = (int)me->query_skill("sword") +
			   (int)me->query_skill("tanqin-jifa", 1);
		jing_wound = jing_wound / 2 + random(jing_wound / 2);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, jing_wound, 66,
		       MAG "$n��ʱֻ������������������һ��̽�˫����ɲ�Ǽ�ͷ��Ŀѣ��ȫ���ʹ��"NOR"\n");
		me->start_busy(2 + random(2));
	} else
	{
		me->add("neili", -50);
		msg += HIG "����$n��æ���ľ�������������˿������$N�����ĸ��š�"NOR"\n";
		me->start_busy(3);
	}
	message_combatd(msg, me, target);
	return 1;
}

