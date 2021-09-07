// tui.c ��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string query_name() { return "����"ZJBR"һ��"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	string msg;
	int skill, ap, dp, damage;

	if (! target || target == me)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! target || ! me->is_fighting(target))
		return notify_fail("��󡹦������ʽ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

	skill = me->query_skill("hamagong", 1);

	if (skill < 240)
		return notify_fail("��ĸ�󡹦��Ϊ�����������ʹ�á�����ʽ����\n");

	if (me->query("max_neili") < 4000)
		return notify_fail("���������Ϊ��������޷�ʩչ������ʽ����\n");

	if (me->query("neili") < 1000)
		return notify_fail("��������������޷����á�����ʽ����\n");

       if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIY "$N" HIY "���ڵ��ϣ����á���һ����У�˫����"
	      "����룬ƽ�ƶ�����һ�ɼ����������ͬ"
	      "��ɽ����һ�㱼��$n" HIY "��"NOR"\n";

	ap = me->query_skill("force") * 15 + me->query("max_neili");
	dp = target->query_skill("force") * 15 + target->query("max_neili") +
	     target->query_skill("sun-finger", 1) * 20;
	if (dp < 1) dp = 1;
	if (ap / 3 + random(ap) > dp)
	{
		me->add("neili", -400);
		me->start_busy(2);
		damage = (ap - dp) / 10 + random(ap / 10);
		msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 60,
					   HIR "$n" HIR "�����͵�������$P" HIR "�����ƺ�"
					   "�Ⱥƴ�$p" HIR "��ʱ������Ѫ���������ۡ���"
					   "�³���һ����Ѫ��"NOR"\n");
	} else
	if (target->query_skill("sun-finger", 1))
	{
		me->start_busy(2);
		me->add("neili", -300);
		msg += HIG "Ȼ��$p" HIG "����һЦ������һָ�̳�������һ"
		       "��ָ�ľ������������׵Ļ�����$P" HIG "�Ĺ��ơ�"NOR"\n";
	} else
	{
		me->add("neili",-200);
		msg += CYN "����$n" CYN "�������˵�˫���ϣ�������$P"
		       CYN "��һ��֮ʽ��ֻ�������һ�����������"
		       "�������"NOR"\n";
		me->start_busy(3);
		if (! target->is_busy())
			target->start_busy(1);
		if (target->query("neili") > 200)
			target->add("neili", -200);
		else
			target->set("neili", 0);
	}
	message_combatd(msg, me, target);

	return 1;
}
