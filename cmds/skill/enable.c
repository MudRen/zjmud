// enable.c

#include <ansi.h>

inherit F_CLEAN_UP;

mapping valid_types = ([
	"unarmed":      "ȭ��",
	"sword":	"����",
	"blade":	"����",
	"staff":	"�ȷ�",
	"hammer":       "����",
	"club" :	"����",
	"throwing":     "����",
	"force":	"�ڹ�",
	"xinfa":	"�ķ�",
	"parry":	"�м�",
	"dodge":	"�Ṧ",
	"magic":	"����",
	"whip":	 	"�޷�",
	"dagger":       "�̱�",
	"finger":       "ָ��",
	"hand":	 	"�ַ�",
	"cuff":	 	"ȭ��",
	"claw":	 	"צ��",
	"strike":       "�Ʒ�",
	"medical":      "ҽ��",
	"poison":       "����",
	"cooking":      "����",
	"chuixiao-jifa" : "����",
	"guzheng-jifa"  : "����",
	"tanqin-jifa"   : "����",
]);

int main(object me, string arg)
{
	mapping map;
	string *types, *skill, ski, map_to;
	string msg;
	int i, modify;

	seteuid(getuid());

	if (! arg)
	{
		map = me->query_skill_map();
		if (! mapp(map) || sizeof(map) == 0)
			return notify_fail("������û��ʹ���κ����⼼�ܡ�\n");

		skill = keys(valid_types);
		
		msg = ZJOBLONG"��������Ŀǰʹ���е����⼼�ܣ�\n";
		msg+=HIC+"��"+HIY+"һһһһһһһһһһһһһһһһһһһһһ"+HIC+"��"+NOR+"\n";
		for (i = 0; i < sizeof(skill); i++)
		{
			if (undefinedp(map[skill[i]]))
				continue;

			if (! me->query_skill(skill[i]))
				continue;

			modify = me->query_temp("apply/" + skill[i]);
			msg += sprintf("  %-14s�� %-18s  ��Ч�ȼ���%s%3d"NOR"\n",
				valid_types[skill[i]],
				undefinedp(map[skill[i]]) ? "��" : to_chinese(map[skill[i]]),
				(modify==0 ? "" : (modify>0 ? HIC : HIR)),
				me->query_skill(skill[i]));
		}
		msg+=HIC+"��"+HIY+"һһһһһһһһһһһһһһһһһһһһһ"+HIC+"��"+NOR+"\n";

		msg= replace_string(msg,"\n",ZJBR);
		if(msg[(strlen(msg)-4)..(strlen(msg)-1)]=="$br#")
			msg= msg[0..(strlen(msg)-5)];
		msg += "\n";
		write(msg);
		return 1;
	}

	if (arg == "?" )
	{
		msg = "�����ǿ���ʹ�����⼼�ܵ����ࣺ\n";
		skill = sort_array(keys(valid_types), (: strcmp :) );
		for (i = 0; i < sizeof(skill); i++)
			msg += sprintf("  %s (%s)\n", valid_types[skill[i]], skill[i]);
		write(msg);
		return 1;
	}

	if (sscanf(arg, "%s %s", ski, map_to) != 2)
		return notify_fail("ָ���ʽ��enable|jifa [<��������> <��������>|none]\n");

	if (undefinedp(valid_types[ski]))
		return notify_fail("û������������࣬�� enable ? ���Բ鿴����Щ���ࡣ\n");

	if (map_to == "none")
	{
		me->map_skill(ski);
		me->reset_action();
		write(HIW "���������ȡ��" HIG + CHINESE_D->chinese(ski) + HIW "�����⼼�ܡ�"NOR"\n");
		return 1;
	} else if (map_to == ski)
	{
		write("��" + to_chinese(ski) + "��������" + valid_types[ski] + "�Ļ���������Ҫ enable��\n");
		return 1;
	}

	if (me->query_skill_mapped(ski) == map_to)
		return notify_fail("���������������ּ����ء�\n");

	if (me->query_skill(map_to, 1) < 1)
		return notify_fail("�㲻�����ּ��ܡ�\n");

	if (me->query_skill(ski, 1) < 1)
		return notify_fail("�㻹������" + to_chinese(ski) + "�ء�\n");

	if (! SKILL_D(map_to)->valid_enable(ski))
		return notify_fail("������ܲ��ܵ���������;��\n");

	me->map_skill(ski, map_to);
	me->reset_action();
	write(HIW "�����������" HIR + CHINESE_D->chinese(map_to) + HIW "��Ϊ" HIG + CHINESE_D->chinese(ski) + HIW "�����⼼�ܡ�"NOR"\n");

	if (ski == "magic")
	{
		write("�������һ�ַ���ϵ�������������¶�����\n");
		me->set("jingli", 0);
		me->receive_damage("jing", 0);
	}
	else if (ski == "force")
	{
		write("�������һ���ڹ��������������¶�����\n");
		me->set("neili", 0);
		me->receive_damage("qi", 0);
	}

	return 1;
}
int help(object me)
{
	write(@HELP
ָ���ʽ : enable|jifa [<��������> <��������> | none]
	   enable|jifa ?

���ָ������ָ����Ҫ�õļ��ܣ���ָ����������ͼ������ơ�������Ӳ�
�������ʾ���������༰��Ŀǰ��ʹ�õļ������� �������һ�������г�
������ʹ�����⼼�ܵļ������ࡣ

HELP );
	return 1;
}
