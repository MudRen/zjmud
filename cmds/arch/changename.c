// changename.c
// created by doing

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string id, new_name;
	object ob;
	string result;
	string *opts;
	int i;
	int opt_force;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg)
		return notify_fail("��Ҫ�޸���һ����ҵ��������֣�\n");

	// ǿ���޸����ֵı�־
	opt_force = 0;
	opts = explode(arg, " ");
	for (i = 0; i < sizeof(opts); i++)
	{
		if (opts[i] == "-f")
		{
			opt_force = 1;
			opts[i] = 0;
		}
	}

	// �ж����ѡ���Ժ������жϲ���
	opts -= ({ 0 });
	arg = implode(opts, " ");

	if (sscanf(arg, "%s %s", id, new_name) == 2)
	{
		if (! LOGIN_D->check_legal_name(new_name, 8))
			return 0;

		ob = UPDATE_D->global_find_player(id);
		if (! objectp(ob))
			return notify_fail("û�������ҡ�\n");

		result = NAME_D->change_name(ob, new_name, opt_force);
		if (result)
		{
			write(result);
			if (opt_force)
				write("ϵͳǿ���޸��� " + id + " �����֡�\n");
		}
		else
			write("�ɹ����޸��� " + id + " �����֡�\n");
		UPDATE_D->global_destruct_player(ob, 1);
		return 1;
	} else
		return notify_fail("��ʽ��changename [-f] <���ID> <������>\n");
}

int help(object me)
{
write(@HELP
ָ���ʽ : changename [-f] <���ID> <������>
 
������ҵ��������֣���Ϊ������ҵ��������ֶ���¼��ϵͳ�У���
�����ֱ���޸Ľ���������ݲ�һ�¡����������-f��������ϵͳ��
ǿ���޸����ֶ����˼�ԭ���Ƿ�������������������֡�

HELP );
    return 1;
}
