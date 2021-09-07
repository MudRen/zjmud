// wear.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int do_wear(object me, object ob);

int main(object me, string arg)
{
	object ob,ob2, *inv;
	int i, count;

	if (! arg) return notify_fail("��Ҫ����ʲô��\n");
	if (userp(me) && me->is_busy() )
		return notify_fail("����æ���ء�\n");

	if (arg == "all")
	{
		inv = all_inventory(me);
		for(count = 0, i = 0; i < sizeof(inv); i++)
		{
			if (inv[i]->query("equipped")) continue;
			if (inv[i]->is_item_make()&&inv[i]->item_owner()!=me->query("id")) continue;
			if (do_wear(me, inv[i])) count++;
		}
		if (! count)
			write("��ʲô��û�д��ϡ�\n");
		else
			write("�㴩���ˡ�\n");
		return 1;
	}

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û������������\n");

//	if (ob->is_item_make()&&ob->item_owner()!=me->query("id"))
//		return notify_fail("����˵�˽��װ��װ�����㲻��ʹ�á�\n");

	if (ob->query("equipped"))
	{
		inv = all_inventory(me) - ({ ob });
		for(count = 0, i = 0; i < sizeof(inv); i++)
		{
			if (! inv[i]->id(arg)) continue;
			if (inv[i]->query("equipped")) continue;
			if (do_wear(me, inv[i]))
			{
				count++;
				break;
			}
		}
		if (! count)
			return notify_fail("���Ѿ�װ�����ˡ�\n");

		return 1;
	}

	if (ob2=me->query_temp("armor/" + ob->query("armor_type")))
		me->force_me("remove "+file_name(ob2));

	return do_wear(me, ob);
}

int do_wear(object me, object ob)
{
	string str;
	mapping p;
	mixed notice;
	str="";
	if (notice = ob->query_temp("no_wear"))
	{
		if (stringp(notice)) write(notice);
		return notify_fail("�������Ա�İɣ�\n");
	}

	if (ob->query("female_only") &&
	    (string)me->query("gender") =="����")
		return notify_fail("����Ů�˵���������һ��������Ҳ�봩����Ҳ���ߣ�\n");

	switch (ob->wear())
	{
	case 0:
		return 0;

	case -1:
		return 1;

	default:
		str = ob->query("wear_msg");
		if (!stringp(str))
			switch (ob->query("armor_type"))
			{
				case "cloth":
				case "armor":
				case "boots":
				case "pants":
					str = YEL "$N����һ" + ob->query("unit") + "$n" YEL "��"NOR"\n";
					break;
				case "head":
				case "neck":
				case "wrists":
				case "hands":
					str = YEL "$N����һ" + ob->query("unit") + "$n" YEL "��"NOR"\n";
					break;
				case "waist":
					str = YEL "$N��һ" + ob->query("unit") + "$n" YEL "�������䡣"NOR"\n";
					break;
				default:
					str = YEL "$Nװ��$n" YEL "��"NOR"\n";
			}
		if (ob->query_temp("daub") &&
		    ob->query("armor_type") != "hands")
			DAUB_CMD->check_poison(me, ob);

		message_vision(str, me, ob);
		return 1;
	}
}

int help(object me)
{
	write(@HELP
ָ���ʽ��wear <װ������>
 
���ָ������װ��ĳ�����ߡ�
 
HELP );
	return 1;
}
