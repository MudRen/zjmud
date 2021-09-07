// huagu.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit "/inherit/condition/damo";

string name() { return "damo_shangshen"; }

string chinese_name() { return "����֮��"; }

string update_msg_others()
{
       return HIC "$N" HIC "ҡͷ���ԣ����۾����������ˣ�����ȥ����֮����"NOR"\n";
}

string update_msg_self()
{
	return HIR "ֻ�����Լ����񲻼ã�ƣ���������������ܵ���Ħ���񽣵ĸ��š�"NOR"\n";
}

string die_msg_others()
{
	return RED "$N" RED "��������˼�����������Ҳû�а�㶯����"NOR"\n";
}

string die_reason()
{
	return "����˥��������";
}

int jing_damage(object me, mapping cnd)
{
	int d;

	d = cnd["level"];

	if (d > 300 )
		d = 100 + (d - 300) / 12;
	else
	if (d > 60)
		d = 60 + (d - 60 ) / 6;
	d /= 3;
	if (d < 10) d = 10;

	return d / 2 + random(d);
}
