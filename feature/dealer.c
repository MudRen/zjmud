// dealer.c ����

#include <ansi.h>
#include <dbase.h>
#include <name.h>
#include <config.h>

int is_vendor() { return 1; }

string is_vendor_good(string arg)
{
	mixed goods;
	object ob;
	int i;

	goods = query("vendor_goods");
	if (mapp(goods))
		goods = keys(goods);

	if (arrayp(goods))
		for (i = 0; i < sizeof(goods); i++) 
		{
			if (goods[i]->id(arg)) return goods[i];
			if (filter_color(goods[i]->name(1)) == arg)
				return goods[i];
		}
	return "";
}

string value_string(int value)
{
	if( value < 1 ) value = 1;
	else	if( value < 100 )
	return chinese_number(value) + "��Ǯ";
	else	if( value < 10000 )
	return chinese_number(value/100) + "������"
		+ (value%100? "��" + chinese_number(value%100) + "��Ǯ": "");
	else
	return chinese_number(value/10000) + "���ƽ�"
		+( (value%10000)/100 ? chinese_number((value%10000)/100) + "������" : "")
		+( (value%10000)%100 ? "��" + chinese_number((value%10000)%100) + "��Ǯ": "");
}
int pay_player(object who, int amount)
{
	object ob;
	int total;
	if( amount < 1 ) amount = 1;
	if( amount/10000 ) {
	if (!ob=present("gold_money", who)){
			ob = new(GOLD_OB);
		if (!ob->move(who)) ob->move(environment(who));
	}else total=ob->query_amount();
		ob->set_amount(amount/10000+total);
		amount %= 10000;
	}
	if( amount/100 ) {
	if (!ob=present("silver_money", who)){
			ob = new(SILVER_OB);
		if (!ob->move(who)) ob->move(environment(who));
	}else total=ob->query_amount();
		ob->set_amount(amount/100+total);
	amount %= 100;
	}
	if( amount ) {
	if (!ob=present("coin_money", who)){
		ob = new(COIN_OB);
		if (!ob->move(who)) ob->move(environment(who));
	}else total=ob->query_amount();
		ob->set_amount(amount+total);
	}
	return 1;
}
int do_pawn(string arg)
{
	return notify_fail("��Ҫ�䵱ʲ����Ʒ��\n");
}
int do_check(string arg)
{
	return notify_fail(this_object()->query("name")+"˵�����͹ٲ�δ�ڱ���䵱���κ���Ʒ��\n");
}
int do_redeem(string arg)
{
	return notify_fail(this_object()->query("name")+"˵�����͹ٲ�δ�ڱ���䵱���κ���Ʒ��\n");
}
int do_value(string arg)
{
	return notify_fail("��Ҫ��ʲ����Ʒ�����̹��ۣ�\n");
}

int do_sell(string arg)
{
	return notify_fail("��Ҫ��ʲô��\n");
}

