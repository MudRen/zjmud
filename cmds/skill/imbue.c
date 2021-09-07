// imbue.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string item, imbue;
	object obj, dest;

	if (! arg)
		return notify_fail("��Ҫ��ʲô�����Ͻ���������Ʒ��\n");

	//if (!wizardp(me)) return notify_fail("���ܸ��²����У��Ժ󿪷ţ�\n");

	if (me->is_busy())
		return notify_fail("��æ����������������������ɣ�\n");

	if (me->is_fighting())
		return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

	if (! objectp(obj = present(arg, me)))
		return notify_fail("������û���������������������롣\n");

	notify_fail(obj->name() + "�޷���͸��\n");
	return obj->do_imbue(me);
}

int help(object me)
{
write(@HELP
ָ���ʽ : imbue <����>

���ָ��������㽫ĳ��������Ʒ��������һ�ֵ����У��Զ�������
���߻��Ƿ�������������
HELP
    );
    return 1;
}
