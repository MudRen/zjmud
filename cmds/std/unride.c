// Filename : /cmds/std/unride.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me)
{
	object ob;

	if (! objectp(ob = me->query_temp("is_riding")))
		return notify_fail("����ʲô�£�������û���\n");

	message_vision("$N��$n�Ϸ������¡�\n", me, ob);
	ob->move( environment(me) );
	ob->delele_temp("is_rided_by");
	me->delete_temp("is_riding");
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : unride | xia
 
���ָ�������������ŵ���ѱ���Ķ�������������
 
HELP );
    return 1;
}
