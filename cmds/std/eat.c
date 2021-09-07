// eat.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	int count;
	string from;
	object from_ob;
	object ob;
	object *guard;
	int search_flag;
	string prefix;
	int k,need_busy;

	if (! arg)
		return notify_fail("��Ҫ��ʲô������\n");

	prefix = "";
	need_busy = 0;
	if (sscanf(arg, "%s in %s", arg, from) == 2)
	{
		// ������ݾ�
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

		prefix = "��" + from_ob->name() + "��";
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

	if (! undefinedp(count = ob->query_amount()) && count < 1)
		return notify_fail(ob->name() + "�Ѿ������ˡ�\n");

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
		k = ob->do_effect(me);
		if(ob)
			write("����Լ���ʹ��"+ZJURL("cmds:use "+ob->query("id"))+ob->name()+NOR+"��"NOR"\n");
		return k;
	} else
	{
		if (! ob->query("food_remaining"))
			return notify_fail(ob->name() + "�Ѿ�ûʲô�óԵ��ˡ�\n");

		if (me->is_fighting())
		{
			write("��ߴ�ܱ߳Զ���Ҳ����Ū����θ��\n");
			return 1;
		}
 
		if (ob->query("material") == "plant")
		{
			message_vision("$N��$n����������˼������¶ǡ�\n",me, ob);
			destruct(ob);
			return 1;
		}

		if ((int)me->query("food") > (int)me->max_food_capacity())
		{
			write("���Ѿ���̫���ˣ���Ҳ�������κζ����ˡ�\n");
			return 1;
		}
		while((int)me->query("food") < (int)me->max_food_capacity())
		{
			me->add("food", ob->query("food_supply"));
			ob->set("base_value", 0);
			ob->add("food_remaining", -1);
			ob->do_effect(me);
			if (ob->query("food_remaining") < 1)
			{
				message_vision("$N��ʣ�µ�" + ob->name() + "�Եøɸɾ�����\n", me);
				ob->clear_effect();
				if (! ob->finish_eat())
					destruct(ob);
				break;
			} else 
			{
				message_vision("$N" + prefix + "�ó�" + ob->name() + "ҧ�˼��ڡ�\n", me);
			}
		}
	}

	if (! me->is_busy() && need_busy)
		me->start_busy(need_busy);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : eat <ʳ��> | <��ҩ> [in [all] <����>]
 
���ָ����������ʳ������û�����û������� careful������
������û�д�����ʳ��ͻ��Զ�����Χ�Ļ���Ѱ����ָ����ʳ�

�����ָ���� in�� ��ô�㽫�Ӱ���ȡ��ʳ��ʳ�á�����������û��
ָ���İ�������û�����û������� careful �Ļ��� �ͻ��Զ��ڸ���
�Ļ���Ѱ�ҡ�

�����ָ���� all����ô�㽫����������ָ���İ�����Ѱ����Ҫ��ʳ
�����Ҫ������һЩʱ�䡣

see also : drink
 
HELP );
	return 1;
}
