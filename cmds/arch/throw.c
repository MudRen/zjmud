// throw.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

#define SCHEME_CMD      "/cmds/usr/scheme"

int main(object me, string arg)
{
	object card;
	object ob;
	int can = 0;
	string tstr;
	string unit;
	int time;
	string because;
	string bmsg;

	can = SECURITY_D->valid_grant(me, "(arch)");

	if (! arg)
		return notify_fail("��Ҫ��˭�ͽ�������\n");

	sscanf(arg, "%s because %s", arg, because);

	// default is 20 minute
	time = 20;
	if (sscanf(arg, "%s %s", arg, tstr) == 2)
	{
		if (sscanf(tstr, "%d%s", time, unit) != 2)
		{
			sscanf(tstr, "%d", time);
			unit = "";
		}

		switch (unit)
		{
		case "h": time *= 60;	 break;
		case "d": time *= 60 * 24 ;   break;
		case "m": time *= 1440 * 30;  break;
		case "y": time *= 1440 * 365; break;
		}
	}

	if (! time)
		return notify_fail("��Ҫ���ձ��˶�ã�\n");

	ob = find_player(arg);
	if (wiz_level(me) < 1 && ! objectp(ob))
		return notify_fail("û�������ҡ�\n");

	if (! objectp(ob))
	{
		ob = UPDATE_D->global_find_player(arg);
		if (! objectp(ob))
			return notify_fail("û�������ҡ�\n");

		if (stringp(ob->query("startroom")))
			ob->move(ob->query("startroom"));
		else
			ob->move(environment(me));
	}

	if (! ob || ! me->visible(ob))
		return notify_fail("û�������ҡ�\n");

	if (ob == me || time < 0)
		return notify_fail("����... �����Ƿ��ˣ�\n");

	if (wiz_level(ob) > 0)
		return notify_fail("�㲻�ܽ�����ʦ��\n");

	bmsg = "";
	if (! ob->is_in_prison())
	{
		if (! because)
		{
			UPDATE_D->global_destruct_player(ob);
			return notify_fail("���˽������������һ�����ɲ��С�\n");
		}

		switch (because)
		{
		case "flood":
		case "copy":
		case "rude":
		case "rumor":
		case "bug":
		case "main":
			break;

		default:
			UPDATE_D->global_destruct_player(ob);
			return notify_fail("���������Ҳ̫������ˡ�\n");
		}
	}

	if (! can)
	{
		if (card = present("throw card", me))
		{
			message("vision", me->name() + "�ͳ�һ�ſ�Ƭ��"
				"���ֹ����Ĳ�֪����˵Щʲô������"
				"�ᵽ��" + ob->query("name") + "��\n",
				environment(me), ({ me }));
			tell_object(me, "���ͳ�" + card->name() + "��"
				"���������дʣ������飡�����飡���" +
				ob->query("name") + "�͵�����ȥ��\n");
			time = card->query("time_to_leave");
			destruct(card);
			can = 1;
		}
	}

	if (! can)
	{
		UPDATE_D->global_destruct_player(ob);
		return notify_fail("����Ȩ��" + ob->query("name") + "�ͽ�������\n");
	}

	if (! ob->is_in_prison())
		log_file("static/throw",
			 sprintf("%s %s send into prison by %s because %s.\n",
				 log_time(), geteuid(ob), geteuid(this_player(1)), because));

	ob->get_into_prison(me, 0, time);
	UPDATE_D->global_destruct_player(ob, 1);

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : throw <���ID> [ <ʱ��> ] because <����>
 
���ָ����������ĳ����ҽ���һ��ʱ�䡣ʱ���Է���Ϊ��λ����
���� h ��ʾСʱ��d ��ʾ�죬m ��ʾ�·ݣ�y ��ʾ�ꡣ

��������������Ҫ���£�
1. �ڳ����Ի���(rude)
2. ��������˵�����Ի���(copy)
3. ��ҥ����(rumor)
4. ɢ���ظ���Ϣ(flood)
5. ʹ��ϵͳ���󣬵�������(bug)
6. ����ά������ҵ�����Ŀ��(main)

see also : free 
HELP );
	return 1;
}
