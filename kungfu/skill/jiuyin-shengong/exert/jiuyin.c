// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "九阴"ZJBR"心法"; }
string *pfm_type() { return ({ "xinfa", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("你只能用九阴心法提升自己的战斗力。\n");

	if(me->query_skill_mapped("xinfa")!="jiuyin-shengong")
		return notify_fail("运用心法，需要激发心法技能才行。\n");

	if(me->query_skill("xinfa",1)<me->query_skill("jiuyin-shengong",1))
		return notify_fail("你的基本心法等级低于九阴神功等级，不能发挥出心法的威力。\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("你的内力不够!");

	if ((int)me->query_temp("jiuyin"))
		return notify_fail("你已经在运功中了。\n");

	skill = me->query_skill("xinfa");

	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIY "$N" HIY "缓缓的吐出了一口气，只见衣袖飘飘、气涨如鼓，似要飞扬！"NOR"\n", me);

	me->add_temp("apply/attack", skill * 2 / 5);
	me->add_temp("apply/defense", skill * 2 / 5);
	me->set_temp("jiuyin", 1);

	me->start_call_out((: call_other, __FILE__, "remove_effect",me, skill * 2 / 5 :), skill);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int amount)
{
	if ((int)me->query_temp("jiuyin"))
	{
		me->add_temp("apply/attack", -amount);
		me->add_temp("apply/defense", -amount);
		me->delete_temp("jiuyin");
		tell_object(me, "你的九阴神功运行完毕，将内力收回丹田。\n");
	}
}
