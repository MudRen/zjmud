// mystery.c ���ƾ���
// Created by Doing Lu 10/7/2K

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "���ƾ���" NOR; }

int perform(object me, string skill)
{
	return notify_fail("������ܹ���������������������Ҫ���á�\n");
}
