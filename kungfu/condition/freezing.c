// freezing.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "freezing"; }

string chinese_name() { return "���Ϻ���"; }

string update_msg_others()
{
	switch (random(3))
	{
	case 0:
		return HIW "$N" HIW "������ͻȻһ�Σ���ɫ��ò԰ף����ݲ�ס�Ĵ����"NOR"\n";

	case 1:
		return HIW "$N" HIW "΢΢����һ��������ʹ���쳣��"NOR"\n";

	default:
		return HIW "$N" HIW "������һ�£�������������һ���˪��"NOR"\n";
	}
}

string update_msg_self()
{
	return HIG "��Ȼ����һ���䣬������������"NOR"\n";
}

string die_reason()
{
	return "������������������";
}
