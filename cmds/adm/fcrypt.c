// fcrypt.c

#include <ansi.h>

inherit F_CLEAN_UP;

int build_path(string arg);

int main(object me, string arg)
{
	string affix;

	if (! me->is_admin())
		return 0;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	if (! arg)
		return notify_fail("������·�������ļ�����\n");

	arg = resolve_path(me->query("cwd"), arg);
	switch (file_size(arg))
	{
	case -1:
		return notify_fail("û������ļ�����·����\n");
	case -2:
		if (arg[strlen(arg) - 1] != '/') arg += "/";
		write("Ϊ " + build_path(arg) + " ���ļ������˼���ID��\n");
		return 1;
	}

	if (strlen(arg) < 2)
		return notify_fail("����ļ�û�б�Ҫ���Ӽ���ID��\n");

	affix = arg[strlen(arg) - 2..<1];
	if (affix != ".c" && affix != ".h")
		return notify_fail("����ļ�û�б�Ҫ���Ӽ���ID��\n");

	if (VERSION_D->append_sn(arg) == 1)
	{
		write("�ɹ��������˼���ID��\n");
		return 1;
	}

	write("���Ӽ���IDʧ���ˡ�\n");
	return 1;
}

int build_path(string path)
{
	string affix;
	mixed file;
	int count;
	int i;

	file = get_dir(path, -1);

	count = 0;
	i = sizeof(file);
	while (i--)
	{
		reset_eval_cost();
		if (file[i][1] != -2)
		{
			affix = file[i][0][strlen(file[i][0]) - 2..<1];
			if (affix != ".c" && affix != ".h")
				continue;

			switch (VERSION_D->append_sn(path + file[i][0]))
			{
			case 1:
				count++;
				write("Add file: " + file[i][0] + "\n");
				break;

			case 0:
				write(HIR "Bad file: " + file[i][0] + ""NOR"\n");
				break;
			}
		}
	}

	i = sizeof(file);
	while (i--)
	{
		reset_eval_cost();
		if (file[i][1] == -2)
			count += build_path(path + file[i][0] + "/");
	}

	return count;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : fcrypt <Ŀ¼��> | <�ļ���>

���ô�һָ�����Ϊĳһ���ļ�����ĳһ��Ŀ¼�µ�����Դ�ļ�����
����������ID��

HELP
    );
    return 1;
}
