// cut.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string part;
	string who;

	if (! arg)
		return notify_fail("��Ҫ��ʲô������\n");

	if (sscanf(arg, "%s from %s", part, who) != 2)
	{
		part = "?";
		who = arg;
	}

	if (! objectp(ob = present(who, environment(me))))
		return notify_fail("�㸽��û������������\n");

	if (ob == me)
		return notify_fail("���Լ�������ë������\n");

	if (ob->query("can_speak"))
		return notify_fail("������Ҳ�Ҹ�Ҵ�ô��\n");

	notify_fail("��û�еط����֡�\n");
	return ob->do_cut(me, part);
}

int help(object me)
{
	write( @HELP
ָ���ʽ: cut <something> from sth. | <sb>.

��ĳ�������������һ�����������磺
cut head from corpse
cut middle finger from arm

���� cut ? from sth ������ҵ����ֵĲ�λ��

HELP );
	return 1;
}
