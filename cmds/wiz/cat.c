// cat.c
// updated by doing

int main(object me, string arg)
{
	string file;

	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	seteuid(geteuid(me));

	if (me != this_player())
		return 0;

	if (! arg) return notify_fail("ָ���ʽ :cat <������>\n");
	file = resolve_path(me->query("cwd"), arg);
	if (file_size(file) < 0)
		return notify_fail("û�����������\n");

	if (! SECURITY_D->valid_read(file, me, "cat"))
		return notify_fail("û�����������\n");

	if (file_size(file) > 32000)
		write("�ļ�̫�������� more ָ��鿴��\n");
	else
		write(ZJMAPTXT+replace_string(color_filter(read_file(file)),"\n",ZJBR)+"\n");
//		me->start_more(read_file(file));
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ :cat <������>

���ָ��������Բ���һ���ļ������ݡ�

see also: more
HELP );
    return 1;
}
