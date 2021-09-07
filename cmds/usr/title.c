// mktitle.c

#include <ansi.h>

inherit F_CLEAN_UP;

private int   do_normal(object me, string arg);
private int   create_title(string arg);
private int   delete_title(string arg);
private int   grant_title(string arg);
private int   replace_title(string arg);
private int   set_title(string arg);
private int   list_title();
private mixed check_title(string arg);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object ob;
	string sw;

	if (! arg)
	{
		if (! me->query("title"))
			write("�����ڲ�û���κγƺš�\n");
		else
			write("�����ڵĽ����ƺţ�" + me->query("title") + "\n");
			if (stringp(me->query_temp("title")))
				write("��Ϸ�����������ƺţ�" + me->query_temp("title") + "\n");
		return 1;
	}

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return do_normal(me, arg);

	if (arg == "-l")
		return list_title();

	if (sscanf(arg, "%s %s", sw, arg) != 2)
		return notify_fail("��μ� help title ��ø������ʹ�÷�����\n");

	switch (sw)
	{
	case "-c": return create_title(arg);  break;
	case "-d": return delete_title(arg);  break;
	case "-g": return grant_title(arg);   break;
	case "-r": return replace_title(arg); break;
	case "-s": return set_title(arg);     break;
	case "-l": return list_title();       break;
	default:   return notify_fail("��������\n");
	}
}

// ��ͨ���ʹ�� title ����
private int do_normal(object me, string arg)
{
	if (! wiz_level(me) &&
	    time() - me->query_temp("last/set_title") > 3600)
	{
		if (! me->query_temp("pending/set_title"))
		{
			write("����Ҫ�����������ƽ�������ѣ������ȷ������������һ��������\n");
			me->set_temp("pending/set_title", 1);
			return 1;
		}

		if (me->query("balance") < 3000000)
			return notify_fail("��Ǯׯ�Ĵ�����\n");

		me->add("balance", -3000000);
		write("�����˳���Ϸ֮ǰ��������ʮ���ӵ�ʱ����������趨��ĳƺš�\n");
		me->set_temp("last/set_title", time());
	}

	if (! stringp(arg = check_title(arg)))
		return 0;

	me->set("title", arg);
	write("���趨���˳ƺš�\n");
	return 1;
}

// �����ƺ�
private int create_title(string arg)
{
	int n = 1;
	mixed ts;

	sscanf(arg, "%s %d", arg, n);
	ts = UPDATE_D->query_title_base();
	if (! arrayp(ts)) ts = ({ });
	if (n + sizeof(ts) >= 100)
		return notify_fail("ϵͳ�����ֻ����һ�ٸ��ƺţ��������㿼����ȡ��һЩ��\n");

	if (! stringp(arg = check_title(arg)))
		return 0;

	write("������" + chinese_number(n) + "���ƺţ�" + arg + "\n");
	while (n--)
		ts += ({ ({ arg, 0 }) });
	UPDATE_D->set_title_base(ts);
	UPDATE_D->save();
	return 1;
}

// ɾ���ƺ�
private int delete_title(string arg)
{
	mixed ts;
	mixed item;
	mixed ds;
	object ob;
	int n;

	ts = UPDATE_D->query_title_base();
	if (! arrayp(ts))
		return notify_fail("Ŀǰ��Ϸ�в�û���κ�����ƺš�\n");

	if (sscanf(arg, "%d", n))
	{
		if (n < 1 || n > sizeof(ts))
			return notify_fail("�ƺŵĴ����Ǵ� 1 �� " +
					   sizeof(ts) + " ����������Ч�Ĵ��š�\n");

		n--;
		if (stringp(ts[n][1]) && wiz_level(ts[n][1]) > wiz_level(this_player()))
			return notify_fail("��û��Ȩ��ɾ�� " + ts[n][1] +
					   " ӵ�еĳƺš�\n");

		if (stringp(ts[n][1]) && objectp(ob = find_player(ts[n][1])))
		{
			ob->delete_temp("title");
			ob->delete("granted_title");
		}

		ds = ts[0..n - 1] + ts[n + 1..<1];
		UPDATE_D->set_title_base(ds);
		UPDATE_D->save();
		write("ȥ���˵� " + (n + 1) + " ���ƺš�\n");
		return 1;
	}

	if (! stringp(arg = check_title(arg)))
		return notify_fail("Ŀǰ��Ϸ�в�û������ƺš�\n");;

	arg = filter_color(arg);

	ds = allocate(sizeof(ts));
	n = 0;
	foreach (item in ts)
	{
		if (! arrayp(item) || sizeof(item) != 2)
			continue;

		if (filter_color(item[0]) == arg &&
		    (! stringp(item[1]) || wiz_level(item[1]) < wiz_level(this_player())))
		{
			if (stringp(item[1]) && objectp(ob = find_player(item[1])))
			{
				ob->delete_temp("title");
				ob->delete("granted_title");
			}
			continue;
		}

		ds[n++] = item;
	}
	ds = ds[0..n - 1];
	UPDATE_D->set_title_base(ds);
	UPDATE_D->save();
	write("ȥ���˳ƺţ�" + arg + "��\n");

	return 1;
}

