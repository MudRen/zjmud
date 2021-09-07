// dest.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string option, target, msg;
	object obj;
	int opt_clone;
	object *obs;

	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	if (! arg)
		return notify_fail("ָ���ʽ : dest <���֮���ƻ���>\n");

	if (sscanf(arg, "%s %s", option, target) == 2 &&
	    option == "-c")
	{
		opt_clone = 1;
	} else
	{
		target = arg;
		opt_clone = 0;
	}

	obj = find_object(target);
	if (! obj) obj = present(target, me);
	if (! obj) obj = present(target, environment(me));
	if (! obj) obj = find_object(target);
	if (! obj) obj = find_object(resolve_path(me->query("cwd"), target));
	if (! obj) return notify_fail("û���������....��\n");

	seteuid(getuid());

	if (! me->is_admin())
	{
		switch (SECURITY_D->query_site_privilege("dest"))
		{
		case "all":
			break;

		case "noneuser":
			if (playerp(obj))
				return notify_fail("�㲻�ܶ����ʩչ������\n");
			break;

		case "user":
			if (! playerp(obj))
				return notify_fail("��ֻ�ܶ����ʩչ������\n");
			break;

		default:
			return notify_fail("�㲻��ʹ�ø����\n");
		}
	}

	if (! is_root(me)) seteuid(geteuid(me));

	if (playerp(obj) && wiz_level(me) < wiz_level("(arch)"))
	{
		write("��û��Ȩ�޴ݻ���ҡ�\n");
		return 1;
	}

	if (! SECURITY_D->valid_write(base_name(obj), me, "dest"))
	{
		write("��û��Ȩ�޲����������\n");
		return 1;
	}

	if (opt_clone)
	{
		if (clonep(obj))
		{
			write("�ö����Ǹ��ƶ���û�����������޷�ִ�� -c ѡ�\n");
			return 1;
		}

		if (obj == find_object(USER_OB))
		{
			write("�㲻�����ʹ���ߵ���������\n");
			return 1;
		}

		if (obj == find_object(LOGIN_OB))
		{
			write("�㲻�����ʹ����������Ϣ����������\n");
			return 1;
		}

		obs = children(base_name(obj));
		foreach (obj in obs)
		{
			write("��ݻ���" + obj->name(1) + "(" +
			      file_name(obj) + ")��\n");
			destruct(obj);
		}
		write("Ok.\n");
		return 1;
	}

	if (me == obj)
		message_vision("$N�ٻ���һ���ڶ���һͷ���˽�ȥ��\n", me);
	else
	if (environment(me) == environment(obj))
		message_vision("$N�ٻ���һ���ڶ���һ�Űѽ�$n���˽�ȥ��\n", me, obj);

	destruct(obj);
	if (obj) write("���޷����������ݻ١�\n"); else
	if (me) write("Ok.\n");

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : dest [-c] <���֮���ƻ���>

���ô�һָ��ɽ�һ����� object �Ӽ����������������������
����һ�βο�����������ʱ������½������롣

���ʹ���� -c ������������õ��������������ж���

�������ڿ��Ա���Ȩʹ�õ���Ϣ������noneuser��user��all��

�ο����ϣ� destruct()
HELP );
	return 1;
}
