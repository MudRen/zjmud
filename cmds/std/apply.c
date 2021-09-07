// apply.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	int count;
	object ob;
	object *guard;

	if (! arg)
		return notify_fail("��Ҫʹ��ʲô������\n");

	if (! objectp(ob = present(arg, me)))
	{
		ob = present(arg, environment(me));

		if (! objectp(ob))
			return notify_fail("������û����������������Ҳû�С�\n");
	}

	if (! undefinedp(count = ob->query_amount()) && count < 1)
		return notify_fail(ob->name() + "�Ѿ������ˡ�\n");

	if (me->is_busy())
	{
		write("����һ��������û����ɡ�\n");
		return 1;
	}

	if (guard = ob->query_temp("guarded"))
	{
		guard = filter_array(guard, (: objectp($1) && present($1, environment($(me))) && living($1) && ($1 != $(me)) :));
		if (sizeof(guard))
			return notify_fail(guard[0]->name()	+ "������" + ob->name() + "һ�ԣ���ֹ�κ������ߡ�\n");
	}

	if (ob->query("can_be_applied"))
	{
		return ob->do_apply(me);
	} else
		return notify_fail("��ô��" + ob->name() + "��\n");

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : apply <��Ʒ>

���ָ�������������������Ʒ���������Ĺ�Ч��
 
HELP );
	return 1;
}
