// iceshock.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "iceshock"; }

string chinese_name() { return "����"; }

string update_msg_others()
{
       return HIR "$N��Ȼ����һ�����¡�"NOR"\n";
}

string update_msg_self()
{
	return HIB "����þ�������˱�����һ���������Ǻ��������ˣ�"NOR"\n";
}
