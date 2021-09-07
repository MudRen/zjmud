// maxsuck.c

#include <ansi.h>

inherit F_SSERVER;

string query_name() { return "��ڤ"ZJBR"����"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int sp, dp;
	int my_max, tg_max;
	int sucked;

	if (! target || target == me) target = offensive_target(me);

	if (environment(me)->query("no_fight"))
		return notify_fail("�����ﲻ�ܹ������ˡ�\n");

	if (! objectp(target) || ! me->is_fighting(target))
		return notify_fail("��Ҫ��ȡ˭�ĵ�Ԫ��\n");

	if (target->query("race") != "����" ||
	    target->query("not_living"))
		return notify_fail("����ˣ�ֻ�л��ŵ���������е�Ԫ��\n");

	my_max = me->query("max_neili");
	tg_max = target->query("max_neili");

	if (me->query_temp("sucked"))
		return notify_fail("��ո���ȡ����Ԫ��\n");

	if (objectp(me->query_temp("weapon")))
		return notify_fail("�������ֲ���ʩ�ñ�ڤ�����˵�Ԫ��\n");

	if (! me->is_fighting() || ! target->is_fighting())

	if ((int)me->query_skill("beiming-shengong", 1) < 90)
		return notify_fail("��ı�ڤ�񹦹���������������ȡ�Է��ĵ�Ԫ���\n");

	if ((int)me->query("neili") < 20)
		return notify_fail("�����������������ʹ�ñ�ڤ�񹦡�\n");

	if ((int)me->query_current_neili_limit() <= my_max)
		return notify_fail("����ڹ�ˮƽ���ޣ�����ȡҲ��ͽ�͡�\n");

	if ((int)target->query("max_neili") < 100)
		return notify_fail( target->name() +
			"��Ԫ��ɢ������δ�ۣ����޷�����������ȡ�κζ�����\n");

	if ((int)target->query("max_neili") < (int)me->query("max_neili") / 5)
		return notify_fail( target->name() +
			"���ڹ���ΪԶ�����㣬���޷�����������ȡ��Ԫ��\n");

	message_combatd(HIG "$N" HIG "ȫ��һ��������֣���������$n"
			HIG "���ֱ��ϡ�"NOR"\n", me, target);

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

		sucked = 1 + (me->query_skill("beiming-shengong", 1) - 90) / 10;
		target->add("max_neili", -sucked);
		if (target->query("max_neili") < 1)
			target->set("max_neili", 0);
		if (my_max > tg_max + 100)  sucked /= 2;
		if (my_max > tg_max + 200)  sucked /= 2;
		if (my_max > tg_max + 400)  sucked /= 2;
		if (my_max > tg_max + 800)  sucked /= 2;
		if (my_max > tg_max + 1600) sucked /= 2;
		if (my_max > tg_max + 3200) sucked /= 2;

		if (sucked < 1)
			tell_object(me, HIG "�����㷢�ֶԷ�����"
				    "�ƺ�������̫�࣬һʱ����������Ϊ���á�"NOR"\n");
		else
			me->add("max_neili", sucked);

		me->start_busy(4 + random(4));
		if (! target->is_busy()) target->start_busy(2);
		me->add("neili", -10);

		call_out("del_sucked", 10, me);
	}
	else
	{	
		message_combatd(HIY "����$p" HIY "������$P" HIY
				"����ͼ����������˿�ȥ��"NOR"\n",
				me, target);
		me->start_busy(7);
		call_out("del_sucked", 20, me);
	}

	return 1;
}

void del_sucked(object me)
{
	me->delete_temp("sucked");
}
