// quest.c

#include <ansi.h>
 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob,obj;
	mapping q;
	string master,str;

	if (me->query_condition("db_exp"))
		tell_object(me, HIG"������鵤ʱ�仹��"+chinese_number(me->query_condition("db_exp")/6)+"���ӡ�"NOR"\n");
	if (me->query_condition("db_exp2"))
		tell_object(me, HIG"������鵤ʱ�仹��"+chinese_number(me->query_condition("db_exp2")/6)+"���ӡ�"NOR"\n");

if (me->query("auto_kill_quest_npc") && me->query("quest/id")) {
	if (objectp(present(me->query("quest/id"),environment(me)))) {
		me->force_me("kill " + me->query("quest/id"));
		return 1;
	}
}

	while (arg)
	{
		if (arg == "cancel")
		{
			if (! stringp(master = me->query("quest/master_id")))
				return notify_fail("������������������\n");

			if (! objectp(ob = present(master, environment(me))))
				return notify_fail("������������Ǹ������ڲ�������ɣ�\n");
		}
		else if (! objectp(ob = present(arg, environment(me))))
			return notify_fail("����û������ˣ�����ô������\n");

		if (! living(ob))
			return notify_fail("�㻹�ǵ�" + ob->name() + "������˵�ɣ�\n");

		if (me->is_fighting())
			return notify_fail("ר�Ĵ���ļܣ�\n");

		if (me->is_busy())
			return notify_fail("�㻹���п����ٺ�" + ob->name() + "̸��Щ����ɣ�\n");

		if (ob->is_fighting())
			return notify_fail("�㻹�ǵ�" + ob->name() + "�������˵�ɣ�\n");

		if (ob->is_busy())
			return notify_fail(ob->name() + "��æ���أ�û�������㡣\n");

		notify_fail(ob->name() + "������Ǻǵ�ɵЦ��\n");
		return (arg == "cancel" ? ob->cancel_quest(me) : ob->ask_quest(me));
	}

	if (me->query("quest_count"))
		write(sprintf("ʦ����������������Ѿ���������� "HIM"%d"NOR" ����\n",
			      me->query("quest_count")));
 
	if (! mapp(q =  me->query("quest")))
	{
		write("������û�����κ�����\n");
		return 1;
	}
	if(objectp(obj=find_living(q["id"]))&&environment(obj))
		str = "��˵����Ŀǰ��" + q["place"] + environment(obj)->query("short") + "��û��\n";
	else
		str = "��������ʧ��\n";
	switch (q["type"])
	{
	case "kill":
		if(wizardp(me))
			write(q["master_name"] + "�Ը�����" + CHINESE_D->chinese_monthday(q["limit"]) +
			      "֮ǰ����" HIR + ZJURL("cmds:goto "+q["id"])+q["name"] + NOR "(" + q["id"] + ")����ͷ����" + q["family"] + "���\n" +
			      "��˵����ǰ����������" + q["place"] + "��û��\n");
		else
			write(q["master_name"] + "�Ը�����" + CHINESE_D->chinese_monthday(q["limit"]) +
			      "֮ǰ����" HIR + q["name"] + NOR "(" + q["id"] + ")����ͷ����" + q["family"] + "���\n" +
			      "��˵����ǰ����������" + q["place"] + "��û��\n");
		return 1;
	case "letter":
		write(q["master_name"] + "�Ը�����" + CHINESE_D->chinese_monthday(q["limit"]) +
		      "֮ǰ���ż��͵�" HIC + q["name"] + NOR "(" + q["id"] + ")���У�ȡ��ִ���\n" + str);
		return 1;
	}

	write("������û�����κ�����\n");
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : quest  ���ָ�����������������ɵ����Ż����ҳ���
��ȡ������������κβ�������ʾ���㵱ǰ������
HELP );
	return 1;
}
