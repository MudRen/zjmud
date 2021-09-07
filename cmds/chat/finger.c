// finger

#include <ansi.h>
#include <net/messaged.h>

inherit F_CLEAN_UP;

int main(object me, mapping info)
{
	string msg;
	string fun;

	if (! stringp(info[ARG]))
		return MESSAGE_D->error_msg("��������Ҫ��ѯ���û����š�\n");

	msg = FINGER_D->finger_user(info[ARG], me);
	if (sscanf(info[ARG], "%*s@%*s") == 2)
	{
		// finger remote user ?
		fun = FUN_TELL; // Only message to user
		msg = HIY + msg + NOR;
	} else
	{
		fun = FUN_NOTICE;
		msg = HIW "�����û�(" + info[ARG] + ")�Ĳ�ѯ��Ϣ��\n"
		      NOR + msg;
	}

	MESSAGE_D->tell_user(me, fun, msg);
	return 1;
}

