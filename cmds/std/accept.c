// ai.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string r;

	if (arg)
		return 0;

	if (environment(me)->query("pigging"))
		return notify_fail("�㻹�ǰ��ĵĹ���ɣ�\n");

	if (! objectp(ob = STORY_D->query_running_story()) || base_name(ob) != STORY_DIR + "challenge")
		return notify_fail("����û��������ս����Ϲ��ʲô��\n");

	if (me->is_in_prison())
		return notify_fail("�úõ�������ΰɡ�\n");

	if (me->is_ghost())
		return notify_fail("�㻹�ǵȻ�������˵�ɡ�\n");

	if (me->is_busy())
		return notify_fail("��������æ�����п�����˵�ɣ�\n");

	if (me->is_fighting())
		return notify_fail("�㻹�ǰ���ǰ�ĵ��˷ŵ���˵�ɣ�\n");

	if (r = ob->cannot_accept(me))
		return notify_fail(r);

	ob->accept_for_challenge(me);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : accept

����������ս�ߵ���ս����Ȼ������������ս�ſ��ԡ�

�������ָ��: fight, hit

HELP );
	return 1;
}

