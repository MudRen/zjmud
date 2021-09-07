// more.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string file;
	object ob;
	int    with_line_number = 1;

	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	seteuid(geteuid(me));

	if (! arg) return notify_fail("ָ���ʽ : more <����>|<�����> \n");

	if (sscanf(arg, "%s -n", file)) with_line_number = 0;
	else file = arg;

	file = resolve_path(me->query("cwd"), file);
	if (file_size(file) < 0)
	{
		ob = present(arg, me);
		if (! ob) ob = present(arg, environment(me));
		if (! ob) return notify_fail("û�����������\n");
		file = base_name(ob) + ".c";
	}

	if (! SECURITY_D->valid_read(file, me, "read"))
		return notify_fail("û�����������\n");

	if (with_line_number)
		me->start_more_file(file);
	else me->start_more(read_file(file));

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : more <������> [-n]

���ָ����������Է�ҳ��ʽ����һ���ļ������ݡ������ -n
���������ʾ����ʾ�кš�

see also: cat
HELP );
	return 1;
}

