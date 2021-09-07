// id.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj, *inv;
	string *id;
	string cname;
	string name;
	int i, j;
	int l;

	if (! arg)
	{
		inv = all_inventory(me);
		if (! sizeof(inv))
			return notify_fail("������û���κζ�����\n");
		write("������Я����Ʒ�ı������(�ҷ�)��\n");
		for(i = 0; i < sizeof(inv); i++)
		{
			if (! me->visible(inv[i])) continue;
			name = inv[i]->name();
			l = 20 + strlen(name) - strlen(filter_color(name));
			write(sprintf("%-" + sprintf("%d", l) + "s = %s\n", name,
				implode(inv[i]->parse_command_id_list(), "��")));
		}
		return 1;
	}

	if (arg == "here" || sscanf(arg, "here for %s", cname))
	{
		inv = all_inventory(environment(me));

		if (cname)
			inv = filter_array(inv, (: $1->name() == $(cname) :));

		if (! sizeof(inv))
			return notify_fail("����û���κζ�����\n");

		write("�����������, ���Ｐ��Ʒ��(Ӣ��)�������£�\n");
		for(i = 0; i < sizeof(inv); i++)
		{
			if (! me->visible(inv[i])) continue;
			name = inv[i]->name();
			l = 20 + strlen(name) - strlen(filter_color(name));
			write(sprintf("%-" + sprintf("%d", l) + "s = %s\n", name,implode(inv[i]->parse_command_id_list(), "��")));
			write(file_name(inv[i])+"\n");
		}
		return 1;
	}
}

int help(object me)
{
	write(@HELP
ָ���ʽ : id [here [for <��������>]]
 
���ָ���������֪����Ʒ��Ӣ�����Ƽ�����. ֻ�� id ����ʾ
��������Я����Ʒ������. 'id here' ����ʾ���и�����ͬһ��
��������������.
 
HELP );
	return 1;
}
