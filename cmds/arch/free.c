// free.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object ob;
	object card;
	string tstr;
	string unit;
	int time;

	if (! arg)
		return notify_fail("��Ҫ��˭����������\n");

	time = 0;
	if (sscanf(arg, "%s %s", arg, tstr) == 2)
	{
		if (sscanf(tstr, "%d%s", time, unit) != 2)
		{
			sscanf(tstr, "%d", time);
			unit = "";
		}

		switch (unit)
		{
		case "h": time *= 60;   break;
		case "d": time *= 1440; break;
		}
	}

	ob = find_player(arg);
	if (! ob && wiz_level(me) < 1)
		return notify_fail("û�������ҡ�\n");

	if (! ob)
	{
		ob = UPDATE_D->global_find_player(arg);
		if (! objectp(ob))
			return notify_fail("û�������ҡ�\n");

		ob->move(environment(me));
	}

	if (! ob || ! me->visible(ob))
	{
		UPDATE_D->global_destruct_player(ob);
		return notify_fail("û�������ҡ�\n");
	}

	if (! ob->is_in_prison())
	{
		UPDATE_D->global_destruct_player(ob);
		return notify_fail("����������û�б����ա�\n");
	}

	if (! SECURITY_D->valid_grant(me, "(arch)"))
	{
		if (! objectp(card = present("help card", me)))
			return notify_fail("��û��Ȩ�����˷ų�����\n");

		message_vision("$N����һ�ſ�Ƭ��ƴ����߶��̫���Ͼ���������" +
			       ob->name(1) + "�����޹�����\n", me);
		destruct(card);
	}

	ob->leave_prison(me, time);
	UPDATE_D->global_destruct_player(ob, 1);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : free <���ID> [ <ʱ��> ]
 
���ָ���������ѱ����յ�����ͷų�����ʱ���Է���Ϊ��λ����
���� h ��ʾСʱ��d ��ʾ�졣

see also : throw
 
HELP );
	return 1;
}
