// chat command: tell.c

#include <net/messaged.h>

inherit F_CLEAN_UP;

int main(object user, mapping info)
{
	if (! stringp(info[MSGTO]))
		return MESSAGE_D->error_msg("��Ҫ����Ϣ��˭��\n");

	if (! stringp(info[MESSAGE]))
		return MESSAGE_D->error_msg("��Ҫ˵ʲô����\n");

	return MESSAGE_D->send_msg_to(user, info[MSGTO], info[MESSAGE]);
}

