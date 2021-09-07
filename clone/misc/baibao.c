// baibao.c
// by ranger_����

#include <ansi.h>
inherit ITEM;
inherit F_SAVE;

mapping baowus;

void create()
{
	set_name(HIW"�����"NOR, ({ "chuwu dai" }) );
	set("long",HIW"һ������Ĵ��ӣ����Դ�ȡ��౦����"NOR"\n");
	set("unit", "��");
	set("no_put", 1);
	set("no_get", 1);
	set("no_give", 1);
	set("no_drop", 1);
	set("no_sell", 1);
	set("no_steal", 1);
	seteuid(getuid());
}

string query_save_file()
{
	string id;

	if( !stringp(id = query("owner_id")) ) return 0;

	return sprintf(DATA_DIR"baibao/%c/%s", id[0], id);
}

int set_owner(string id)
{
	set("owner_id", id);
	return 1;
}

void init()
{
	if(!query("owner_id"))
	{
		set_owner(this_player()->query("id"));
	}

	if(this_player()->query("id")==query("owner_id"))
	{
		add_action("do_cunbao","baocun");
		add_action("do_qubao","tiqu");
		add_action("do_chabao","dlist");
		restore();
	}
}

int do_cunbao(string arg)
{
	object me,ob;
	string *item_nb,nb;
	int i,snum;
	mapping info=([]);

	me = this_player();
	if(!arg)
		return notify_fail("��Ҫ������д�ʲô������\n");

	if(!objectp(ob=present(arg,me)))
		return notify_fail("������û�����ֱ����ɣ�\n");

//������Ʒ���ܱ���
	if (ob->query("unique") || ! clonep(ob) )
	{
		tell_object(me, ob->name() + "���ܷ��봢�����\n");
		return 1;
	}

//װ������Ʒ���ܱ���
	switch((string)ob->query("equipped")) 
	{
	case "worn":
		tell_object(me, ob->name() + "���������������ܴ�š�\n");
		return 1;
	case "wielded":
		tell_object(me, ob->name() + "�����Ƚ��װ�����ܴ�š�\n");
		return 1;
	}

//�ں���Ʒ��������Ʒ���ܱ���
	if (sizeof(all_inventory(ob))) 
	{
		tell_object(me, "�����Ȱ�" + ob->query("name") + "����Ķ������ó�����\n");
		return 1;
	}


//������Լ�����಻�ܱ�����Ʒ���ж�
//////ʬ�壬����ȵȡ�����

	if(!clonep(ob)
	||ob->query("unique")
	||ob->query("treasure")
	||ob->query("owner")
	||ob->query("no_put")
	||ob->query("u_times")
	||ob->query("quest")
	||ob->is_corpse()
	||ob->query("food_remaining")
	||ob->query("liquid")
	||ob->query("material")=="meat"
	||ob->query("money_id")
	||ob->is_character()
	||(stringp(ob->query("owner")) && ob->query("owner")!="0")
	||ob->query("credit")
	) return notify_fail("����������ܴ��봢�����\n");

	snum = 20 + me->query("zjvip/all_pay")/10 + me->query("combat_exp")/50000;
        if (snum>100) snum=100;

	if (mapp(baowus)&&(sizeof(keys(baowus))>=snum))
		return notify_fail("��Ĵ�����Ѿ��Ų��¸�����Ʒ�ˣ��Ͻ�����һ�°ɡ�\n");

	info["short"] = ob->query("name");
	info["id"] = ob->parse_command_id_list();
	info["file"] = base_name(ob);
	info["data"] = save_variable(ob->query_entire_dbase());
	if(ob->query_amount()) info["amount"] = ob->query_amount();

	if( !mapp(baowus)) baowus = ([]);
	if( baowus == ([]))
	{
		baowus["1"] = info;
		destruct(ob);
		save();
	}
	else
	{
		item_nb = sort_array( keys(baowus), (: strcmp :) );
		for(i=1; i<(sizeof(item_nb)+2); i++) {
			nb = sprintf("%d",i);
			if(undefinedp(baowus[nb]))
			{
				baowus[nb] = info;
		tell_object(me,"���"+ob->query("name") + "���봢�����\n");
				destruct(ob);
				save();
				break;
			}
		}
	}
	if(objectp(ob))
		tell_object(me,"��Ʒ����ʧ�ܣ�\n");
	else
		tell_object(me,"��Ʒ����ɹ���\n");
	return 1;
}

