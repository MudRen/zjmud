// zhaichu.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj, item;

	if (! arg)
		return notify_fail("��Ҫժ��ʲô�����ϵ���Ƕ��Ʒ��\n");

	if (me->is_busy())
		return notify_fail("��æ����������������������ɣ�\n");

	if (me->is_fighting())
		return notify_fail("���������ڴ�ܣ�ûʱ������Щ���飡\n");

	if (sscanf(arg,"%s yes",arg)!=1)
	{
		if (! objectp(obj = present(arg, me)))
			return notify_fail("������û�����װ����\n");

		if (! obj->is_item_make() || !obj->query("magic/tessera"))
			return notify_fail("��Ҫժ��ʲô������\n");

		write(ZJOBLONG"��ȷ��Ҫժ��"+obj->short()+"����Ƕ��"+obj->query("magic/tessera")+"��"ZJBR
			"ժ����ʯ��Ҫ����"+obj->query("magic/power")+"��Ҵ���ʯժ�����������ɻָ��������ز�����\n"
			ZJOBACTS2+ZJMENUF(3,3,10,30)+"ȷ��:zhaichu "+arg+" yes"ZJSEP"ȡ��:shake\n");
		return 1;
	}

	if (! objectp(obj = present(arg, me)))
		return notify_fail("������û�����װ����\n");

	if (! obj->is_item_make() || !obj->query("magic/tessera"))
		return notify_fail("��Ҫժ��ʲô������\n");

	if (me->query("balance") < obj->query("magic/power")*10000)
		return notify_fail("��Ǯׯ���㣬���ܽ��б�ʯժ����\n");

	me->add("balance",-obj->query("magic/power")*10000);
	write("�㽫"+obj->short()+"����Ƕ��"+obj->query("magic/tessera")+"ժ����������\n"+obj->query("magic/tessera")+"�����˷�ĩ���紵ɢ�ˡ�\n");
	obj->delete("magic/power");
	obj->delete("magic/type");
	obj->delete("magic/tessera");
	obj->save();
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : zhaichu <����>

���ָ��������㽫ĳ��װ������Ƕ�ı�ʯժ���������Ա�������Ƕ��
HELP
    );
    return 1;
}
