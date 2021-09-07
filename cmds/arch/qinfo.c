// qinfo.c
#include <ansi.h>

inherit F_CLEAN_UP;

string time_len(int n)
{
	return sprintf("%.2d:%.2d:%.2d", n / 3600, (n % 3600) / 60, n % 60);
}

int main(object me, string arg)
{
	mapping total;
	object *obs;
	object qob;
	string str;

	seteuid(getuid());

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	total = QUEST_D->query("information");
	if (! mapp(total))
		return notify_fail("��ǰϵͳû���κ�����\n");

	obs = keys(total);
	obs = filter_array(obs, (: objectp($1) :));

	if (! sizeof(obs))
		return notify_fail("��ǰϵͳû���κ�����\n");

	if (arg)
	{
		sscanf(arg, "%s %*s", arg);
		qob = find_object(arg);
		if (! objectp(qob) || member_array(qob, obs) == -1)
		{
			obs = filter_array(obs, (: $1->name() == $(arg) :));
			if (! sizeof(obs))
			{
				write("Ŀǰϵͳ�в����� " + arg +
				      " �������\n");
				return 1;
			}
			qob = obs[0];
		}

		write(sprintf("�й����� " + qob->name() + " ���鱨��Ϣ��\n%O\n",
			      total[qob]));
		return 1;
	}

	str = WHT "��������	      ִ��ʱ��    ״  ̬    ��������Ӧ��ϵͳOBJECT"NOR"\n"
	      HIW "��������������������������������������������������������������������"NOR"\n";
	foreach (qob in obs)
	{
		str += sprintf("%-22s%-12s%-10s%s\n",
			       qob->name(),
			       time_len(time() - qob->query("start_time")),
			       qob->query_status(),
			       file_name(qob));
	}
	str += HIW "��������������������������������������������������������������������"NOR"\n"
	       WHT "ϵͳĿǰ���� " CYN + sizeof(obs) + WHT " ������"NOR"\n";

	me->start_more(str);

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : qinfo [<��������>]

��ָ��ɲ鿴��ǰϵͳ�е�����
HELP );
	return 1;
}
