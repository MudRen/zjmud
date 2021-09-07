// cmds/std/auction.c �����뾺�۳���
// call_out() ӳ����ư� for sz	xo2(xkx)
/*
key  string ob_id      ��ƷID
v[0] object obj	       ������Ʒ	    
v[1] int    ob_price   ����۸�		      
v[2] object ob_auction ������		      
v[3] object ob_onwer   ��Ʒ������	      
v[4] string ob_desc    ��Ʒ�����߶Ը���Ʒ�Ľ���
v[5] string auction_id ������ID
v[6] string onwer_id   ����ID
v[7] string ob_name    ��Ʒ����
v[8] string ob_long    ��Ʒ����

mapping	structure:
auction[obj : {ob, ob_price, ob_auction, ob_onwer, ob_desc, auction_id,	...} ]
*/

#include <ansi.h>
inherit	F_DBASE;

#define	PRICE_DIFFERENCE 100

mapping auction = ([]);

// ״̬�仯�Ŀ�������
void auction_chat(string msg);	
void auction_state_check(int times, int	s_times, int last_price, string	obj_id); 
// ��ֹ��״̬�л�
void auction_end(string	ob_name, int ob_price, mixed ob_auction, object	ob_onwer, object ob, string ob_id);
void auction_cancel(string ob_id, object discredit_1, object discredit_2);
// ʵ������
void get_ob_desc(string	desc, object me, string	str, int num);
void choise_secret(string decide, object me, string ob_id, string desc,	int num);
// ���ݷ���
int player_demand(int num, string unit,	object me, string flag);
int player_bank(object ob);
int player_pay(object who, int amount);
int help();
int help_2();

// channeld.c��Ҫ����auctionƵ��
int clean_up(){	return 1;}

void create()
{
	seteuid(ROOT_UID);
	set("name", "����ָ��");
	set("id", "jiaoyi");
	set("channel_id","");
}

void auction_chat(string msg) 
{	
	msg = replace_string(msg, NOR, HIY);	
	CHANNEL_D->do_channel(this_object(),"jiaoyi",msg);
}

void auction_state_check(int times, int	s_times, int last_price, string	obj_id)
{
	int    i, ob_price, flag1 = 0, flag2 = 0;
	object ob, ob_auction, ob_onwer, new_auction, new_onwer, nul;
	mixed  *v;
	string *k, ob_name, ob_id, str;
	
	// ���¶�λ����Ʒ��������Ϊ������Ʒ��������������ű仯
	k = keys(auction);
	i = member_array(obj_id,k); 
	v = values(auction)[i];
	ob_id	   = k[i];
	ob	   = v[0];
	ob_price   = v[1];
	ob_auction = v[2];
	ob_onwer   = v[3];
	ob_name	   = v[7];
	
	if(!objectp(ob_auction)	&& !stringp(ob_auction))
	{
		flag1++;
		if(objectp(new_auction = find_player(v[5])))
		{
			ob_auction = new_auction;
			flag1 =	0;
		}
	}
	if(!objectp(ob_onwer))
	{
		flag2++;
		if(objectp(new_onwer = find_player(v[6])))
		{
			ob_onwer = new_onwer;
			flag2 =	0;
		}
	}

	if(flag2 && !flag1) 
	{
		str="��������ȱϯ��ȡ��"+ob_name+"������";
		auction_chat(str);
		auction_cancel(ob_id, ob_auction, nul);
		return;
	}
	if(!objectp(ob)	|| !objectp(present(ob,ob_onwer)))
	{
		str="�����������ܲ�����������Ʒ"+ob_name+"��ʧ����������ȡ����\n";
		auction_chat(str);
		ob_onwer->delete_temp("auctioning");
		auction_cancel(ob_id, ob_auction, nul);
		return;
	}
	if(times < 120)
	{
		times++;
		if(ob_price > last_price)
		{
			s_times	= 0;
			call_out("auction_state_check",	20, times, s_times, ob_price, ob_id);
		}
		else
		{
			s_times++;
			if(s_times<4)
			{
				str = HIR"��"+CHINESE_D->chinese_number(s_times)+"�κ���:"HIY"����"+ob_name+"���ּ�"+MONEY_D->price_str(ob_price)+"!!";
				auction_chat(str);   
				call_out("auction_state_check",	30, times, s_times, ob_price, ob_id);
			}
			else
			{
				if(flag1 && !flag2)
				{
					str="������ȱϯ��ȡ��"+ob_name+"��������";
					auction_chat(str);
					auction_cancel(ob_id, ob_onwer,	nul);
					return;
				}
				if(flag1 && flag2)
				{
					str="��������˫��ȱϯ��ȡ��"+ob_name+"��������";
					auction_chat(str);
					auction_cancel(ob_id, nul, nul);
					return;
				}	
				auction_end(ob_name, ob_price, ob_auction, ob_onwer, ob, ob_id);
			}
		}
	}
	else
	{
		if(flag1 && !flag2)
		{
			str="������ȱϯ��ȡ��"+ob_name+"��������";
			auction_chat(str);
			auction_cancel(ob_id, ob_onwer,	nul);
			return;
		}
		if(flag1 && flag2)
		{
			str="��������˫��ȱϯ��ȡ��"+ob_name+"��������";
			auction_chat(str);
			auction_cancel(ob_id, nul, nul);
			return;
		}
		str = "ʱ���ѵ�������"+ob_name+"�Ĺ��̵���Ϊֹ��\n";
		auction_chat(str);
		auction_end(ob_name, ob_price, ob_auction, ob_onwer, ob, ob_id);
		return;
	}
	return ;
}

