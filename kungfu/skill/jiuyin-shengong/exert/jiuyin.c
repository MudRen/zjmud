// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

string query_name() { return "����"ZJBR"�ķ�"; }
string *pfm_type() { return ({ "xinfa", }); }

int exert(object me, object target)
{
	int skill;

	if (target != me)
		return notify_fail("��ֻ���þ����ķ������Լ���ս������\n");

	if(me->query_skill_mapped("xinfa")!="jiuyin-shengong")
		return notify_fail("�����ķ�����Ҫ�����ķ����ܲ��С�\n");

	if(me->query_skill("xinfa",1)<me->query_skill("jiuyin-shengong",1))
		return notify_fail("��Ļ����ķ��ȼ����ھ����񹦵ȼ������ܷ��ӳ��ķ���������\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("�����������!");

	if ((int)me->query_temp("jiuyin"))
		return notify_fail("���Ѿ����˹����ˡ�\n");

	skill = me->query_skill("xinfa");

	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIY "$N" HIY "�������³���һ������ֻ������ƮƮ��������ģ���Ҫ���"NOR"\n", me);

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
		tell_object(me, "��ľ�����������ϣ��������ջص��\n");
	}
}
