// mkdir.c
// updated by doing

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
	string dir;

	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	if (! arg) return help(me);

	dir = resolve_path(me->query("cwd"), arg);

	seteuid(geteuid(me));
	if (mkdir(dir))
		write("Ok.\n");
	else
		write("��û�������ｨ��Ŀ¼��Ȩ����\n");
	return 1;	
}

int help(object me)
{
	write(@HELP
ָ���ʽ : mkdir <��Ŀ¼��>

����һ����Ŀ¼��

see also: rm
HELP );
	return 1;
}
