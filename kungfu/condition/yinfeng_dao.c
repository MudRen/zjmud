#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "yinfeng_dao"; }

string chinese_name() { return "����ι�֮��"; }

string update_msg_others()
{
       return HIW "$N�Һ�һ����ֻ��ȫ�������Ҫ˺�ѿ�һ�㣬����ĺ��鲻ס�ĵ��¡�"NOR"\n";
}

string update_msg_self()
{
	return HIW "��е�һ���й��溮���˿ڴ����𣬿������������絶�ھ��ĸ��ţ�"NOR"\n";
}

