// team command: talk

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object *t;

	if (! arg) arg = "...";

	if (! pointerp(t = me->query_team()))
		return notify_fail("�����ڲ�û�кͱ�����ɶ��顣\n");

	if (me->ban_say(1))
		return 0;

	message("team", HIW "�����顿" + me->name(1) +"��" + arg + ""NOR"\n", t);
	return 1;
}