// �����ƺ�
private int replace_title(string arg)
{
	string new_title;
	mixed ts;
	mixed item;
	object ob;
	int n;

	if (sscanf(arg, "%s %s", arg, new_title) != 2)
		return notify_fail("��������Щ�ƺ��޸ĳ�ʲô��\n");

	if (! stringp(new_title = check_title(new_title)))
		return 0;

	ts = UPDATE_D->query_title_base();
	if (! arrayp(ts))
		return notify_fail("Ŀǰ��Ϸ�в�û���κ�����ƺš�\n");

	if (sscanf(arg, "%d", n))
	{
		if (n < 1 || n > sizeof(ts))
			return notify_fail("�ƺŵĴ����Ǵ� 1 �� " +
					   sizeof(ts) + " ����������Ч�Ĵ��š�\n");

		n--;
		if (! stringp(ts[n][1]) || wiz_level(ts[n][1]) <= wiz_level(this_player()))
		{
			// �����޸�����ƺ�
			ts[n][0] = new_title;
			if (stringp(ts[n][1]) &&
			    objectp(ob = find_player(ts[n][1])))
				ob->set_temp("title", new_title);
		} else
			return notify_fail("��û��Ȩ���޸� " + ts[n][1] + " ��ӵ�еĳƺš�\n");

		UPDATE_D->set_title_base(ts);
		UPDATE_D->save();
		write("�޸��˵� " + (n + 1) + " ���ƺš�\n");
		return 1;
	}

	if (! stringp(arg = check_title(arg)))
		return notify_fail("Ŀǰ��Ϸ�в�û������ƺš�\n");;

	n = 0;
	arg = filter_color(arg);
	foreach (item in ts)
	{
		if (! arrayp(item) || sizeof(item) != 2)
			continue;

		if (filter_color(item[0]) == arg)
		{
			if (! stringp(item[1]) || wiz_level(item[1]) <= wiz_level(this_player()))
			{
				// �����޸�����ƺ�
				n++;
				item[0] = new_title;
				if (stringp(item[1]) && objectp(ob = find_player(item[1])))
					ob->set_temp("title", new_title);
			}
			continue;
		}
	}

	if (! n)
		return notify_fail("Ŀǰ��Ϸ�в�û�п��������޸ĵĳƺš�\n");

	UPDATE_D->set_title_base(ts);
	UPDATE_D->save();
	write("�޸ĳƺš�" + arg + "��Ϊ��" + new_title + "����\n");

	return 1;
}

// ���óƺ�
private int set_title(string arg)
{
	string user;
	object ob;

	if (sscanf(arg, "%s %s", user, arg) != 2)
		return notify_fail("��ҪΪ˭����ʲô�ƺţ�\n");

	if (! objectp(ob = find_player(user)))
		return notify_fail("�����Ҳ�����Ϸ�У������趨�ƺš�\n");

	if (! stringp(arg = check_title(arg)))
		return 0;

	if (wiz_level(this_player()) < wiz_level(ob))
		return notify_fail("�㲻��Ϊ" + ob->name(1) + "�趨�ƺš�\n");

	ob->set("title", arg);
	write("Ϊ" + ob->name(1) + "�趨�˳ƺš�\n");
	return 1;
}

// ����ƺ�
private int grant_title(string arg)
{
	string user;
	mixed ts;
	mixed item;
	object nob;
	object ob;
	int i;

	if (sscanf(arg, "%s none", user) == 1)
	{
		// �����ԭ�ȵ� title
		write(UPDATE_D->clear_user_data(user, "title"));
		return 1;
	}

	if (sscanf(arg, "%s %d", user, i) != 2)
		return notify_fail("����ƺ������ָ����ҺͳƺŵĴ��š�\n");

	ts = UPDATE_D->query_title_base();
	if (i < 1 || i > sizeof(ts))
		return notify_fail("�ƺŵĴ����Ǵ� 1 �� " +
				   sizeof(ts) + " ����������Ч�Ĵ��š�\n");
	i--;
	item = ts[i];

	if (! objectp(nob = UPDATE_D->global_find_player(user)))
		return notify_fail("��ֻ������ƺŸ��Ѿ�ע�����ҡ�\n");

	if (item[1] == user)
	{
		notify_fail(nob->name(1) + "�ĳƺ�Ŀǰ���������\n");
		UPDATE_D->global_destruct_player(nob);
		return 0;
	}

	if (wiz_level(this_player()) < wiz_level(nob))
	{
		notify_fail("�㲻��Ϊ" + nob->name(1) + "�趨�ƺš�\n");
		UPDATE_D->global_destruct_player(nob);
		return 0;
	}

	// �����ԭ�ȵ� title
	UPDATE_D->remove_title(nob);

	if (stringp(item[1]) && objectp(ob = find_player(item[1])))
	{
		// �ָ������ҵ�ԭ�ȳƺ�
		ob->delete_temp("title");
		ob->delete("granted_title");
	}

	// ��������ϵͳ�� title ��¼
	item[1] = user;
	ts[i] = item;

	// ����������ҵ� title
	nob->set_temp("title", item[0]);
	nob->set("granted_title", 1);
	nob->save();

	UPDATE_D->set_title_base(ts);
	UPDATE_D->save();
	write("Ϊ" + nob->name(1) + "�����ˡ�" + item[0] + "���ĳƺš�\n");
	UPDATE_D->global_destruct_player(nob);

	return 1;
}

