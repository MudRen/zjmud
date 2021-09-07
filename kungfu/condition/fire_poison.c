// fire_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "fire_poison"; }

string chinese_name() { return "���޶���"; }

string update_msg_others()
{
	return HIR "$N" HIR "һ���Һ���ȫ��ȼ����" NOR + HIG "����ɫ" NOR + HIR "�Ļ��档"NOR"\n";
}

string update_msg_self()
{
	return HIR "��ֻ��ȫ�������ޱȣ�ȫ���ȼ���" NOR + HIG "����" NOR + HIR "ֱ�����衣"NOR"\n";
}


