#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	mapping skill_status;
	object ob;
	string skill, obj;
	string *skills;
	string file;
	int i, j, level;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg)
		return notify_fail("ָ���ʽ��setsk <ĳ��> [ <��"
				   "��> | all ] <������>\n");

	if (sscanf(arg, "%s %s %d", obj, skill, level) != 3
	   && sscanf(arg, "%s %d", skill, level) != 2)
		return notify_fail("ָ���ʽ��setsk <ĳ��> [ <��"
				   "��> | all ] <������>\n");

	if (sscanf(arg, "%s %d", skill, level) == 2)
	{
		ob = me;
	} else
	if (sscanf(arg, "%s %s %d", obj, skill, level) == 3)
	{
		ob = find_player(obj);

		if (! ob)
			ob = find_living(obj);

		if (! ob)
			ob = present(obj, environment(me));

		if (! ob)
			return notify_fail("Ŀ�겻���ڣ�������趨����"
					   "���ܣ�Ŀ���������ȱʡ��\n");
	}

	if (wiz_level(me) <= wiz_level(ob) && me != ob)
		return notify_fail("��ֻ�ܸ�Ȩ�ޱ��Լ��͵����趨���ܡ�\n");

/*
	if (! is_root(me) && playerp(ob) && ! wizardp(ob))
		return notify_fail("ֻ��������ܸ���ͨ������趨���ܡ�\n");
*/

	if (skill == "all")
	{
		if (! (skill_status = ob->query_skills())
		   || ! sizeof(skill_status))
			return notify_fail("Ŀ��û��ѧ���κμ��ܣ��޷�"
					   "ʹ�� all ������\n");

		skills  = keys(skill_status);
		j = sizeof(skill_status);

		write(WHT "\n");

		for (i = 0; i < j; i++)
		{
			if (level == 0)
			{
				ob->delete_skill(skills[i]);
				printf("Ŀ�꣺" CYN "%s" WHT "  ȡ�����ܣ�"
				       CYN "%s\n" WHT, ob->name() + "(" +
				       ob->query("id") + ")", to_chinese(skills[i]) +
				       "(" + skills[i] + ")");
			} else
			{
				ob->set_skill(skills[i], level);
				printf("Ŀ�꣺" CYN "%s" WHT "  �趨���ܣ�"
				       CYN "%-30s " WHT "�ȼ���" CYN "%d\n"
				       WHT, ob->name() + "(" + ob->query("id") + ")",
				       to_chinese(skills[i]) + "(" + skills[i] + ")",
				       level);
			}
		}
		write(""NOR"\n");
	} else
	{
		if (! stringp(file = SKILL_D(skill))
		   || file_size(file + ".c") <= 0)
			return notify_fail("û�� " + skill + " ���ּ��ܴ��ڡ�\n");

		write(WHT);

		if (level == 0)
		{
			ob->delete_skill(skill);
			printf("Ŀ�꣺" CYN "%s" WHT "  ȡ�����ܣ�"
			       CYN "%s\n" WHT, ob->name() + "(" +
			       ob->query("id") + ")", to_chinese(skill) +
			       "(" + skill + ")");
		} else
		{
			ob->set_skill(skill, level);
			printf("Ŀ�꣺" CYN "%s" WHT "  �趨���ܣ�"
			       CYN "%-30s " WHT "�ȼ���" CYN "%d\n"
			       WHT, ob->name() + "(" + ob->query("id") + ")",
			       to_chinese(skill) + "(" + skill + ")", level);
		}
		write(NOR);
	}
	return 1;
}

int help()
{
	write(@LONG
ָ���ʽ��setsk  <ĳ��>  [ <����> | all ]  <������>

�����趨ĳ�˵�ĳ�ּ��ܵļ�����������ڶ����� all�������е�
���ܸ�Ϊ�趨�ļ����������ѡ���˼�����Ϊ����ɾ�����˴���ܡ�
���û��ָ��������ϵͳĬ�϶���Ϊʹ���ߡ�

LONG);
	return 1;
}