int do_list(string arg)
{
	mixed  goods;
	string *gks;
	object *obs,me;
	string msg;
	int i;

	mapping vip;
	mapping count;
	mapping amo;
	mapping price;
	mapping unit;
	mapping long;
	string  short_name;
	string  prefix;
	string  *dk;
	me=this_player();
	if (arg && ! id(arg))
		return 0; // Don't notify_fail

	vip = ([]);
	count   = ([]);
	amo   = ([]);
	unit	= ([]);
	price   = ([]);
	long   = ([]);

	goods = query("vendor_goods");
	if (arrayp(goods) || mapp(goods))
	{
		gks = mapp(goods) ? keys(goods) : goods;
		for (i = 0; i < sizeof(gks); i++)
		{
			object gob;
			call_other(gks[i], "???");
			if (! objectp(find_object(gks[i])))
			{
				log_file("log", sprintf("No found vendor good:%s\n", gks[i]));
				continue;
			}
			gob = find_object(gks[i]);
			short_name = gob->name(1);
			if (! undefinedp(unit[short_name]))
			{
				count[short_name] = -1;
				continue;
			}
			if (gob->query("base_unit"))
				prefix = "base_";
			else
				prefix = "";
			amo += ([ short_name : (gob->query("base_unit")? 1 : 0) ]);
			count += ([ short_name : -1 ]);
			unit  += ([ short_name : gob->query(prefix + "unit") ]);
			if(stringp(gob->query("spectxt")))
				long += ([ short_name : replace_string(gob->query("spectxt"),"\n","") ]);
			if (gob->query("yuanbao"))
			{
				vip += ([ short_name : 1]);
				price += ([ short_name : gob->query("yuanbao") ]);
			}
			else
				price += ([ short_name : (mapp(goods) && goods[gks[i]] > 0) ? goods[gks[i]] : gob->query(prefix + "value") ]);
		}
	}

	dk = sort_array(keys(unit), 1);
 
	if(!sizeof(dk))  
	{
		write(ZJOBLONG+HIG"��ʱû�������϶�����С��Ҳ�䲻����Ʒ������"NOR"\n");	 
	}
	else
	{
		msg = HIG"�������"+this_object()->name()+"����������Ʒ:"NOR"\n"ZJOBACTS2+ZJMENUF(2,2,7,32);
		for (i = 0; i < sizeof(dk); i++)
		{
			int p;
			p = price[dk[i]];
			if (count[dk[i]] > 0) p = p * 12 / 10;
			if(!long[dk[i]])
			{
				if(amo[dk[i]])
					msg += sprintf(WHT"%s"NOR+"��%s:buy %s"ZJSEP, dk[i], vip[dk[i]]?(sprintf("%d",p)+"Ԫ��"):MONEY_D->money_str(p),filter_color(dk[i]));
				else
					msg += sprintf(WHT"%s"NOR+"��%s:buy 1 %s"ZJSEP, dk[i],vip[dk[i]]?(sprintf("%d",p)+"Ԫ��"):MONEY_D->money_str(p),filter_color(dk[i]));
			}
			else
			{
				if(amo[dk[i]])
					msg += sprintf(WHT"%s"NOR+"��%s"ZJBR"%s:buy %s"ZJSEP, dk[i], vip[dk[i]]?(sprintf("%d",p)+"Ԫ��"):MONEY_D->money_str(p),long[dk[i]],filter_color(dk[i]));
				else
					msg += sprintf(WHT"%s"NOR+"��%s"ZJBR"%s:buy 1 %s"ZJSEP, dk[i],vip[dk[i]]?(sprintf("%d",p)+"Ԫ��"):MONEY_D->money_str(p),long[dk[i]],filter_color(dk[i]));
			}
		}
		if(msg[(strlen(msg)-4)..(strlen(msg)-1)]=="$zj#")
			msg = msg[0..(strlen(msg)-5)];
		msg += "\n";
		write(ZJOBLONG+msg);
	}   
	return 1;
}	 

