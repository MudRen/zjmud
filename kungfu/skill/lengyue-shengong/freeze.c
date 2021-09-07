// freeze.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me);

string query_name() { return "����"ZJBR"�̹�"; }
string *pfm_type() { return ({ "force", }); }

int exert(object me, object target)
{
	int ap;
	int dp;
	int damage;
	string msg;

	if (target == me || ! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

	if (! me->is_fighting(target))
		return notify_fail("��ֻ���ú�������ս���еĶ��֡�\n");

	if (me->query_skill("lengyue-shengong", 1) < 150)
		return notify_fail("��������񹦻�򲻹����޷����ú�����\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("�������������");

	if (! living(target))
	      return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

	msg = HIW "$N" HIW "Ĭ�������񹦣�һ�ɺ���ӭ������$n"
	      HIW "�����ܵ�ʱѩ��ƮƮ��"NOR"\n";

	ap = me->query_skill("force");
	dp = target->query_skill("force");

	me->start_busy(2);

	if (ap / 2 + random(ap) > dp)
	{
		damage = ap + random(ap / 3);
		target->receive_damage("qi", damage, me);
		target->receive_wound("qi", damage, me);
		if (target->query("neili") > damage)
			target->add("neili", -damage);
		else
			target->set("neili", 0);

		msg += HIG "$n" HIG "��Ȼ����һ��͸�Ǻ��⣬��ʱ��"
		       "�����ѪҺ������Ҫ�����ˡ�"NOR"\n";
		if (! target->is_busy())
			target->start_busy(1);

		target->set_temp("lengyue-shengong_freeze", 1);
		target->start_call_out((: call_other, __FILE__, "remove_effect", target :),
				       me->query_skill("lengyue-shengong") / 5);

	} else
		msg += HIY "$n" HIY "�е�һ�������ĵ׷�����æ"
		       "�˶��ֿ����������¡�"NOR"\n";

	message_combatd(msg, me, target);

	return 1;
}

void remove_effect(object me)
{
	if ((int)me->query_temp("lengyue-shengong_freeze"))
	{
		me->delete_temp("lengyue-shengong_freeze");
		tell_object(me, HIY "��е���ߵĺ�������ɢȥ�ˡ�"NOR"\n");
	}
}

