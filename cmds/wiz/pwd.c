// pwd.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	seteuid(getuid());

	write("Cwd: " + (string)me->query("cwd") +  "\n");
	write("Cwf: " + (string)me->query("cwf") +  "\n");
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : pwd
 
���ָ�����ʾ����Ŀǰ�Ĺ���Ŀ¼ (cwd) ���������� (cwf).
'update' ���Ӳ���ʱ��������� cwf.
 
HELP );
    return 1;
}