int do_buy(string arg)
{
	mapping goods;
	int	amount;
	int	value,yuanbao, val_factor;
	string  ob_file;
	object *obs;
	object  ob;
	string  my_id;
	string  start_room;
	object  room;
	object  nob,me;
	mapping room_obmap;
	int i;
	
	if (! arg)
		return notify_fail("������ʲô��\n");

	if (sscanf(arg, "%s from %s", arg, my_id) == 2 && ! id(my_id))
		return 0;

	me = this_player();
	if (! query("carried_goods"))
	{
		if (stringp(start_room = query("startroom")) &&
			(room = find_object(start_room)) != environment())
		{
			// I am not in start room.
			message_vision("$N���һ���������ã�����ô�ܵ�������ˣ���\n"
					  "˵��ͷҲ���صļ���ææ�������ˡ�\n", this_object());
			if (!objectp(room) || !mapp(room_obmap = room->query_temp("objects")) || member_array(this_object(), values(room_obmap)) == -1)
			{
				destruct(this_object());
			} else
				this_object()->move(room);
			return 1;
		}
	}

	if (sizeof(filter_array(all_inventory(me), (: ! $1->query("equipped") :))) >= MAX_ITEM_CARRIED)
	{
		write("�����ϵĶ���̫���ˣ��ȴ���һ���������ɡ�\n");
		return 1;
	}

	if (sscanf(arg, "%d %s", amount, arg) != 2)
	{
		write(INPUTTXT("��Ҫ����١�"+arg+"����","buy $txt# "+arg)+"\n");
		return 1;
	}

	if (amount > 100)
	{
		write(CYN + name() + "æ��������������һ�������һ�ټ�����"NOR"\n");
		return 1;
	}

	if (amount <= 0)
	{
		write(CYN + name() + "��е�����������Ҫ�ҵ���Ǯ���㰡����"NOR"\n");
		return 1;
	}

	// no present or equipped
	ob = present(arg, this_object());
	if (! ob && arg[0] > 160)
	{
		for (i = 0; i < sizeof(obs = all_inventory()); i++)
			if (filter_color(obs[i]->name(1)) == arg)
			{
				ob = obs[i];
				break;
			}
	}

	if (! ob || ob->query("equipped"))
	{
		if ((ob_file = is_vendor_good(arg)) == "")
		{
			write(ob ? "�˼������Ű�����ô�������㣿\n"
				: "������ʲô��\n");
			return 1;
		}
		ob = new(ob_file);
		if (amount > 1) ob->set_amount(amount);
		val_factor = 10;
		call_out("destruct_it", 0, ob);
	} else
	{
		if (ob->query_amount())
		{
			object old_ob;
			if (amount > ob->query_amount())
			{
				write("�˼������û����ô���" + ob->name() + "��\n");
				return 1;
			}
			ob = new(base_name(old_ob = ob));
			ob->set_amount(amount);
			ob->set_temp("moved_from", old_ob);
			call_out("destruct_it", 0, ob);
		}
		val_factor = 12;
	}

	if (ob->query("money_id"))
	{
		write(CYN + name() + "��Ц��������������Ҫ��Ǯ������˼����"NOR"\n");
		return 1;
	}

	if (query_temp("busy"))
	{
		write(CYN + name() + CYN "���ͷ�������û�����������æ��ô����"NOR"\n");
		return 1;
	}

	if(ob->query("yuanbao"))
		yuanbao = ob->query("yuanbao");

	if(ob->query_amount())
		value = ob->query("base_value");
	else
		value = ob->query("value");
	if (value > 100000000 || value * val_factor / val_factor != value)
	{
		write(CYN + name() + CYN "��ʧɫ��������ô��һ�����⣿�ҿɲ���������"NOR"\n");
		return 1;
	}

	value = value * val_factor / 10;

	if (mapp(goods = query("vendor_goods")) && (int)goods[base_name(ob)] > 0)
	{
		value = goods[base_name(ob)];
		if (value * amount / amount != value)
		{
			write(CYN + name() + CYN "��ʧɫ��������ô��һ�����⣿�ҿɲ���������"NOR"\n");
			return 1;
		}
	}
	value *= amount;

	if (amount > 10 && ! ob->query_amount())
	{
		write(ob->name() + "һ�����ֻ����10" + ob->query("unit")+"��\n");
		return 1;
	}

	if(yuanbao)
	{//Ԫ������
		if((amount*yuanbao)>me->query("yuanbao"))
		{
			write(CYN + name() + "˵������������ô��Ԫ��ô?��"NOR"\n");
			return 1;
		}
		set_temp("busy", 1);
		if (ob->query_amount())
		{
			message_vision("$N��$n����������" + ob->short() + "��\n",me, this_object());
			ob->move(me, 1);
		}
		else
		{
			message_vision("$N��$n����������"+ amount + ob->query("unit") + ob->query("name") + "��\n", me, this_object());
			for(i=0;i<amount;i++)
			{
				nob = new(base_name(ob));
				nob->move(me,1);
			}
		}
		me->add("yuanbao",-amount*yuanbao);
		me->add("zjvip/yuanbao_used",amount*yuanbao);
		if (objectp(ob->query_temp("moved_from")))
		{
			ob->query_temp("moved_from")->add_amount(-amount);
			ob->delete_temp("moved_from");
		}
	}
	else
	switch (MONEY_D->player_pay(me, value))
	{
	case 0:
		write(CYN + name() + "��Ц��������⵰��һ�ߴ���ȥ����"NOR"\n");
		return 1;
	case 2:
		write(CYN + name() + "��ü������������û����Ǯ������Ʊ�ҿ��Ҳ�������"NOR"\n");
		return 1;
	default:
		set_temp("busy", 1);
		if (ob->query_amount())
		{
			message_vision("$N��$n����������" + ob->short() + "��\n",me, this_object());
			ob->move(me, 1);
		}
		else
		{
			message_vision("$N��$n����������"+ amount + ob->query("unit") + ob->query("name") + "��\n", me, this_object());
			for(i=0;i<amount;i++)
			{
				nob = new(base_name(ob));
				nob->move(me,1);
			}
			call_out("destruct_it", 0, ob);
		}
		if (objectp(ob->query_temp("moved_from")))
		{
			ob->query_temp("moved_from")->add_amount(-amount);
			ob->delete_temp("moved_from");
		}
	}
	remove_call_out("enough_rest");
	call_out("enough_rest", 1 + random(3));

	return 1;
}

