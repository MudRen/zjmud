// banker.c ���м�

#include <dbase.h>
#include <ansi.h>

int do_check()
{
	// here we use 3 units to display bank infos
	int total = (int)this_player()->query("balance");
	if (!total || total < 0)
	{
		this_player()->set("balance", 0);
		write(ZJOBLONG"���ڱ��̺�û�д�Ǯ��\n");
		return 1;
	}
	write(ZJOBLONG+this_object()->query("name")+"���ĸ����㣺���ڱ��̺Ź�����" + MONEY_D->money_str(total) + "��\n");
	return 1;							       
}

int do_convert(string arg)
{
	string from, to;
	int amount, bv1, bv2;
	object from_ob, to_ob;
	object me;

	me = this_player();						     

	if (me->is_busy())
		return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

	if (this_object()->is_fighting())
		return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

	if (! arg || sscanf(arg, "%d %s to %s", amount, from, to) != 3)
	{
	   	return notify_fail("�����ʽ��convert|duihuan <����> <���ҵ�λ> to <�»��ҵ�λ>\n");
	}

	from_ob = present(from + "_money", me);
	to_ob = present(to + "_money", me);

	if (! to_ob && file_size("/clone/money/" + to + ".c") < 0)
	   	return notify_fail("����һ���ʲô��\n");

	if (! from_ob)
	   	return notify_fail("������û�д�����Ǯ��\n");

	if (from_ob == to_ob)
		return notify_fail("����ë������\n");

	if (amount < 1)
	   	return notify_fail("�����׬����\n");

	if ((int)from_ob->query_amount() < amount)
	   	return notify_fail("�����" + from_ob->query("name") + "������\n");

	bv1 = from_ob->query("base_value");
	if (! bv1)
	   	return notify_fail("����������ֵǮ��\n");

	bv2 = to_ob ? to_ob->query("base_value")
		    : call_other("/clone/money/" + to, "query", "base_value");
	if (bv1 < bv2)  amount -= amount % (bv2 / bv1);
	if (amount == 0)
	   	return notify_fail("��Щ" + from_ob->query("name") + "��������\n ");

	if (bv1 > bv2 && bv1 / bv2 * amount > 10000)
		return notify_fail("Ŷ��...����һ���ӻ��ò�����ô��ɢǮ...\n");

	// allowed to convert now
	me->start_busy(1);

	from_ob->add_amount(-amount);

	if (! to_ob)
	{
		to_ob = new("/clone/money/" + to);
		to_ob->set_amount(amount * bv1 / bv2);
		to_ob->move(me, 1);
	}
	else
		to_ob->add_amount(amount * bv1 / bv2);

	message_vision(sprintf("$N������ȡ��%s%s%s��������%s%s%s��\n",
			       chinese_number(amount),
			       from_ob->query("base_unit"),
			       from_ob->query("name"),
			       chinese_number(amount * bv1 / bv2),
			       to_ob->query("base_unit"),
			       to_ob->query("name")), me);

	return 1;
}									       

int do_deposit(string arg)						      
{
	string what,str;
	int amount, money_limit,i;
	object *inv,what_ob, me,obj;

	me = this_player();

	if (me->is_busy())
		return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

	if (this_object()->is_fighting())
		return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

	if (!arg)
	{
		inv = all_inventory(me);
		str = ZJOBACTS2+ZJMENUF(1,1,8,30);
		for(i=0;i<sizeof(inv);i++)
		{
			if(inv[i]->query("money_id"))
			{
				if(str!=ZJOBACTS2+ZJMENUF(1,1,8,30))
					str += ZJSEP+inv[i]->short()+":cun "+inv[i]->query("id");
				else
					str += inv[i]->short()+":cun "+inv[i]->query("money_id");
			}
		}
		if(str==ZJOBACTS2+ZJMENUF(1,1,8,30))
		{
			write(ZJOBLONG"������ûʲôǮ����Ҫ��ʲô��\n");
		}
		else
		{
			write(ZJOBLONG"��ѡ��Ҫ��Ļ��ң�\n"+str+"\n");
		}
		return 1;
	}

	if (sscanf(arg, "%d %s", amount, what) != 2)
	{
		if (! objectp(obj = present(arg, me)))
			return notify_fail(ZJOBLONG"��Ҫ��ʲô��\n");
		write(INPUTTXT("�㹲��"+obj->short()+"���������٣�","cun $txt# "+ arg)+"\n");
		return 1;
	}

	what_ob = present(what + "_money", me);
	if (! what_ob)
		return notify_fail("������û�д�����Ǯ��\n");

	if (amount < 1)
		return notify_fail("��������" + what_ob->query("name") + "��\n");

	if ((int)what_ob->query_amount() < amount)
		return notify_fail("�����" + what_ob->query("name") + "������\n");

	// deposit it
	me->start_busy(1);

	if (me->query("balance") >= 1000000000)
		return notify_fail("��Ĵ���Ѵ����ޡ�\n");


	message_vision(sprintf("$N�ó�%s%s%s����������š�\n",
	chinese_number(amount), what_ob->query("base_unit"),
	what_ob->query("name")), me);

	me->add("balance", what_ob->query("base_value") * amount);
	what_ob->add_amount(-amount);

	return 1;
}

