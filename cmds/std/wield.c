// wield.c

inherit F_CLEAN_UP;

int do_wield(object me, object ob);

int main(object me, string arg)
{
	object ob,ob2, *inv;
	int i, count;

	if (! arg) return notify_fail("��Ҫװ��ʲô������\n");
	if (userp(me) && me->is_busy() )
		return notify_fail("����æ���ء�\n");

	if (arg == "all")
	{
		inv = all_inventory(me);
		for (count = 0, i = 0; i<sizeof(inv); i++)
		{
			if (inv[i]->query("equipped")) continue;
			if (inv[i]->is_item_make()&&inv[i]->item_owner()!=me->query("id")) continue;
			if (do_wield(me, inv[i])) count ++;
		}
		write("Ok.\n");
		return 1;
	}

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û������������\n");

//	if (ob->is_item_make()&&ob->item_owner()!=me->query("id"))
//		return notify_fail("����˵�˽��װ��װ�����㲻��ʹ�á�\n");

	if (ob->query("equipped"))
	{
		inv = all_inventory(me) - ({ ob });
		for (count = 0, i = 0; i < sizeof(inv); i++)
		{
			if (! inv[i]->id(arg)) continue;
			if (inv[i]->query("equipped")) continue;
			if (do_wield(me, inv[i]))
			{
				count++;
				break;
			}
		}
		if (! count)
			return notify_fail("���Ѿ�װ�����ˡ�\n");
		return 1;
	}

	if(ob2=me->query_temp("weapon"))
		me->force_me("unwield "+file_name(ob2));
	return do_wield(me, ob);
}

int do_wield(object me, object ob)
{
	string str;
	switch (ob->wield())
	{
	case 0:
		return 0;

	case -1:
		return 1;

	default:
		if (! stringp(str = ob->query("wield_msg")))
			str = "$Nװ��$n��������\n";
		if (userp(me) && me->is_fighting()) me->start_busy(1);
		message_vision(str, me, ob);
		return 1;
	}
}

int help(object me)
{
	write(@HELP
ָ���ʽ��wield <װ������>
 
���ָ������װ��ĳ����Ʒ������, �����Ҫӵ��������Ʒ.
 
HELP );
    return 1;
}
