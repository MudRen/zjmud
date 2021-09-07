// power.c ������
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "������" NOR; }

int perform(object me, string skill)
{
	int count;

	if (me->query("qi") < 80)
		return notify_fail("���������֧���޷�Ѹ�������Լ���ս������\n");

	message_vision(HIY "$N" HIY "˫��һ��һ����ϥ��΢�䣬"
		       "�������ˡ�"NOR"\n", me);
	count = me->query_str();

	if (me->query_temp("special_skill/power", 1))
		return notify_fail("���Ѿ����������Լ���ս�����ˡ�\n");

	me->receive_damage("qi", 40 + random(40));
	me->set_temp("special_skill/power", 1);
	me->add_temp("apply/attack", count);
   	me->start_call_out((: call_other, __FILE__, "remove_effect", me,
			      count :), 60 + random(30));

	return 1;
}

void remove_effect(object me, int count)
{
	me->delete_temp("special_skill/power", 1);
	me->add_temp("apply/attack", -count);
	tell_object(me, "��ʩչ��������������һ������\n");
}
