// sanyin.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "sanyin"; }

string chinese_name() { return "�������צ֮��"; }

string update_msg_others()
{
       return "$NͻȻ����ס�Ķ���������ȥʮ��ʹ�ࡣ\n";
}

string update_msg_self()
{
	return HIB "��Ȼ�������֫�������ƺ�������С�������ߣ��������̣�"NOR"\n";
}

