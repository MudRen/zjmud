#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "bingcan_duzhang"; }

string chinese_name() { return "���Ϻ���"; }

string update_msg_others()
{
       return HIW "$N" HIW "�Һ�һ������ɫ���࣬ȫ���ֳ�һ�㺮������ס�Ĳ�����"NOR"\n";
}

string update_msg_self()
{
	return HIW "��ֻ���������ģ�ȫ�����Ҫ����һ�㡣"NOR"\n";
}

