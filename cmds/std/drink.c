// drink.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string from;
	object from_ob;
	object ob;
	object *guard;
	int search_flag;
	string prefix;
	int need_busy;

	if (! arg)
		return notify_fail("��Ҫ��ʲô������\n");

	if (sscanf(arg, "%s in %s", arg, from) == 2)
	{
		// ����ݾ�
		if (sscanf(from, "all %s", from))
		{
			if (me->is_busy())
				return notify_fail("��æ���أ�û�й����Ҷ�����\n");

			search_flag = 0;
			foreach (from_ob in all_inventory(me))
			{
				if (! from_ob->id(from))
					continue;

				if (from_ob->is_character())
					continue;

				if (! present(arg, from_ob))
					continue;

				search_flag = 1;
				break;
			}

			if (! search_flag)
			{
				me->start_busy(2);
				return notify_fail("�㷭�������ϴ��Ķ�����Ҳû�ҵ���Ҫ�ġ�\n");
			} else
				need_busy = 3;
		} else
		if (! objectp(from_ob = present(from, me)))
		{
			from_ob = present(from, environment(me));
			if (me->query("env/careful"))
			{
				if (! objectp(from_ob))
					return notify_fail("������û������ݾߡ�\n");
				else
					return notify_fail("������û�������ݾߣ�������" +
							   from_ob->name() + "���ֲ��Ҷ���\n");
			}
	
			if (! objectp(from_ob))
				return notify_fail("������û�������ݾߣ�����Ҳû�С�\n");
		}

		if (from_ob->is_character() && from_ob != me)
			return notify_fail("��Ҫ���ٰ���\n");
		else
		if (sizeof(all_inventory(from_ob)) < 1)
			return notify_fail(from_ob->name() + "����ʲô��û�а���\n");
	} else
		from_ob = me;

	if (! objectp(ob = present(arg, from_ob)))
	{
		ob = present(arg, environment(me));
		if (me->query("env/careful"))
		{
			if (! objectp(ob))
				return notify_fail("������û������������\n");
			else
				return notify_fail("������û������������������" +
						   ob->name() + "���ֲ��Ҷ���\n");
		}

		if (! objectp(ob))
			return notify_fail("������û����������������Ҳû�С�\n");
	}

	if (me->is_busy())
	{
		write("����һ��������û����ɡ�\n");
		return 1;
	}

	if (guard = ob->query_temp("guarded"))
	{
		guard = filter_array(guard, (:
			objectp($1) && present($1, environment($(me))) &&
			living($1) && ($1 != $(me)) :));
		if (sizeof(guard))
			return notify_fail(guard[0]->name()
				+ "������" + ob->name() + "һ�ԣ���ֹ�κ������ߡ�\n");
	}

	if (ob->query("only_do_effect"))
	{
		if (! ob->query("can_drink"))
		{
			write(ob->name() + "��ô�ȣ�\n");
			return 1;
		}

		return ob->do_effect(me);
	}

	if (! mapp(ob->query("liquid")))
		return notify_fail("�㲻֪����ô��" + ob->name() + "... :)\n");

	if (me->is_fighting())
	{
		write("��ߴ�ܱߺȶ���Ҳ����Ǻ�ţ�\n");
		return 1;
	}

	if (! ob->query("liquid/remaining"))
	{
		write(ob->name() + (ob->query("liquid/name") ?
		      "���" + ob->query("liquid/name") + "�Ѿ����ȵ�һ��Ҳ��ʣ�ˡ�\n" :
		      "�ǿյġ�\n"));
		if (me->query("env/auto_drinkout") &&
		    environment(ob) != environment(me))
		{
			message_vision("$N����һ" + ob->query("unit") + "$n��\n", me, ob);
			   write("һ" + ob->query("unit") + "�տյ�" + ob->name() + "��������������˵�ע�⣡\n");
			ob->move(environment(me));
			   destruct(ob);
		}
		return 1;
	}

	if ((int)me->query("water") > me->max_water_capacity())
	{
		write("���Ѿ���̫���ˣ���Ҳ�಻��һ��ˮ�ˡ�\n");
		return 1;
	}

	while((int)me->query("water") < me->max_water_capacity())
	{
		ob->add("liquid/remaining", -1);
		message_vision("$N����" + ob->name() + "������غ��˼���" + ob->query("liquid/name")	+ "��\n", me);
		me->add("water", 30);

		ob->do_effect();
		if (! ob->query("liquid/remaining"))
		{
			write("���Ѿ���" + ob->name() + "���" + ob->query("liquid/name") + "�ȵ�һ��Ҳ��ʣ�ˡ�\n");
			ob->clear_effect();
			if (me->query("env/auto_drinkout") && environment(ob) == me)
			{
				message_vision("$N����һ" + ob->query("unit") + "$n��\n", me, ob);
				write("һ" + ob->query("unit") + "�տյ�" + ob->name() + "��������������˵�ע�⣡\n");
				ob->move(environment(me));
			 		destruct(ob);
			}
			break;
		}
	}

	switch (ob->query("liquid/type"))
	{
	case "alcohol":
		me->apply_condition("drunk",
			(int)me->query_condition("drunk") +
			(int)ob->query("liquid/drunk_apply"));
		break;
	}

	if (! me->is_busy() && need_busy)
		me->start_busy(need_busy);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : drink <����> [in [all] <����>]
 
���ָ�������������������Һ�塣�����û�����ñ��� careful��
����������û�д����������ͻ��Զ�����Χ�Ļ���Ѱ����ָ����������

�����ָ���� in�� ��ô�㽫�Ӱ���ȡ���������á�����������û��
ָ���İ�������û�����û������� careful �Ļ��� �ͻ��Զ��ڸ���
�Ļ���Ѱ�ҡ�

�����ָ���� all����ô�㽫����������ָ���İ�����Ѱ����Ҫ����
��������Ҫ������һ��ʱ�䡣

see also : eat

HELP );
	return 1;
}
