// who3.c

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
	object ob;
	object *ob_list, *wiz_ob;
	mapping dbase;
	string *line;
	int i;
	int delta;

	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	seteuid(getuid());

	ob_list = users();
	wiz_ob = filter_array(ob_list, (: wizardp :));
	ob_list -= wiz_ob;

	wiz_ob  = sort_array(wiz_ob, "sort_wizard");
	ob_list = sort_array(ob_list, "sort_user");
	ob_list = wiz_ob + ob_list;

	i = 0;
	line = allocate(sizeof(ob_list) + 2);
	line[i++] = HIG" ���      ����-���� ����-���� ��-���� ����-���� �쳣 ��ò"NOR"\n"
		    WHT"��������������������������������������������������������������������"NOR"\n";
	foreach (ob in ob_list)
	{
		dbase = ob->query_entire_dbase();
		delta = dbase["int"] + dbase["con"] +
			dbase["str"] + dbase["dex"] - 80;
		line[i] = sprintf(NOR"%-10s  "
			       HIR"%2d:"
			       HIR"%4d "
			       HIG"%4d:"
			       HIG"%4d "
			       HIY"%4d:"
			       HIY"%4d "
			       HIB"%4d:"
			       HIB"%4d "
			       HIW"%4d "
			       HIM"%4d "NOR"\n",
			       ob->name(1),
			       dbase["int"],
			       ob->query_int(),
			       dbase["con"],
			       ob->query_con(),
			       dbase["dex"],
			       ob->query_dex(),
			       dbase["str"],
			       ob->query_str(),
			       delta,
			       dbase["per"]);

		i++;
	}
	line[i] = WHT"��������������������������������������������������������������������"NOR"\n" +
		  sprintf("%s���� %d λʹ���������С�\n", LOCAL_MUD_NAME(), sizeof(ob_list));

	str = implode(line, "");
	me->start_more(str);
	return 1;
}

int sort_wizard(object ob1, object ob2)
{
	return (int)SECURITY_D->get_wiz_level(ob2) -
	       (int)SECURITY_D->get_wiz_level(ob1);
}

int sort_user(object ob1, object ob2)
{
	return ob2->query("mud_age") - ob1->query("mud_age");
}

int help(object me)
{
	write(@HELP
ָ���ʽ��who3

�����Ϣ��ѯ�б�3��
HELP );
	return 1;
}	    