void auction_end(string	ob_name, int ob_price, mixed ob_auction, object	ob_onwer, object ob, string ob_id)
{

	object	*inv, *en_inv, nul;
	string onwer_id, str;

	if(!objectp(ob_onwer))	return;	 // ��Ȼ��̫���ܷ������������ж��±���
	onwer_id = ob_onwer->query_temp("auction/"+ob_id);
	
	if(stringp(ob_auction))
	{
		str=onwer_id+"�Ե׼�"+MONEY_D->price_str(ob_price)+"����"+
		ob_name+"����������Ͷ�꣬����������Ч��\n";		
		auction_cancel(ob_id, ob_onwer,	nul);
		tell_object(ob_onwer,HIR"���ź�����"NOR"���"+ob_name+"����Ͷ�꣬����������Ч��\n");
		ob_onwer->set("auction_fail",ob_onwer->query("mud_age"));
	}
	else
	{
		str=ob_auction->query("name")+"("+ob_auction->query("id")+")"+"����"+MONEY_D->price_str(ob_price)+"����"+
		ob_name+"�ɹ������������ɽ���\n";
			
		// ����˫����Ǯ��Ʒ�Ľ��������轻�ɽ���10%���н��
		if(!player_pay(ob_auction, (int)(ob_price*11/10))) 
		{
			str="����������֧�����ۣ�ȡ��"+ob_name+"��������\n";
			ob_auction->delete_temp("auctioning");
			auction_cancel(ob_id, ob_onwer,	nul);
		}
		else
		{
			inv = all_inventory(ob_auction); 
			en_inv = all_inventory(environment(ob_auction)); 
			tell_object(ob_auction,"��ϲ���㾺��ɹ����õ���"+ob_name+"\n���������10%���н���Ѿ���������\n");
			
			if(!ob->move(ob_auction) || (inv && sizeof(inv)	> 49))
			{
				if(en_inv && sizeof(en_inv) < 49)
				{
					tell_object(ob_auction,	"����ͷ�Ѿ��ò�����,�����䵽����Ľű�..\n");
					ob->move(environment(ob_auction)); 
				}
				else
				{
					tell_object(ob_auction,	"�˴����������������������ܶ��չ���У�\n");
					destruct(ob);
				}
			}	
			tell_object(ob_onwer,ob_name+"�����ɹ������ÿ��Ѿ��Զ�ת�����Ǯׯ�ʻ���\n");
			ob_onwer->add("balance",ob_price);
			auction_cancel(ob_id, ob_auction, ob_onwer);
		}
	}
	auction_chat(str);
	return;
}

void auction_cancel(string ob_id, object discredit_1, object discredit_2)
{
	if(member_array(ob_id, keys(auction)) != -1)
		map_delete(auction, ob_id);

	if(objectp(discredit_1))
		discredit_1->delete("discredit/"+ob_id);
	if(objectp(discredit_2))
		discredit_2->delete("discredit/"+ob_id);
}

