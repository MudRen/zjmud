// lucky.c ���˵�ͷ
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "���˵�ͷ" NOR; }

int perform(object me, string skill)
{
	return notify_fail("������ܸ�������ܺõ�����������Ҫ���á�\n");
}
