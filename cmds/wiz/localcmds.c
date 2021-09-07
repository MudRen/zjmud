// localcmds.c
// updated by doing

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	mixed *cmds;
	int i;

	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	if (! arg) ob = me;
	if (! ob) ob = present(arg, environment(me));
	if (! ob) ob = find_player(arg);
	if (! ob)
		return notify_fail("û�������ҡ�\n");

	if (! me->is_admin())
	{
		switch (SECURITY_D->query_site_privilege("localcmds"))
		{
		case "enable":
			break;

		default:
			return notify_fail("�㲻�ܲ鿴���ص����\n");
		}
	}

	cmds = ob->query_commands();
	write((ob == me ? "��" : ob->name()) +"���ϼ����ܵ���Ʒ�����ڵĻ����ṩ����ָ�\n");
	for(i = 0; i<sizeof(cmds); i++)
		write(sprintf("%-15s  %2d %O\n", cmds[i][0], cmds[i][1], cmds[i][2]));

	return 1;
}

int help()
{
	write(@TEXT
ָ���ʽ��localcmds

�г������ϼ����ܵ���Ʒ�����ڵĻ����ṩ������ָ�

�������ڿ��Ա���Ȩʹ�õ���Ϣ������enable��
TEXT );
	return 1;
}
