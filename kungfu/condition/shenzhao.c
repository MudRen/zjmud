#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "shenzhao"; }

string chinese_name() { return "���վ��ھ�"; }

string update_msg_others()
{
       return HIR "ֻ��$N" HIR "ǺǺ��������������ҡ�Σ�˫"
	      "�Ƚ����������ƺ�������һ�㡣"NOR"\n";
}

string update_msg_self()
{
	return HIW "��ֻ����Ϣ���ͣ�����������һ�����ǵ�ͨ"
	       "�죬��Ҫ������"NOR"\n";
}

int jing_damage(object me, mapping cnd)
{
	return cnd["level"] / 8;
}

int qi_damage(object me, mapping cnd)
{
	return cnd["level"] / 4;
}

