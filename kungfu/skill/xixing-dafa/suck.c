// suck.c

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "��ȡ"ZJBR"����"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int sp, dp;
	int my_max, tg_max;
	int amount;
	object weapon;

	if (! target || target == me) target = offensive_target(me);

	if (environment(me)->query("no_fight"))
		return notify_fail("�����ﲻ�ܹ������ˡ�\n");

	if (! objectp(target) || ! me->is_fighting(target))
		return notify_fail("��ֻ����ȡս���еĶ��ֵĵ�Ԫ��\n");

	if (target->query("race") != "����" ||
	    target->query("not_living"))
		return notify_fail("����ˣ�ֻ�л��ŵ���������е�Ԫ��\n");

	my_max = me->query("max_neili");
	tg_max = target->query("max_neili");

	if (me->query_temp("sucked"))
		return notify_fail("��ո���ȡ����Ԫ��\n");

	if ((int)me->query_skill("xixing-dafa", 1) < 200)
		return notify_fail("������Ǵ���δ��ɣ���"
				   "������ȡ�Է��ĵ�Ԫ��Ϊ���ã�\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�����������������ʹ�����Ǵ󷨡�\n");

	if ((int)me->query_current_neili_limit() <= my_max)
		return notify_fail("����ڹ�ˮƽ���ޣ�����ȡҲ��ͽ�͡�\n");

	if ((int)target->query("max_neili") < 100)
		return notify_fail( target->name() +
			"��Ԫ��ɢ������δ�ۣ����޷�����������ȡ�κζ�����\n");

	if ((int)target->query("max_neili") < (int)me->query("max_neili") / 5)
		return notify_fail( target->name() +
			"���ڹ���ΪԶ�����㣬���޷�����������ȡ��Ԫ��\n");

	if (! objectp(weapon = me->query_temp("weapon")))
		message_combatd(HIR "$N" HIR "̽�����֣�ƽƽ������$n"
				HIR "����ǰ���ƺ�û�а��������"NOR"\n",
				me, target);
	else
		message_combatd(HIR "$N" HIR "�����е�" + weapon->name() +
				HIR "һ������ı���$n" HIR + "��$p"
				HIR "��æ��ס��"NOR"\n",
				me, target);

	if (living(target) && !target->is_killing(me))
	{
		me->want_kill(target);
		target->kill_ob(me);
	}

	sp = me->query_skill("force");
	dp = target->query_skill("force");

	me->set_temp("sucked", 1);

	if ((sp + random(sp) > dp + random(dp) ) || ! living(target))
	{
		tell_object(target, HIR "��ֻ��ȫ������ȫ������"
			    "��ѩ����ʧ����Ӱ���٣�"NOR"\n");
		tell_object(me, HIG "�����" + target->name() +
			    HIG "�ĵ�Ԫ������ԴԴ���������˽�����"NOR"\n");

		amount = 1 + (me->query_skill("xixing-dafa", 1) - 120) / 10;
		target->add("max_neili", -amount);
		me->add("max_neili", amount);
		me->add("exception/xixing-count", amount * 10);
		SKILL_D("xixing-dafa")->check_count(me);
		if (target->query("max_neili") < 1)
			target->set("max_neili", 0);

		me->start_busy(4 + random(4));
		if (! target->is_busy()) target->start_busy(2);
		me->add("neili", -10);

		me->start_call_out((: call_other, __FILE__, "del_sucked", me :), 20);
	} else
	{	
		message_combatd(HIY "����$p" HIY "������$P" HIY
				"����ͼ��������������$P" HIY
				"���漴���˿�ȥ��"NOR"\n",
				me, target);
		me->start_busy(7);
		me->start_call_out((: call_other, __FILE__, "del_sucked", me :), 20);
	}

	return 1;
}

void del_sucked(object me)
{
	if (objectp(me))
		me->delete_temp("sucked");
}