private int list_title()
{
	mixed ts;
	string str;
	mixed item;
	int i;

	ts = UPDATE_D->query_title_base();
	if (! arrayp(ts) || sizeof(ts) < 1)
		return notify_fail("Ŀǰ��Ϸ��û���κ�����ƺš�\n");

	i = 1;
	str = "Ŀǰϵͳ�е�����ƺ��� " CYN + sizeof(ts) + NOR " ����\n";
	foreach (item in ts)
	{
		str += sprintf("%3d. %-" + (30 + color_len(item[0])) + "s%s\n",
			       i, item[0], item[1] ? item[1] : "");
		i++;
	}
	this_player()->start_more(str);

	return 1;
}

private mixed check_title(string arg)
{
	arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);

	if (strlen(filter_color(arg)) > 30 || strlen(arg) > 100)
		return notify_fail("������̫���ˣ�Ϊ�˽�Լ��Դ�����������趨��\n");

	return arg + NOR;
}

int help(object me)
{
	write(@HELP
�������û�о�����Ȩ����ң�
ָ���ʽ : title [<�ƺ�>]

��������������趨�ƺţ��޸ĳƺ�����Ҫ������������
���ƽ��Զ������Ǯׯ�˺��Ͽ۳�������δ�˳���Ϸ����
ʮ���������ٴ��޸Ĳ���Ҫ�����κ��������á�

��ע�⣺�趨�ĳƺŲ�ҪΥ����Ϸ���򣬷������������
�������Ĵ�����

������Ǿ���ʹ�ø�����Ȩ�޵���һ���ʦ��
ָ���ʽ : title -c <�ƺ�> [<����>]
	   title -d <�ƺŴ���> | <�ƺ�>
	   title -g <sb> <�ƺŴ���> | <none>
	   title -r <�ƺŴ���> | <�ƺ�> <�³ƺ�>
	   title -s <���> <�³ƺ�>
	   title -l
 
���ָ���������Ϊĳ��ȡһ��������ͷ�Σ�����ֻ����
ʦ�ſ���ʹ�ã������ϣ���������ʹ�� ANSI �Ŀ�����
Ԫ�ı���ɫ�����������µĿ����ִ���

$BLK$ - ��ɫ		$NOR$ - �ָ�������ɫ
$RED$ - ��ɫ		$HIR$ - ����ɫ
$GRN$ - ��ɫ		$HIG$ - ����ɫ
$YEL$ - ����ɫ		$HIY$ - ��ɫ
$BLU$ - ����ɫ		$HIB$ - ��ɫ
$MAG$ - ǳ��ɫ		$HIM$ - �ۺ�ɫ
$CYN$ - ����ɫ		$HIC$ - ����ɫ
$WHT$ - ǳ��ɫ		$HIW$ - ��ɫ
 
����ϵͳ�Զ������ִ�β�˼�һ�� $NOR$��

����ƺſ���ʹ�� -g ����������ǰ������Ҫ�����ƺţ�ʹ�� -c ��
����������Ϸ�д���һ�������ƺš�ʹ�� -d ����ȥ����Щ�ƺš�
�� -l �������ܹ��г�������Щ�ƺź�Ŀǰ�����������ʹ�� -r ��
�����Խ�Ŀǰ��ĳЩ�ƺŸ����������� -s ���������������ҵ�ԭ
ʼ�ƺţ�ע�⣬����ƺ��ڰ�ʦ������ĳЩ�����¿��ܻᱻ�޸ġ�

����������ĳ����ҡ���а������ƺſ��ԣ�
title -c $HIY$��а
title -l �鿴������а������ƺŵĴ�����2��
title -g player 2
�����ԡ���а������ƺŲ����⣬���ԣ�
title -r ��а ����
������ƺŵ����ָ�����
�����Ҫ��������ƺſ��ԣ�
title -g player none

ֻ����Ҫ���ñ����� title ��ʹ�� title -c ����Ȼ��������ң�
һ���޸� title Ӧ��ʹ�� title -s <���> <�ƺ�> �Խ�Լ��Դ��

HELP );
	return 1;
}
