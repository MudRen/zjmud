// ss_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "ss_poison"; }

string chinese_name() { return "������֮��"; }

string update_msg_others()
{
       return HIR "$N" HIR "ͻȻ���ڵ��ϣ�˫��������һ����ץ��"NOR"\n";
}

string update_msg_self()
{
	return HIB "��Ȼһ�ɺ�������һ������ӿ�����������е������������ˣ�"NOR"\n";
}
