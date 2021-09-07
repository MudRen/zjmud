// qdel.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mapping total;
	object *obs, *dst;
	object qob;

	seteuid(getuid());

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg)
		return notify_fail("��Ҫ���ʲô����\n");

	total = QUEST_D->query("information");
	if (! mapp(total))
		return notify_fail("��ǰϵͳû���κ�����\n");

	obs = keys(total);
	obs = filter_array(obs, (: objectp($1) :));

	if (! sizeof(obs))
		return notify_fail("��ǰϵͳû���κ�����\n");

	sscanf(arg, "%s %*s", arg);
	if (arg == "all" || arg == "ALL")
	{
		foreach (qob in obs)
		{
			reset_eval_cost();
			destruct(qob);
		}
		write("�������ϵͳ�����е�����\n");
		return 1;
	}

	qob = find_object(arg);
	if (! objectp(qob) || ! qob->is_quest())
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

	write("������ˡ�" + qob->name() + "���������\n");
	destruct(qob);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : qdel all | <��������>

��ָ��������ǰϵͳĳһ������������е�����
HELP
	);
	return 1;
}
