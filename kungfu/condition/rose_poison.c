// rose_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "rose_poison"; }

string chinese_name() { return "��õ�嶾"; }

string update_msg_others()
{
       return "$N���˸���ս�����˼�����\n";
}

string update_msg_self()
{
	return HIG "���е�" HIR "�ۻ�õ�嶾��" HIG "�����ˣ�\n";
}
