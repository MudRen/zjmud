// agile.c �������
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "�������" NOR; }

int perform(object me, string skill)
{
	int count;

	if (me->query("qi") < 80)
		return notify_fail("���������֧���޷����������Լ����ٶȡ�\n");

	message_vision(HIC "$N" HIC "�ż�һ�㣬����һЩ��"
		       "���������˶�ʱ��ֽͬ��һ��ƮƮ������"NOR"\n", me);
	count = me->query_dex();

	if (me->query_temp("special_skill/agile", 1))
		return notify_fail("���Ѿ������������Լ����ٶ��ˡ�\n");

	me->receive_damage("qi", 40 + random(40));
	me->set_temp("special_skill/agile", 1);
	me->add_temp("apply/dodge", count);
   	me->start_call_out((: call_other, __FILE__, "remove_effect", me,
			      count :), 60 + random(30));

	return 1;
}

void remove_effect(object me, int count)
{
	me->delete_temp("special_skill/agile");
	me->add_temp("apply/dodge", -count);
	tell_object(me, "����������ʩչ��ϣ�����һ�٣�������������\n");
}