int main(object	me,string arg)
{
	int i, j, k, coin, guaranty, num, index, cheat_times, ob_price,value, *check_v;
	mixed *ob_value, *v, *v2;
	string str, unit, *tuned_ch, *ob_key, ob_id, *check_k;
	object ob, obj;
	mapping check;
	
	ob_key = keys(auction);
	ob_value = values(auction);
	check = me->query("discredit");
	cheat_times = sizeof(check);
/*

if(!this_player()->query("canpaimai"))
{
    write("sorry, currently disable by scatter\n");
    return 1;
}
*/
	
	if(!arg)
	{
		tuned_ch = me->query("channels");
		if( !pointerp(tuned_ch)	)
			me->set("channels", ({ "jiaoyi" }) );
		else if( member_array("jiaoyi", tuned_ch) == -1 )
			me->set("channels", tuned_ch + ({ "jiaoyi" }) );
		tell_object(me,"\n��Ľ���Ƶ��(jiaoyi)���ڴ��ڿ�ͨ״̬\n");
		return 1;
	}	
		
	if(arg == "-l")
	{
		if(!sizeof(auction))
		{
			tell_object(me,"Ŀǰû����Ʒ��������\n");
			return 1;
		}
		str=HIG"��ǰ������Ʒ�嵥��\n\n";
		str += sprintf(HIC"��"HIY"����������������������������������������������������������������"HIC"��"NOR"\n");
		str += "  ��Ʒ����		   ��ǰ���		 ��߾�����\n";
		str += HIG" ������������������������������������������������������������������ "NOR"\n";
		
		for(i=0; i<sizeof(auction);i++)
		{
			v = ob_value[i];

			str += sprintf("  %-25s  ", v[7]);
			str += sprintf("%-25s  ", MONEY_D->price_str(v[1]));
			str += sprintf("%-10s  \n", (!stringp(v[2]))? v[5] : "");
		}
		str += "\n\n";
		str += sprintf(HIC"��"HIY"����������������������������������������������������������������"HIC"��"NOR"\n");
		me->start_more(str);
		return 1;
	}
	if(arg == "-i")
	{
		if(!sizeof(auction))
		{
			tell_object(me,"Ŀǰû����Ʒ��������\n");
			return 1;
		}
		str=HIG"��ǰ������Ʒ��ϸ���ܣ�\n"NOR"\n";
		for(i=0; i<sizeof(auction);i++)
		{
			v = ob_value[i];

			str+=HIG"------------"NOR"\n��Ʒ���ƣ� "+v[7]+
			"\n��Ʒ������"+v[8]+
			"\n�������ܣ�"+v[4]+
			"\n������"+v[6]+"\n\n";
		}
		me->start_more(str);		
		return 1;
	}
	if(arg == "-h")
		return help_2();
	if(sscanf(arg,"%s for %d %s",str,num,unit) == 3)
	{
		
		str = lower_case(str);
		if(me->query("age") < 10)
		{
			tell_object(me,"�㻹û�г��꣬�ܶ��Լ���������Ϊ������\n");
			return 1;
		}			
		if(me->query("combat_exp") < 1)
		{
			tell_object(me,"�����ѳ��꣬������������̫�٣��޷����Լ���������Ϊ����\n");
			return 1;
		}


				if(unit != "gold" && unit !="silver")
				{
					write("����ֻ�����Իƽ�(gold)�Ͱ�����silver)����\n");
					return 1;
				}

				if( num < 0 )
				{
					write("�벻Ҫ��Υ������\n");
					return 1;
				}

				if( num > 500 )
				{
					write("���ܳ���������ƽ�\n");
					return 1;
				}



		if(cheat_times && !me->query_temp("auctioning"))
		{
			check_v = values(check);
			check_k = keys(check);
			for(j = 0; j < sizeof(check_v); j++)
			{
				if(me->query("mud_age") - check_v[j] < 3600*cheat_times)	
				{
					tell_object(me,"��������ĳ����������������ֵ���ͣ���ʱ��Ȩ���롣\n");
					return 1;
				}
				else map_delete(check, check_k[j]);			
			}
		}
		if(me->query("mud_age")	- me->query("auction_fail") < 60)
		{
			tell_object(me,"���ϴ���������Ʒ�����ʽ���ػ����Ȼ���ʱ������г��ɡ�\n");
			return 1;		
		}
		if(sizeof(auction) > 4) // ����ͬʱ�����ж����������̿��Բ���
		{
			tell_object(me,"������Ʒ�������������ٺ�\n");
			return 1;
		}
		if(!objectp(ob = present(str,me)))
		{
			tell_object(me,"������û�� "+HIG+str+NOR+" �����Ʒ��\n");
			return 1;
		}
		ob_id = ob->query("id");		
		if(member_array(ob_id, ob_key)!= -1)
		{
			tell_object(me,"������һ����������Ʒ�Ѿ����������ˡ�\n");
			return 1;
		}
		
		if( ob->query("money_id") || ob->is_character() || ob_id == "corpse" || ob_id == "skeleton" || ob_id == "huo ba" || ob_id == "deng long" || ob_id == "la zhu"||ob->query("no_drop"))
		{
			tell_object(me,"�����Ʒ���ܲμ�������\n");
			return 1;
		}
		// �˿�����������10%
		
		value = ob->query("value");
		if (value < 30)
		{
			write(ob->query("name") + "һ�Ĳ�ֵ�����ܲμ�������\n");
			return 1;
		}
		unit = lower_case(unit);
		if(!(num = player_demand(num, unit, me,	"sale"))) return 1;
		guaranty = (int)(num/50);		
		if(!player_pay(me, guaranty)) 
		{
			tell_object(me,"��ȫ������ҲƲ��в����Խ���������֤��(���ʹ����Ʊ�������ȶһ�)\n");
			return 1;
		}		
		write("����Ҫ��������Ʒ��"+ob->query("name")+"�� �׼ۣ�"+MONEY_D->price_str(num)+"\n\n");
		write("��������Ը���Ʒ�Ľ��ܣ�������50���ַ��ڣ�\nֱ�Ӱ��س�(enter)���Ժ��Դ��\n");
		input_to("get_ob_desc",	me, ob_id, num);
		return 1;
	}
	if(sscanf(arg,"%s add %d %s", ob_id,num,unit) == 3)
	{
		
		if(me->query("age") < 10)
		{
			tell_object(me,"�㻹û�г��꣬�ܶ��Լ���������Ϊ������\n");			
			return 1;
		}


		if(unit != "gold")
		{
			write("����ֻ�����Իƽ�(gold)�м�\n");
			return 1;
		}
		if( num < 0 )
		{
			write("�벻Ҫ��Υ������\n");
			return 1;
		}

		if( num > 5 )
		{
			write("��������һ�����������ƽ��Ա��ⲻ��Ҫ���������\n");
			return 1;
		}

		if(me->query("combat_exp") < 1)
		{
			tell_object(me,"�����ѳ��꣬������������̫�٣��޷����Լ���������Ϊ����\n");
			return 1;
		}
		if(cheat_times && !me->query_temp("auctioning"))
		{
			check_v = values(check);
			check_k = keys(check);
			for(j = 0; j < sizeof(check_v); j++)
			{
				if(me->query("mud_age") - check_v[j] < 3600*cheat_times)	
				{
					tell_object(me,"��������ĳ����������������ֵ���ͣ���ʱ��Ȩ���롣\n");
					return 1;
				}
				else map_delete(check, check_k[j]);			
			}
		}
		if((index = member_array(ob_id, ob_key)) == -1)
		{
			for(k = 0; k < sizeof(auction); k++)
			{
				if (strsrch(ob_key[k], ob_id) == -1)
					continue;
				index = k;
			}
			if (index < 0)
			{
				tell_object(me,"Ŀǰ������������û�������Ʒ��\n\nָ�auction <��ƷID> add <���ֵ> <���ҵ�λ>\n����auction -lָ���ѯ��ǰ����Ʒ���������\n");
				return 1;
			}
		}

		v2 = ob_value[index];
		obj = v2[0];
		ob_price = v2[1];
		ob_id = ob_key[index];
		
		if(objectp(obj)	&& v2[3]	== me)
		{
			tell_object(me,"�������Լ���������Ʒ���밵���м۲��ɣ�\n");
			return 1;
		}
		coin = player_bank(me);
		unit = lower_case(unit);
		if(!(num = player_demand(num, unit, me,	"add"))) return	1;
		
		if ( intp (me->query("paimai/bathtime")) )
		if (uptime() < me->query("paimai/bathtime") + 5 )
			return notify_fail("���Ͷ�ı���Ͷ����ʲô�������ء�\n");

		if((int)((num + ob_price)*11/10 > this_player()->query("balance")))
		{
			tell_object(me,"Ǯׯ��û���㹻�Ĵ��������������Ʒ����Ԥ�Ƽۺ�10%�н�ѣ���\n");
			return 1;
		}


		me->set("discredit/"+ob_id,me->query("mud_age"));
		me->set_temp("auctioning",1);
		v2[1] = num + ob_price;
		v2[2] = me;
		v2[5] = me->query("id");
		str = me->query("name")+"("+me->query("id")+")Ͷ��"+v2[7]+"�����ۣ�"+MONEY_D->price_str(v2[1])+"!\n";
		auction_chat(str);
		me->set("paimai/bathtime",uptime() );
		return 1;
	}
	else return help();
}

