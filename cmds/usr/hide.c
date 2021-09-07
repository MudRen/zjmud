// hide.c ���ر���

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
	object ob;
	int i;

	if (! str)
		return notify_fail("��Ҫ����ʲô��Ʒ��\n");

	if (! stringp(me->query("can_summon/" + str)))
		return notify_fail("�㲻֪��������������Ʒ��\n");

	if (! objectp(ob = present(str, me)) && ! objectp(ob = present(str, environment(me))))
		return notify_fail("�����û�������Ʒ��\n");

	if (! ob->hide_anywhere(me))
	{
		message_vision(HIM "$N" HIM "����" + ob->name() + HIM "�����������дʡ�\nȻ��ʲôҲû�з��� :)\n", me);
	}

	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : hide <��Ʒ��ID>

��ָ�����������ĳЩ��Ʒ����������ʱ��ʧ��
HELP
    );
    return 1;
}

