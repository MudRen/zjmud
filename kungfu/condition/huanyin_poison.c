// huanyin_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "huanyin_poison"; }

string chinese_name() { return "��������"; }

string update_msg_others()
{
       return HIG "$N" HIG "��ʹ���������һ����������"
	      "����һ�ɵ�����������"NOR"\n";
}

string update_msg_self()
{
	return HIB "��Ȼһ�����Ե���Ķ�������͸����"
	       "֫���࣬͸�������⡣"NOR"\n";
}

int jing_damage(object me, mapping cnd)
{
	return cnd["level"] / 6;
}

int qi_damage(object me, mapping cnd)
{
	return cnd["level"] / 3;
}
