// enchase.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string item, tessera;
	object obj, dest;

	if (! arg)
		return notify_fail("��Ҫǿ��ʲôװ����\n");

	if (me->is_busy())
		return notify_fail("��æ����������������������ɣ�\n");

	if (me->is_fighting())
		return notify_fail("���������ڴ�ܣ�ûʱ������Щ���顣\n");

	if (sscanf(arg, "%s with %s", item, tessera) != 2 && sscanf(arg, "%s in %s", tessera, item) != 2)
		return notify_fail("��Ҫ��ʲô����ǿ��ʲôװ����\n");

	if (! objectp(obj = present(tessera, me)))
		return notify_fail("������û������������������ǿ����\n");

	if (! obj->query("item_exp"))
		return notify_fail("��ѡ�õĵ��߲�������ǿ��װ����\n");

	if (! objectp(dest = present(item, me)))
		return notify_fail("������û������װ����\n");

	if (dest->query("equipped"))
		return notify_fail("��ȡ��װ������ǿ����\n");

	notify_fail("���޷���" + obj->name() + "ǿ��" + dest->name() + "��\n");
	return dest->do_enhance(me, obj);
}

int help(object me)
{
write(@HELP
ָ���ʽ : enhance <������Ʒ> with <����>

���ָ�����������ĳ��������Ʒǿ��װ����ʹ��װ���ɳ���
HELP
    );
    return 1;
}
