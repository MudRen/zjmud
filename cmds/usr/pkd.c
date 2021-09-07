// pkd.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object *obs;
	string msg;
	string sht;
	int i;

	if (PK_D->is_ready())
		return notify_fail("�������ڱ����أ��Ȼ����˵��\n");

	obs = PK_D->query_all_competitor();
	if (! arrayp(obs) || ! sizeof(obs))
	{
		if (PK_D->is_pking())
			return notify_fail("�޷��� PK DAEMON ������������ϵ��\n");
		return notify_fail("�������˳��ڲ�û��ʲô�ˡ�\n");
	}

	obs -= ({ me, 0 });
	if (! sizeof(obs))
	{
		write("�������˳���ֻ����һ�����ˡ�\n");
		return 1;
	}

	msg = HIR "�������˳��г����㻹ʣ��" + chinese_number(sizeof(obs)) +
	      "�ˣ������ǣ�"NOR"\n";
	msg += HIC "��" HIY "����������������������������������������������������������������������" HIC "��"NOR"\n";
	for (i = 0; i < sizeof(obs); i++)
	{
		sht = obs[i]->name(1) + "(" + obs[i]->query("id") + ")";
		msg += (obs[i]->query("gender") == "Ů��" ? HIC : WHT) +
			sprintf("%-20s", sht) + NOR;
		if (! ((i + 1) % 4))
			msg += "\n";
	}

	if (i % 4)
		msg += "\n";
	msg += HIC "��" HIY "����������������������������������������������������������������������" HIC "��"NOR"\n";
	write(msg);
	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : pkd

������ָ����Բ鿴Ŀǰ����˭�����˳��б�����
 
HELP );
	return 1;
}
