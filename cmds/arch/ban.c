// ban.c

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string site;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg)
	{
		BAN_D->print();
		return 1;
	}

	if (sscanf(arg, "+ %s", site) == 1)
	{
		if (sscanf(site, "%*d.%*d.%*d.%*d") != 4 &&
		    sscanf(site, "%*d.%*d.%*d.*") != 3)
		{
			write("��ֻ�ܽ�ֹһ��IP��ַ����һ��C������(?.?.?.*)��ַ��\n");
			return 1;
		}

		BAN_D->add_site(site);
		write("Ok.\n");
	} else
	if (sscanf(arg, "- %s", site) == 1)
		BAN_D->remove_site(site);
	else
		write("ָ���ʽ��ban [+|- site]\n");

	return 1;
	
}

int help(object me)
{
	write(@HELP
ָ���ʽ��ban [+|- site]

����������������ֹ�������⵷�ҡ���������ban + ??.??.??.*����
ֹһ��C�����ε�ַ��
HELP );
	return 1;
}