void get_ob_desc(string	desc, object me, string	str, int num)
{
	write("\n");
	if (strlen(desc) > 60)
	{
		write("������Ʒ�Ľ���̫���ˣ���ע���Լ����ࡣ\n");
		input_to("get_ob_desc",	me, str, num);
		return ;
	}
	write("��Ϊ���������Ƿ�Ը��������������͸¶�Լ�������(y/n)\n");
	input_to("choise_secret", me, str, desc, num);	
	return;
}

void choise_secret(string yn, object me, string	ob_id, string desc, int	num)
{
	mixed *values;
	string ob_name,	onwer_id, str;
	object ob;

	if (yn[0] != 'y' && yn[0] != 'Y')
		me->set_temp("auction/"+ob_id, "ĳ��");
	else 
		me->set_temp("auction/"+ob_id, me->query("name")+"("+me->query("id")+")");
	if(!objectp(ob = present(ob_id,	me)))
	{
		tell_object(me,"�������Ѿ�û����������ˣ����ܲμ�������\n");
		return;
	}		
	if(sizeof(auction) && member_array(ob_id,keys(auction))!= -1)
	{
		tell_object(me,"������һ����������Ʒ�Ѿ��������������ˡ�\n");
		return;
	}
	onwer_id = me->query_temp("auction/"+ob_id);
	ob_name	= ob->query("name")+"("+ob_id+")";

	// ���������������ԣ��ж�Υ��������������
	me->set("discredit/"+ob_id, me->query("mud_age"));
	me->set_temp("auctioning", 1);
	
	values = ({ob, num, "",	me , desc, "", onwer_id, ob_name, ob->long()});
	auction[ob_id] = values;
	str = me->name()+"("+me->query("id")+")�����������̡�";
	CHANNEL_D->do_channel(this_object(),"sys",str);
	str = onwer_id+"���ڿ�ʼ����"+ob_name+"���׼ۣ�"+MONEY_D->price_str(num)+"��\n";
	auction_chat(str);
	call_out("auction_state_check",	30, 0, 0, num,ob_id);
	return;
}

