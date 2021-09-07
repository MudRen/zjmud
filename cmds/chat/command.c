// command.c

#include <ansi.h>
#include <net/messaged.h>

inherit F_CLEAN_UP;

int main(object me, mapping info)
{
	string msg;
	seteuid(geteuid());

	if (! is_root(previous_object()))
		return 0;

	if (! info[ARG])
		return 1;

	if (! environment(me) ||
	    environment(me) == find_object(VOID_OB))
		return MESSAGE_D->error_msg("�����ڻ�����翵�����У�ûʲô�����ġ�\n");

	// clear the error
	if (! me->force_me(info[ARG]))
		return MESSAGE_D->error_msg(me->query_temp("notify_fail"));

	return 1;
}