void destruct_it(object ob)
{
	if (! ob || environment(ob))
		return;
	destruct(ob);
}

void enough_rest()
{
	delete_temp("busy");
}

void reset()
{
	int i;
	object *obs;

	obs = all_inventory();
	for (i = 0; i < sizeof(obs); i++)
		if (i >= 100 || obs[i]->query_weight() >= 1000000)
			destruct(obs[i]);
}
int do_pointlist(string arg)
{
	mixed  goods;
	string *gks;
	object *obs,me;
	string msg;
	int i;

	mapping count;
	mapping price;
	mapping unit;
	string  short_name;
	string  prefix;
	string  *dk;
	me=this_player();
	if (arg && ! id(arg))
		return 0; // Don't notify_fail

	count   = ([]);
	unit	= ([]);
	price   = ([]);
	if (obs = all_inventory())
		for (i = 0; i < sizeof(obs); i++)
		{
			if (obs[i]->query("equipped") ||
				obs[i]->query("money_id") ||
				obs[i]->is_character())
				continue;
			short_name = obs[i]->name(1) + "(" +
					obs[i]->query("id") + ")";
			if (obs[i]->query("base_unit"))
				prefix = "base_";
			else
				prefix = "";
			if (! undefinedp(unit[short_name]))
			{
				count[short_name] += (prefix == "" ? 1 : obs[i]->query_amount());
				continue;
			}
			count += ([ short_name : (prefix == "" ? 1 : obs[i]->query_amount()) ]);
			unit  += ([ short_name : obs[i]->query(prefix + "unit") ]);
			price += ([ short_name : obs[i]->query(prefix + "suit_point") ]);
		}
	
	goods = query("vendor_goods");
	if (arrayp(goods) || mapp(goods))
	{
		gks = mapp(goods) ? keys(goods) : goods;
		for (i = 0; i < sizeof(gks); i++)
		{
			object gob;
			call_other(gks[i], "???");
			if (! objectp(find_object(gks[i])))
			{
				log_file("log", sprintf("No found vendor good:%s\n", gks[i]));
				continue;
			}
			gob = find_object(gks[i]);
			short_name = gob->name(1) + "(" +
					gob->query("id") + ")";
			if (! undefinedp(unit[short_name]))
			{
				count[short_name] = -1;
				continue;
			}
			if (gob->query("base_unit"))
				prefix = "base_";
			else
				prefix = "";
			count += ([ short_name : -1 ]);
			unit  += ([ short_name : gob->query(prefix + "unit") ]);
			price += ([ short_name : (mapp(goods) && goods[gks[i]] > 0) ? goods[gks[i]]
								: gob->query(prefix + "suit_point") ]);
		}
	}

	dk = sort_array(keys(unit), 1);
 
	if(!sizeof(dk))  
	{  
	  write(HIG"\n��ʱ�޿ɶһ�����Ʒ������"NOR"\n");	 
	}
	else
	{
		msg ="";
		printf(""HIG"�������%s�һ�������Ʒ:		  ����< �һ���: %s "HIG">	"NOR"\n",this_object()->name(),HIM+me->query("suit_point")+NOR);
		printf(HIC"��"HIY"��������������������������������������������������������������������"HIC"��"NOR"\n");
		for (i = 0; i < sizeof(dk); i++)
		{
			int p;
			p = price[dk[i]];
			if (count[dk[i]] > 0) p = p * 12 / 10;
			msg += sprintf("  %" + sprintf("  %d", (30 + color_len(dk[i]))) +
				  "-s��ÿ%s< %s >�һ���" CYN "(�ֻ�%s)"NOR"\n", dk[i], unit[dk[i]],HIR+chinese_number(p)+NOR,
				  count[dk[i]] > 0 ? chinese_number(count[dk[i]]) + unit[dk[i]]
						: "�����һ�");
		}
		me->start_more(msg);
		printf(HIC"��"HIY"��������������������������������������������������������������������"HIC"��"NOR"\n");
	}   
	return 1;
}	 

