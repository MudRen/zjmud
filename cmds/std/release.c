// fang.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	if (! arg)
		return notify_fail("��Ҫ��˭�����ϵ��\n");

	if (! objectp(ob = present(arg, environment(me))))
		return notify_fail("��Ҫ��˭�����ϵ��\n");

	if (ob->query_temp("owner") != me)
		return notify_fail("�㲢����" + ob->name() + "�����˰�����ʲô����\n");

	if (ob->query("can_speak"))
		message_vision("$N�����߰ɣ�" + ob->name() +
			       "�����߰ɡ�\n", me, ob);
	else
		message_vision("$N�ܴȱ��ذ�$n���룬����ع���Ȼ�ˡ�\n", me, ob);

	if (me->query_temp("comedby") == ob)
		me->delete_temp("comedby");

	ob->delete_temp("owner");
	ob->delete_temp("owner_id");
	ob->delete_temp("owner_name");
	ob->set_leader(0);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : release <����>

��ָ�����������ĸ����߻���ѱ���Ķ��������ū״̬��

HELP );
	return 1;
}
