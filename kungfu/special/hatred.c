// hatred.c ɱ��
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "ɱ��" NOR; }

int perform(object me, string skill)
{
	int count;

	if (me->query("qi") < 80)
		return notify_fail("���������֧���޷����������Լ����˺�����\n");

	if (me->query_temp("special_skill/hatred", 1))
		return notify_fail("�������Ѿ���ɱ�������ˡ�\n");

	message_vision(HIR "$N" HIR "���о��������������ɨ��"
		       "���ܣ�һ�ɺ�����Ȼ����"NOR"\n", me);
	switch (me->query("character"))
	{
	case "��������":
		count = 30;
		break;

	case "�ĺ�����":
		count = 42;
		break;

	case "������":
		count = 38;
		break;

	case "���ռ�թ":
		count = 48;
		break;
	}

	me->set_temp("special_skill/hatred", 1);
	me->receive_damage("qi", 40 + random(40));
	me->add_temp("apply/damage", count);
	me->add_temp("apply/unarmed_damage", count);
   	me->start_call_out((: call_other, __FILE__, "remove_effect", me,count :), 60 + random(30));

	return 1;
}

void remove_effect(object me, int count)
{
	me->delete_temp("special_skill/hatred");
	me->add_temp("apply/damage", -count);
	me->add_temp("apply/unarmed_damage", -count);
	tell_object(me, "�㾫��һ��и��ɱ����Ȼ�޴档\n");
}
