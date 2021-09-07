// chat command: say.c

#include <ansi.h>
#include <net/messaged.h>

inherit F_CLEAN_UP;

int main(object me, mapping info)
{
	object env;
	string msg;

	if (! objectp(env = environment(me)) || env == find_object(VOID_OB))
		return MESSAGE_D->error_msg("����������翵�����У�û"
					    "�������õ���˵�Ļ���\n");

	if (! stringp(msg = info[MESSAGE]))
		return MESSAGE_D->error_msg("��Ҫ˵ʲô����\n");

	message_vision(CYN "$N" CYN "˵����" + msg + ""NOR"\n", me);
	return 1;
}

