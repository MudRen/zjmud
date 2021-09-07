#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	object nob;
	string my_id;
	int amount;
	int value;
	int res;
	int max_count;
	mixed ns;

	if (! arg)
		return notify_fail("��Ҫ��ʲô��\n");

	if (sscanf(arg, "%d %s", amount, arg) != 2)
		amount = 1;

	if (amount < 1)
		return notify_fail("�����ɶ��\n");

	if (! (ob = present(arg, me)))
	{
		write("������û�����ֶ�������\n");
		return 1;
	}

	max_count = ob->query_amount();
	if (! max_count)
	{
		if (amount > 1)
		{
			write(ob->name() + "���ֶ������ܲ�������\n");
			return 1;
		}
		max_count = 1;
	} else
	{
		if (amount > max_count)
		{
			write("������û����ô��" + ob->name() + "��\n");
			return 1;
		}
	}

	if (ob->query("money_id"))
	{
		write(CYN + "��������Ǯ������"NOR"\n");
		return 1;
	}

	if (ob->is_character())
	{
		write(CYN + "����ҲҪ������"NOR"\n");
		return 1;
	}
/*
	if (ob->query("no_drop") || (ns = ob->query("no_sell")))
	{
		if (stringp(ns))
		{
			write(CYN + "ϵͳ�������ε���" + ns + NOR"\n");
			return 1;
		}
		write(CYN + "�ⶫ������������"NOR"\n");
		return 1;
	}
*/
	if (ns = ob->query("no_sell"))
	{
		if (stringp(ns))
		{
			write(CYN + "ϵͳ�������ε���" + ns + NOR"\n");
			return 1;
		}
		write(CYN + "�ⶫ������������"NOR"\n");
		return 1;
	}
	if (ob->query("food_supply"))
	{
		write(CYN + "ʣ��ʣ�����������Լ��ðɣ���"NOR"\n");
		return 1;
	}
	
	if (ob->query("shaolin"))
	{
		write(CYN + "���������������ô�����������"NOR"\n"); 
		return 1;
	}

	if (ob->query("mingjiao"))
	{
		write(CYN + "ħ�̵Ķ����ɲ������������Σ�յģ���"NOR"\n");
		return 1;
	}

	if (max_count > 1)
		value = ob->query("base_value") * amount;
	else
		value = ob->query("value");

	if (ob->query("consistence"))
		value = value * ob->query("consistence") / 100;

	if (value < 2)
		write(CYN + ob->query("name") + "һ�Ĳ�ֵ��ֱ�Ӷ����ɣ���"NOR"\n");
	else
	{
		write("��������һ" + ob->query("unit") +  ob->query("name") + "�õ�" + MONEY_D->money_str(value*50/100) + "��\n");
	      log_file("pay/sellob", sprintf("%s��"+me->query("id")+"����%s���%s��\n",ctime(time()),ob->query("name"),MONEY_D->money_str(value*50/100) ));
		if (max_count == amount)
			destruct(ob);
		else
			ob->add_amount(-amount);
		MONEY_D->pay_player(me, value * 50 / 100);
	}
	return 1;
}

int help(object me)
{
     write(@HELP
ָ���ʽ: sellob <��Ʒid>

������������

HELP
    );
    return 1;
}
