#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "cuixin_zhang"; }

string chinese_name() { return "����������"; }

string update_msg_others()
{
       return HIR "$Nһ���Һ�����Ϣ���������ۡ���һ�����һ�����Ѫ��"NOR"\n";
}

string update_msg_self()
{
	return HIR "��ֻ�е������������ڲ�ֹ���綾���ģ����������˴������ƾ��ĸ��ţ�"NOR"\n";
}