int do_huan(string arg)
{
	mapping goods;
	int	amount;
	int	value, val_factor;
	string  ob_file;
	object *obs;
	object  ob;
	string  my_id;
	string  start_room;
	object  room;
	object  me;
	mapping room_obmap;
	int i;
	
	if (! arg)
		return notify_fail("����һ�ʲô��( list�鿴�һ��б� )\n");

	if (sscanf(arg, "%s from %s", arg, my_id) == 2 && ! id(my_id))
		return 0;

	me = this_player();
	if (! query("carried_goods"))
	{
		if (stringp(start_room = query("startroom")) &&
			(room = find_object(start_room)) != environment())
		{
			// I am not in start room.
			message_vision("$N���һ���������ã�����ô�ܵ�������ˣ���\n"
					  "˵��ͷҲ���صļ���ææ�������ˡ�\n", this_object());
			if (! objectp(room) ||
				! mapp(room_obmap = room->query_temp("objects")) ||
				member_array(this_object(), values(room_obmap)) == -1)
			{
				destruct(this_object());
			} else
				this_object()->move(room);
			return 1;
		}
	}

	if (sizeof(filter_array(all_inventory(me), (: ! $1->query("equipped") :))) >= MAX_ITEM_CARRIED)
	{
		write("�����ϵĶ���̫���ˣ��ȴ���һ���ٶһ������ɡ�\n");
		return 1;
	}

	if (sscanf(arg, "%d %s", amount, arg) != 2)
		// not indicate the amount of the goods
		amount = 1;

	if (amount > 100)
	{
		write(CYN + name() + "æ��������������һ�����һ�һ�ټ�����"NOR"\n");
		return 1;
	}

	if (amount <= 0)
	{
		write(CYN + name() + "��е�����������Ҫ�ҵ��һ�����㰡����"NOR"\n");
		return 1;
	}

	// no present or equipped
	ob = present(arg, this_object());
	if (! ob && arg[0] > 160)
	{
		for (i = 0; i < sizeof(obs = all_inventory()); i++)
			if (filter_color(obs[i]->name(1)) == arg)
			{
				ob = obs[i];
				break;
			}
	}

	if (! ob || ob->query("equipped"))
	{
		if ((ob_file = is_vendor_good(arg)) == "")
		{
			write(ob ? "�˼������Ű�����ô��һ���Ʒ���㣿\n"
				: "����һ�ʲô��\n");
			return 1;
		}
		ob = new(ob_file);
		if (amount > 1) ob->set_amount(amount);
		val_factor = 10;
		call_out("destruct_it", 0, ob);
	} else
	{
		if (ob->query_amount())
		{
			object old_ob;
			if (amount > ob->query_amount())
			{
				write("�˼������û����ô���" +
					 ob->name() + "��\n");
				return 1;
			}
			ob = new(base_name(old_ob = ob));
			ob->set_amount(amount);
			ob->set_temp("moved_from", old_ob);
			call_out("destruct_it", 0, ob);
		}
		val_factor = 12;
	}

	if (ob->query("money_id"))
	{
		write(CYN + name() + "��Ц��������������Ҫ�һ�"
			 "Ǯ������˼����"NOR"\n");
		return 1;
	}

	if (query_temp("busy"))
	{
		write(CYN + name() + CYN "���ͷ�������û��������"
			 "����æ��ô����"NOR"\n");
		return 1;
	}

	value = ob->query("suit_point");
	if(me->query("suit_point")-value > 0)
	{
		set_temp("busy", 1);
		if (ob->query("suit_point"))
			message_vision(HIG"$N��$n����һ�����" + ob->short() + ".\n"HIR"������ < �һ���: "+HIM+chinese_number(ob->query("suit_point"))+HIR+" >."NOR"\n",me, this_object());
		else

			message_vision(HIG"$N��$n����һ�����һ" + ob->query("unit") + 
					  ob->query("name") + ".\n"HIR"������ < �һ���: "+HIM+chinese_number(ob->query("suit_point"))+HIR+" >."NOR"\n",me, this_object());
		ob->move(me, 1);
		me->add("suit_point",-value);
		set_temp("busy",0);
	}
	else
	{
		write(CYN + name() + "΢Ц��������Ķһ��㲻�����ж�����װ���鼮���Ը��һ�ȡ<�һ���>��"NOR"\n");
		write(CYN + name() + "΢Ц�������ж��� ��װ �� �鼮 ���Ը��һ�ȡ<�һ���>��"NOR"\n");
		return 1;
	}
		
	return 1;
}