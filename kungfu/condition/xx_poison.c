// xx_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "xx_poison"; }

string chinese_name() { return "�����ƶ�"; }

string update_msg_others()
{
       return HIG "$N" HIG "������ͻȻ�������Σ����ظ�������������"NOR"\n";
}

string update_msg_self()
{
	return HIB "��Ȼһ��̹ǵ��溮Ϯ�������е������ƶ������ˣ�"NOR"\n";
}
