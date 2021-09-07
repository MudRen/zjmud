//ice_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "ice_poison"; }

string chinese_name() { return "�����ƶ�"; }

string update_msg_others()
{
       return HIB "$N������ͻȻ�������Σ����ظ�������������"NOR"\n";
}

string update_msg_self()
{
	return HIB "��Ȼһ���溮�ӵ�������������֫�ٺ������еĺ�������֮�������ˣ�"NOR"\n";
}

int dispel(object me, object ob, int duration)
{
	if (me->query_skill_mapped("force") != "jiuyang-shengong")		
		return -1;

	::dispel(me, ob, duration);
	return 1;
}
