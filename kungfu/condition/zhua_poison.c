// zhua_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "zhua_poison"; }

string chinese_name() { return "��Ѫ֮��"; }

string update_msg_others()
{
       return HIR "$N��Ȼ����һ������,����¶��ʹ��������Ц�ݡ�"NOR"\n";
}

string update_msg_self()
{
	return HIB "��Ȼһ˿��������������, �����Ľ�������֫��"
		   "�������е���Ѫ��ץ���Է����ˣ�"NOR"\n";
}
