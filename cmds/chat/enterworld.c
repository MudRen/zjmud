// enterworld.c

#include <ansi.h>
#include <net/messaged.h>

inherit F_CLEAN_UP;

string *valid_entry = ({ "/d/city/kedian" });

int main(object me, mapping info)
{
	object env;
	string startroom;

	if (objectp(env = environment(me)) &&
	    env != find_object(VOID_OB))
		return MESSAGE_D->error_msg("�������Ѿ����뵽�������ˡ�\n");

	startroom = info[ARG];
	if (! stringp(startroom) || member_array(startroom, valid_entry) == -1)
		startroom = "/d/city/kedian";

	if (! me->move(startroom))
		return MESSAGE_D->error_msg("ϵͳ���ֹ��ϣ��޷�����������硣\n");

	message("vision", HIC "��������Ȼ������һ�����̣�������������" +
	       me->name() + HIC "�����ӡ�"NOR"\n", environment(me), ({ me }));

	return 1;
}