int player_demand(int num, string unit,	object me, string flag)
{
	switch(unit)
	{
		case "coin":break;
		case "silver":num*=100;break;
		case "gold":num*=10000;break;
		case "cash":
		case "thousand-cash":
			tell_object(me,"���������в���ʹ����Ʊ��������Ǯׯ�һ���Ӳͨ����\n");
			return 0;
		default:
			tell_object(me,"�Ƿ��Ļ��ҵ�λ��\nvalid	unit: coin, silver, gold\n");
			return 0;
	}
	if (num	< 1000 && flag == "add")
	{
		tell_object(me,"�������򣺲����ʮ������Ϊ���ߡ�\n");
		return 0;
	}
	if (num	< 1000 && flag == "sale")
	{
		tell_object(me,"�Բ��𣬱��в�֧���޵׼�������10�������ǳ��۵��ߡ�\n");
		return 0;
	}
	return num;
}

int player_bank(object ob)
{
	object g_ob;
	object c_ob;
	object s_ob;
	int total;

	total =	ob->query("balance");

	g_ob = present("gold_money", ob);
	c_ob = present("coin_money", ob);
	s_ob = present("silver_money", ob);

	if (g_ob) total	+= g_ob->query_amount()	* 10000;
	if (s_ob) total	+= s_ob->query_amount()	* 100;
	if (c_ob)   total += c_ob->query_amount();
	return total;
}

