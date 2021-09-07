// spend.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string str, str1;
	int amount;
	int yuan;
	int little;
	int rmb;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	if (! arg)
		return notify_fail("��Ҫ��˭��Ǯ��\n");

	if (sscanf(arg, "%s %s", arg, str) != 2)
		return notify_fail("��ʽ��spend <id> <Ǯ��>\n");

	if (sscanf(str, "%d.%s", yuan, str1) != 2)
		return notify_fail("Ǯ���������С���㡣\n");

	switch (strlen(str1))
	{
	case 0:
		little = 0;
		break;

	case 1:
		if (str1[0] < '0' || str1[0] > '9')
			return notify_fail("Ǯ���ĸ�ʽ����ȷ��\n");

		little = (str1[0] - '0') * 10;
		break;

	case 2:
		if (str1[0] < '0' || str1[0] > '9' ||
		    str1[1] < '0' || str1[1] > '9')
			return notify_fail("Ǯ���ĸ�ʽ����ȷ��\n");

		little = (str1[0] - '0') * 10 + (str1[1] - '0');
		break;

	default:
		return notify_fail("Ǯ���ĸ�ʽ����ȷ��\n");
	}

	ob = find_player(arg);
	if (! objectp(ob))
		return notify_fail("û�������ҡ�\n");

	amount = yuan * 100 + little;
	if (amount < 0)
		return notify_fail("��Ҫ�۳�����Ǯ��\n");

	if (! amount)
		return notify_fail("��۲���Ǯ����\n");

	if (amount > ob->query("rmb"))
		return notify_fail((string) ob->name(1) + "����û����ô��Ǯ��\n");

	rmb = ob->add("rmb", -amount);
	str = sprintf("�۳���%s�˺���%4dԪ%d��%d�֣���%4dԪ%d��%d�֡�\n",
		      ob->name(1),
		      yuan, (little / 10), (little % 10),
		      rmb / 100, (rmb % 100) / 10, (rmb % 100));
	write(str);

	log_file("static/spend",
		 sprintf("%s %s%s", log_time(time()), me->name(1), str));
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : spend <id> <����>
 
���ָ��۳���������ϵ��ֽ�(�����)������
 
HELP );
	return 1;
}
