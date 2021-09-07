// brothers

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int sort_brothers(string id1, string id2);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object  who;
	object  ob;
	string  msg;
	string  pro;
	mapping bro;
	string *ids;
	string  id;
	string  nid;

	if (arg && sscanf(arg, "out %s", arg) == 1)
	{
		if (! me->is_brother(arg))
			return notify_fail("������û���������ֵܰ���\n");

		if (me->query_temp("pending/brother_out") != arg)
		{
			write("��ȷ��Ҫ����λ����(" + arg + ")���۶�����\n"YEL "�����ȷ������������һ���������"NOR"\n");
			me->set_temp("pending/brother_out", arg);
			return 1;
		}

		me->delete_temp("pending/brother_out");
		if (objectp(ob = find_player(arg)) && environment(ob) == environment(me))
		{
			message_vision("$Nһ��̾Ϣ������$n������������" + ob->name(1) +
				       "���ض�˵���ӽ������������Ҳû�а���ϵ�ˣ���\n",
				       me, ob);
		}

		nid = me->query("brothers/" + arg) + "(" + arg + ")";
		write("���" + nid + "�Ͼ��˹�ϵ��\n");
		id = me->query("id");
		CHANNEL_D->do_channel(this_object(), "rumor",
			"��˵" + me->name(1) + "(" + id + ")"
			"��" + nid + "���۶��壬�Ͼ���������");

		// remove the brother's association
		UPDATE_D->clear_user_data(id, "brothers:" + arg);
		UPDATE_D->clear_user_data(arg, "brothers:" + id);
		return 1;
	}

	if (! arg || ! wizardp(me))
	{
		who = me;
		pro = "��";
	} else
	{
		if (! objectp(who = find_player(arg)))
			return notify_fail("û���ҵ������ҡ�\n");
		else
			pro = who->name(1);
	}

	if (! mapp(bro = who->query("brothers")) || sizeof(bro) < 1)
		return notify_fail(pro + "���ڻ�û�н�����ֵ��ǡ�\n");

	msg = pro + "����" + LOCAL_MUD_NAME() + "�Ľ����ֵܶ��У�\n\n";
	ids = keys(bro);
	ids = sort_array(ids, (: sort_brothers :));
	foreach (id in ids)
	{
		nid = (string) bro[id] + "(" + id + ")";
		msg += sprintf(WHT "%-14s  ", nid);
		if (objectp(ob = find_player(id)))
			msg += sprintf(HIY "����   "
				       NOR WHT "���飺" HIC "%-9d "
				       NOR WHT "������" HIW "%-8d "
				       NOR WHT "������" HIY "%-8d"NOR"\n",
				       ob->query("combat_exp"),
				       ob->query("score"),
				       ob->query("weiwang"));
		else
			msg += HIR "������"NOR"\n";
	}
	write(msg);

	return 1;
}

int sort_brothers(string id1, string id2)
{
	object ob1, ob2;

	ob1 = find_player(id1);
	ob2 = find_player(id2);
	if (! objectp(ob1) && ! objectp(ob2))
		return strcmp(id2, id1);

	if (objectp(ob1) && objectp(ob2))
		return ob2->query("combat_exp") - ob1->query("combat_exp");

	if (objectp(ob1))
		return -1;

	return 1;
}

int help(object me)
{
   	write( @HELP
ָ���ʽ: brothers �޲��� | out <sb>

�鿴�Լ����ڵĽ����ֵ��ǡ����ʹ�� brothers out <sb> ���Խ�
�������ϵ��

see also��swear
HELP );
   	return 1;
}
