#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "ningxue_shenzhao"; }

string chinese_name() { return "��Ѫ֮��"; }

string update_msg_others()
{
       return HIR "$N" HIR "ֻ����Ϣ���ͣ����ۡ���һ�����һ�����Ѫ��"NOR"\n";
}

string update_msg_self()
{
	return HIR "��ֻ����Ϣ���ͣ�ȫ��ѪҺ�������Ŀ�ʼ����������"NOR"\n";
}