int do_withdraw(string arg)
{
	string what,type;
	int amount, money_limit;
	object ob, me;
	int v;

	me = this_player();

	if (me->is_busy())
		return notify_fail("�㻹�ǵ��п�����˵�ɣ�\n");

	if (this_object()->is_fighting())
		return notify_fail("Ӵ����Ǹ�����������æ���ء��������Ժ�\n");

	if (!me->query("balance")||me->query("balance")<0)
		return notify_fail(ZJOBLONG"���ڱ���û���ɣ�\n");

	if (!arg)
	{
		write(ZJOBLONG"��ѡ��Ҫȡ���Ļ������ࣺ\n"ZJOBACTS2+ZJMENUF(4,4,8,30)"�ƽ�:qu gold"ZJSEP"��Ʊ:qu cash"ZJSEP"����:qu silver"ZJSEP"ͭǮ:qu coin\n");
		return 1;
	}

	if (sscanf(arg, "%d %s", amount, what) != 2)
	{
		if(arg=="cash")
		{
			if((money_limit=me->query("balance")/100000)<1)
				return notify_fail(ZJOBLONG"���ڱ���Ĵ���һ��ǧ����Ʊ������֧ȡ��\n");
			type = "��ǧ����Ʊ";
		}
		else if(arg=="gold")
		{
			if((money_limit=me->query("balance")/10000)<1)
				return notify_fail(ZJOBLONG"���ڱ���Ĵ���һ���ƽ𣬲���ȡ���ƽ�\n");
			type = "���ƽ�";
		}
		else if(arg=="silver")
		{
			if((money_limit=me->query("balance")/100)<1)
				return notify_fail(ZJOBLONG"���ڱ���Ĵ���һ������������֧ȡ��\n");
			type = "������";
		}
		else if(arg=="coin")
		{
			if((money_limit=me->query("balance"))<1)
				return notify_fail(ZJOBLONG"���ڱ���Ĵ���һöͭ�壬����֧ȡ��\n");
			type = "öͭ��";
		}
		write(INPUTTXT("����Ŀǰ�Ĵ�������ȡ��"+money_limit+type+"������ȡ������"+type+"��","qu $txt# "+ arg)+"\n");
		return 1;
	}

	if (amount < 1)
		return notify_fail("����ȡ������Ǯ��\n");

	if(amount >= 10000)
		return notify_fail("��ô�����Ŀ������û��ô����ɢ�ֽ�\n");

	if (file_size("/clone/money/" + what + ".c") < 0)
		return notify_fail("����ȡ��ʲôǮ��\n");

	what = "/clone/money/" + what;
	if ((v = amount * what->query("base_value")) > me->query("balance") || v <= 0)
	       return notify_fail("����Ǯ����ȡ��\n");

	ob = new(what);
	ob->set_amount(amount);
	type = ob->short();
	if(ob->move(me))
	{
		me->start_busy(1);
		me->add("balance", -v);
		message_vision(sprintf("$N��������ȡ��%s��\n",type), me);
	}
	else
	{
		destruct(ob);
		return notify_fail("ȡǮʧ�ܡ�\n");
	}
	return 1;
}