int player_pay(object who, int amount)
{
	object g_ob, s_ob, c_ob;
	int gc,	sc, cc,	left, total;

	seteuid(getuid());

	if (g_ob = present("gold_money", who))
		gc = g_ob->query_amount();
	else
		gc = 0;
	if (s_ob = present("silver_money", who))
		sc = s_ob->query_amount();
	else
		sc = 0;
	if (c_ob = present("coin_money", who))
		cc = c_ob->query_amount();
	else
		cc = 0;
	total =	cc + sc	* 100 +	gc * 10000;
	
	if ( total < amount )
	{
		if((amount-total) > who->query("balance"))
			return 0;
		if(objectp(c_ob)) destruct(c_ob);
		if(objectp(s_ob)) destruct(s_ob);
		if(objectp(g_ob)) destruct(g_ob);		
		who->add("balance",-(amount-total)); 
			tell_object(who,"�����ϵ���Ǯ���������������ֱ�Ӵ�Ǯׯ�ʻ��Ͽ۳���\n\n");
		return 1;
	}
	else 
	{
		left = total - amount;
		gc = left / 10000;
		left = left % 10000;
		sc = left / 100;
		cc = left % 100;

		if (g_ob)
			g_ob->set_amount(gc);
		else sc	+= (gc * 100);
		if (s_ob)
			s_ob->set_amount(sc);
		else if	(sc) {
			s_ob = new(SILVER_OB);
			s_ob->set_amount(sc);
			s_ob->move(who);
		}
		if (c_ob)
			c_ob->set_amount(cc);
		else if	(cc) {
			c_ob = new(COIN_OB);
			c_ob->set_amount(cc);
			c_ob->move(who);
		}
		return 1;
	}
}

int help()
{
    write(@HELP�����ʽ��
 
    �鿴Ŀǰ���ھ���״̬����Ʒ�嵥��paimai -l
    �鿴Ŀǰ���ھ���״̬����Ʒ���ܣ�paimai -i    
    ������Ʒ��paimai <��ƷID> for <�׼�ֵ> <���ҵ�λ>
    ������Ʒ��paimai <��ƷID> add <�Ӽ�ֵ> <���ҵ�λ> 
    
    �鿴��ϸ����������paimai -h
    
HELP
    );
    return 1;
}

int help_2()
{    
    write(@HELP��������˵���ĵ���  

    1. �����18���Ժ�������ֵ�ﵽ1000�㼴��Ȩ������������  
    
    2. ������������Ʊ��Ч������ȥǮׯ�һ���Ӳͨ������ƽ𡢰�����ͭǮ��
    
    3. ������������Ʒʱ������������ʽ��ʼ�������׼۲�������10������������ʱ��ҿ���
       ������1����������100��ͭǮ������Ͳ��ֵ�μӾ��ģ����һ��ʱ��������Ͷ�꣬��
       ���к��ۣ����κ��ۺ���Ȼ���˳��ۣ���������ֹ������һֱ����Ͷ�꣬���˹涨ʱ�䣬
       �˴�������Իᱻ��ֹ���������������5����Ʒͬʱ������
       
    4. �������ֹ����������Ϊʤ������������ֱ߼�Ǯׯ��ȡ����Ʒֱ��ת�Ƶ�����
       ���ϣ������������������������ڷ���֮�У��������Ҳ�޷�װ�£���Ʒ��û�մ���
       �мǣ��������ÿ��ֱ��ת����Ǯׯ�ʻ���������ʼʱ��������ȡ�׼�2%�������ѡ���
       ������������ʼ������Ͷ�꣬������������ʧ�ܣ�������ˡ���˻������������ɹ�����
       ���谴�ɽ��۽���10%���н�ѡ�
       
    5. ���������У�������Ϊ����Υ����������������˫�����κ�һ���뿪��Ϸ��������
       �����жϣ���Ʒ�뿪���������ˣ���������ʱ�����������ɽ��ۡ������������֮һ��
       ���η������Ȼή�ͣ��ͷ���һСʱ�ڲ��òμ��κ��������йصĻ������ڽ�ֹ��
       ����ʱ�����ٴ�Υ�棬���ֹʱ����Υ������ۼӡ�����������Ʒ���κ���֮����Ϊ��
       �˾����ȡ����������һ�����ڲ���������������Ʒ��
    
       Shure
       2001.8.
HELP
    );
    return 1;
}  
