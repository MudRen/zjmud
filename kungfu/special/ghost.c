// ghost.c ����
// Created by chenzzz 2004/05/28

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "����" NOR; }

int perform(object me, string skill)
{
	return notify_fail("�����ʹ�����Ѫ��һ�����٣�����Ҫʹ�á�\n");
}
