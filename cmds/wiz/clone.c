// clone.c
// Updated by Doing Lu 7/12/01

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj;
	string err, msg;
	string file;
	int amount;

	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	seteuid(getuid());

	if (! arg || sscanf(arg, "%s %d", file, amount) != 2)
	{
		file = arg;
		amount = 1;
	}

	if (amount < 1)
		return notify_fail("���븴�ƶ��٣�\n");

	if (! file) file = me->query("cwf");
	if (! file)
		return notify_fail("��Ҫ����ʲ�������\n");

	file = resolve_path(me->query("cwd"), file);
	if (sscanf(file, "%*s.c") != 1) file += ".c";
	me->set("cwf", file);

	if (file_size(file) < 0)
		return notify_fail("û���������(" + file + ")��\n");

	// ����Ը��ļ��ɶ����ܸ��ơ�
	if (! SECURITY_D->valid_read(file, me, "clone"))
	{
		write("��û��Ȩ�޲����������\n");
		return 1;
	}

	if (! find_object(file))
	{
		err = catch(call_other(file, "???"));
		if (err)
		{
			write("����ʧ�ܣ�" + err + "\n");
			return 1;
		}
	}

	seteuid(geteuid(me));

	err = catch(obj = new(file));
	if (err)
	{
		write("����ʧ�ܣ�" + err + "\n");
		return 1;
	}

	if (! objectp(obj))
	{
		write("���޷����Ƹ���Ʒ��\n");
		return 1;
	}

	msg = "ֻ��$N�������һָ�������$n��\n";

	obj->set_amount(amount);
	log_file("static/clone", sprintf("%s %-9s clone %s(%d)\n",
					 log_time(), geteuid(me),
					 base_name(obj), amount));
	if (! obj->is_character() && obj->move(me))
	{
		write(obj->name(1) + "���Ƴɹ������������Ʒ����\n");
		message_vision(msg + "\n", me, obj);
	} else
	if (obj->move(environment(me)))
	{
		write(obj->name(1) + "���Ƴɹ�������������䡣\n");
		message_vision(msg + "\n", me, obj);
	} else
	{
		destruct(obj);
		return notify_fail("�޷����Ʋ����ƶ������(" + file + ")��\n");
	}

	if (obj->query_amount() != amount)
	{
		if (amount > 99) amount = 99;
		while (--amount > 0)
		{
			obj = new(file);
			if (! objectp(obj))
				continue;
	
			if (obj->is_character() || obj->query("no_get") || ! obj->move(me))
				obj->move(environment(me));
		}
	}
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : clone <�ļ���> [<����>]

���ô�ָ��ɸ����κ����ƶ�֮���(������)��

�������ڿ��Ա���Ȩʹ�õ���Ϣ������gift��all��

see also : dest
HELP );
	return 1;
}
