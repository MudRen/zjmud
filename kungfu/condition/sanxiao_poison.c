// sanxiao_poison.c

#include <ansi.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "sanxiao_poison"; }

string chinese_name() { return "��ң��Цɢ֮��"; }

string update_msg_others()
{
       return HIG "$N" HIG "���Ϻ�Ȼ¶�������һЦ��"NOR"\n";
}

string update_msg_self()
{
	return HIG "��֪��ô�ģ����Ȼ�����Լ����Ʋ����������⣬����������Ц��һ�£�"NOR"\n";
}

string die_msg_others()
{
	return RED "$N" RED "����¶�������Ц�ݣ��ƺ����Ҹ���"NOR"\n";
}

string die_reason(string name)
{
	return "����" + chinese_name() + "���Ҹ������������һ����";
}

int jing_damage(object me, mapping cnd)
{
	int d;

	d = cnd["level"];
	if (me->query_skill("xingxiu-poison") > 50) d /= 2;
	return d / 2;
}

int qi_damage(object me, mapping cnd)
{
	int d;

	d = cnd["level"];
	if (me->query_skill("xingxiu-poison") > 50) d /= 2;
	return d;
}

