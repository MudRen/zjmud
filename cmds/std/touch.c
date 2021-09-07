// touch.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj;
	string obj_id;
	object *obj_list;

	if (! arg)
		return notify_fail("��Ҫ����ʲô��Ʒ��\n");
	if (! wizardp(me)) return notify_fail("�����һ�֣�ȴ��ץ��ס��ʲô��\n");
	if (sscanf(arg, "my %s", obj_id))
	{
		obj_list = all_inventory(me);

		if (! obj_list)
			obj_list = all_inventory(environment(me));
		else obj_list += all_inventory(environment(me));
		
		foreach (obj in obj_list)
		{
			if (obj->query("id") == obj_id &&
			    obj->query("owner/" + me->query("id")))
			{
				if (obj->is_character())
					return notify_fail("����Ҷ�" + obj->name() + "�ˡ�\n");
	
				notify_fail("������һ��" + obj->name() + "��\n");
				return obj->do_touch(me);
			}
		}
		return notify_fail("����û����Ķ�����\n");
	}

	if (! objectp(obj = present(arg, me)) &&
	    ! objectp(obj = present(arg, environment(me))))
		return notify_fail("������û����������������Ҳû�С�\n");

	if (obj->is_character())
		return notify_fail("����Ҷ�" + obj->name() + "�ˡ�\n");

	notify_fail("������һ��" + obj->name() + "��\n");
	return obj->do_touch(me);
}

int help(object me)
{
	write(@HELP
ָ���ʽ : touch [my] <��Ʒ����>
 
���ָ��������㸧��ĳ�����������Է�����������������
��������� my ѡ����������ڵķ��������������
���Լ�����Ʒ��
 
HELP );
	return 1;
}