int do_qubao(string arg)
{
	object me,ob;
	string *item_nb;
	int i;

	me = this_player();

	if( !mapp(baowus) || baowus==([]))
		return notify_fail("��Ĵ������ûʲô������ȡ�ġ�\n");
	if(!arg)
		return notify_fail("��Ҫ�Ӵ������ȡ��ʲô������\n");

	if(undefinedp(baowus[arg]))
		return notify_fail("��Ĵ������ûû�������ŵ���Ʒ��\n");

	ob = new(baowus[arg]["file"]);

	ob->set_entire_dbase(restore_variable(baowus[arg]["data"]));
	ob->set_name(baowus[arg]["short"],baowus[arg]["id"]);
	if(baowus[arg]["amount"]) ob->set_amount(baowus[arg]["amount"]);

	if(ob->move(me))
	{
		map_delete(baowus, arg);
		save();
		tell_object(me,"���"+ob->query("name")+"�Ӵ������ȡ����\n");
		tell_object(me,"��Ʒȡ���ɹ���\n");
	}
	else
		tell_object(me,"����ȡ��ʧ�ܣ�\n");

	return 1;
}

int do_chabao(string arg)
{
	object me;
	string *item_nb;
	string msg, ob_name;

	me = this_player();

	msg = ZJOBLONG"����һ������Ĵ��ӣ����Դ�ȡ�öණ����"ZJBR;
	if( !mapp(baowus) )
	{
		msg += "��Ŀǰû�д���κ���Ʒ�ڴ�����\n";
		return  notify_fail(msg);     
	}
	item_nb = sort_array( keys(baowus), (: strcmp :) );

	if( sizeof(item_nb)<1 )
	{
		msg += "��Ŀǰû�д���κ���Ʒ�ڴ�����\n";
		return  notify_fail(msg);     
	}

	msg += HIW"Ŀǰ�㴢�������Ʒ�У�"ZJBR
		  "һһһһһһһһһһһһһһһһһһһһһһһ"NOR"\n";
	msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
	for (int i = 0; i < sizeof(item_nb); i++) 
	{
		ob_name = baowus[item_nb[i]]["short"];
		if(baowus[item_nb[i]]["amount"])
			ob_name += "["+baowus[item_nb[i]]["amount"]+"]";
		msg += sprintf("[%3s] %s:%s"ZJSEP, item_nb[i], ob_name,"tiqu "+item_nb[i]);
	}
	write(msg+"\n");
	return 1;
}	

string long()
{
	object me;
	string *item_nb;
	string msg, msg2,ob_name;

	me = this_player();

	msg = ZJOBLONG"����һ������Ĵ��ӣ����Դ�ȡ�öණ����"ZJBR;
	if( !mapp(baowus) )
	{
		msg += "��Ŀǰû�д���κ���Ʒ�ڴ�����\n";
		write(msg+"\n");
		return  "";     
	}
	item_nb = sort_array( keys(baowus), (: strcmp :) );

	if( sizeof(item_nb)<1 )
	{
		msg += "��Ŀǰû�д���κ���Ʒ�ڴ�����\n";
		write(msg+"\n");
		return  "";     
	}

	msg += HIW"Ŀǰ�㴢�������Ʒ�У�"ZJBR
		  "һһһһһһһһһһһһһһһһһһһһһһһ"NOR"\n";
	msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
	for (int i = 0; i < sizeof(item_nb); i++) 
	{
		ob_name = baowus[item_nb[i]]["short"]; 
		if(baowus[item_nb[i]]["amount"])
			ob_name += "["+baowus[item_nb[i]]["amount"]+"]";
		msg += sprintf("[%3s] %s:%s"ZJSEP, item_nb[i], ob_name,"tiqu "+item_nb[i]);
	}
	write(msg+"\n");
	return "";
}	

int query_autoload() { return 1; }
