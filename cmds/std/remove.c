// remove.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_remove(object me, object ob);

int main(object me, string arg)
{
	object ob, *inv;
	int i;
	int count;

	if (! arg) return notify_fail("��Ҫ�ѵ�ʲô��\n");

	if (arg == "all")
	{
		inv = all_inventory(me);
		for (count = 0, i = 0; i < sizeof(inv); i++)
			count += do_remove(me, inv[i]);
		if (count)
			write("�������ˡ�\n");
		else
			write("��ʲô��û����������\n");
		return 1;
	}

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û������������\n");

	if ((string)ob->query("equipped") != "worn")
	{
		inv = all_inventory(me);
		for (count = 0, i = 0; i < sizeof(inv); i++)
		{
			if (! inv[i]->id(arg))
				continue;

			if ((string)inv[i]->query("equipped") != "worn")
				continue;

			ob = inv[i];
			count++;
			break;
		}

		if (! count)
			return notify_fail("�㲢û��װ������������\n");
	}

	return do_remove(me, ob);
}

int do_remove(object me, object ob)
{
	string str;

	if ((string)ob->query("equipped")!="worn")
		return notify_fail("�㲢û��װ������������\n");

	switch (ob->unequip())
	{
	case -1:
		return 1;

	case 0:
		return 0;

	default:
		if (! stringp(str = ob->query("remove_msg")))
			switch (ob->query("armor_type"))
			{
			case "cloth":
			case "armor":
			case "surcoat":
			case "boots":
				str = YEL "$N��$n" YEL "����������"NOR"\n";
				break;
			case "bandage":
				str = YEL "$N��$n" YEL "���˿ڴ�����������"NOR"\n";
				break;
			default:
				str = YEL "$Nж��$n" YEL "��װ����"NOR"\n";
			}
		if (ob->query_temp("no_wear"))
			str += "����" + ob->name() + "�Ժ������������ˡ�\n";
		message_vision(str, me, ob);
		return 1;
	}
}

int help(object me)
{
	write(@HELP
ָ���ʽ : remove all | <��Ʒ����>
 
���ָ�������ѵ�����ĳ������.
 
HELP );
	return 1;
}
 
