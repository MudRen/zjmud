#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

#define MAX_OBS    100
#define TAX	10

void create()
{
	mapping data;
	
	seteuid(ROOT_UID);
	restore();
	data = query_entire_dbase();
	if( !mapp(data) || undefinedp(data["data"]) ) 
	{
		set("data", ([]));
		save();
	}
	set_heart_beat(10);
}

void remove()
{
	save();
}

public void mud_shutdown()
{
	save();
}

public string query_save_file() { return DATA_DIR "saled"; }

public string do_stock(object me, string arg)
{
	object *inv,gold,ob, obj;
	int i,n, value,now;
	string short_name, file, *dk, *text, id, key, str, db,money,type;
	mapping data;
	
	id = me->query("name");		
	if( !arg )
	{
		inv = all_inventory(me);
		if (! sizeof(inv))
		{
			return (ZJOBLONG+HIY"Ŀǰ������û���κζ����ɼ��ۡ�"NOR);
		}
		dk = ({});
		for (i = 0; i < sizeof(inv); i++)
		{
			if (inv[i]->query("equipped")||inv[i]->query("no_drop")||inv[i]->query("no_give")||inv[i]->query("money_id")) continue;

			short_name = inv[i]->query("name");
			if(inv[i]->query_amount())
				short_name = inv[i]->query_amount() + inv[i]->query("base_unit") + short_name;

			dk += ({ short_name + ":jishou " + file_name(inv[i]) });
		}
		text = sort_array(dk, 1);

		str = ZJOBLONG"��ѡ��������۵���Ʒ��\n";
		str += ZJOBACTS2+ZJMENUF(2,2,10,32);
		if (! sizeof(text))
		{
			return (ZJOBLONG+HIY"Ŀǰ������û���Լ��۵Ķ�����"NOR);
		}
		str += implode(text, ZJSEP);
		return str;
	}

	if(objectp(ob = present(arg,me)))
	{
		return ZJOBLONG"����۳��ɹ����г�����ȡ��һ�������ѡ�"ZJBR"����ѡ�����"+ob->query("name")+"������:\n"ZJOBACTS2+ZJMENUF(3,3,10,30)+"��Ҽ���:jishou "+arg+" value ���"ZJSEP"Ԫ������:jishou "+arg+" value Ԫ��";
	}

	if( sscanf(arg, "%s value %s", file,money) == 2 )
	{
		if(!objectp(ob = present(file,me)))
			return "�����ϲ�û�������Ʒ����";
		
		if( sscanf(money, "%s %d", money,value) != 2 )
		{
			if( money!="���"&&money!="Ԫ��" )
				return "ֻ�ܱ��Ϊ��һ�Ԫ����";

			return INPUTTXT("�����"+ob->query("name")+"�Զ���"+money+"���ۣ�","jishou "+arg+" $txt#");
		}
	}
	else
		return "������������ȷ����������";

	if( !value || value < 0 )
		return "�۸��ע���󣡣���";

	if( value < 2 )
		return "���ٱ��Ϊ2 ������";

	if( value > 9999 )
		return "�����9999��";

	if( !objectp(ob=present(file,me)))
		return "�����ϲ�û�������Ʒ����";

	if( ob->query("no_sell")&&!ob->query("yuanbao"))
		return "�������̫��ҡ�ˣ����Ǳ��ó���������";

	if( ob->query("no_give"))
		return "�������̫��ҡ�ˣ����Ǳ��ó���������";

	if( ob->query("owner")&&ob->query("owner")!=0)
		return "����Ʒ���޷�������";

	if( ob->query("unique") )
		return "����޼۱������Ǳ������ó��������ɡ�";

	if( strsrch(file, "#") == -1 )
		return "�Բ��𣬸���Ʒ�����Լ��ۣ�";

	if( ob->is_character() ) 
		return "�㲻�ܷ������";

	key = "data/" + id;
	if( sizeof(query(key)) >= MAX_OBS )
		return "�Բ����㲻���ټ��۸���Ķ����ˡ�";

	if( !MONEY_D->player_pay(me,10000) ) 
		return "������Ʒ��Ҫһ��"HIY"�ƽ�"NOR"�йܷѡ�";

	db = save_variable(ob->query_entire_dbase()); 

	if(ob->query("weapon_prop"))
		type="����";
	else if(ob->query("armor_prop"))
		type="����";
	else
		type="�ӻ�";

	data = ([
		"file" : file,
		"name" : ob->query("name"),
		"id" : ob->parse_command_id_list(),
		"num" : ob->query_amount()?ob->query_amount():1,
		"seller" : me->query("id"),
		"type" : type,
		"value" : value,
		"money" : money,
		"dbase" : db,
	]);
	now = time();
	set(key + "-"+now, data);
	log_file("saled/jishou",sprintf("%s��%s(%s)��%d%s����%s",ctime(time()),me->query("name"),me->query("id"),value,money,ob->short()));
	destruct(ob);
	
	if( objectp(ob) ) {		
		delete(key + "-"+ now);
		me->save();
		save();
		log_file("saled/jishou","ʧ�ܡ�\n");
		return "���󣡼���ʧ�ܣ�����ϵ����Ա��";
	} else {
		me->save();
		save();  
		log_file("saled/jishou","�ɹ���\n");
		return data["name"] + "�Ѿ����ۺ��ˣ�";
	}
}

public string do_unstock(object me, string arg)
{
	string kid,*ks,id;
	string file="";
	object ob;
	mapping data;
	int i,flag=0;

	id = me->query("name");

	if( !arg || arg == "" )
		return "ָ���ʽ��unstock <��Ʒ���>";

	arg = lower_case(arg);

	if( !(data=query("data/"+arg)) )
		return "��Ҫȡ��ʲô������?";
	
	ks = explode(arg,"-");

	if( ks[0]!=id )
		return "��Ҫȡ��ʲô������?";

	if( data["seller"]!=me->query("id") )
		return "��Ҫȡ��ʲô������?";

	file = data["file"];
	if(!objectp(ob=find_object(file)))
	{
		sscanf(file, "%s#%*s", file);
		ob = new(file);
		if( data["dbase"] ) {
			ob->set_name(data["name"],data["id"]);
			ob->set_dbase(restore_variable(data["dbase"]));
		}
	}
	if(objectp(ob))
	{
		delete("data/"+arg);
		log_file("saled/quhui",sprintf("%s��%s(%s)ȡ�ؼ����е�%s��\n",ctime(time()),me->query("name"),me->query("id"),ob->short()));
		ob->move(me);				
		me->save();
		save();
		me->start_busy(1);			
		return "��Ʒȡ�سɹ� ��";
	}
	return "û���������";
}

public string do_cha(object me, string arg)
{
	string str,kid,*ks,id;
	string file="";
	object ob;
	mapping data;
	int i,flag=0;

	id = me->query("name");

	if( !arg || arg == "" )
		return "ָ���ʽ��chakan <��Ʒ���>";

	arg = lower_case(arg);

	if( !(data=query("data/"+arg)) )
		return "��Ҫ�鿴ʲô����?";
	
	file = data["file"];
	if(!objectp(ob=find_object(file)))
	{
		sscanf(file, "%s#%*s", file);
		ob = new(file);
		if( data["dbase"] ) {
			ob->set_name(data["name"],data["id"]);
			ob->set_dbase(restore_variable(data["dbase"]));
			set("data/"+arg+"/file",file_name(ob));
			save();
		}
	}
	if(objectp(ob))
	{
		"/cmds/std/look"->look_item(me,ob);
		if(data["seller"]==me->query("id"))
			str = ZJOBACTS"����:quhui "+arg;
		else
			str = ZJOBACTS"����:jybuy "+arg;
		return str;
	}
	return "û���������";
}

void heart_beat()
{
	string file,owner,*user,name;
	mapping data,om;
	int stime, i;
	object sob,obj,ob;

	data = query("data");
	if( !mapp(data) ) 
		return;
	user = keys(data);

	for( i = 0; i < sizeof(user); i++ )
	{
		if( mapp(om = data[user[i]]))
		{
			sscanf(user[i],"%s-%d",owner,stime);
			if((time()-stime)>86400)
			{
				if(!(obj=find_player(om["seller"])))
				{
					continue;
				}
				else
				{
					file = om["file"];
					if(!objectp(ob=find_object(file)))
					{
						sscanf(file, "%s#%*s", file);
						ob = new(file);
						if( om["dbase"] ) {
							ob->set_name(om["name"],om["id"]);
							ob->set_dbase(restore_variable(om["dbase"]));
						}
					}
					log_file("saled/time_over",sprintf("%s��%s(%s)���۵�%s��ʱ����������\n",ctime(time()),obj->query("name"),obj->query("id"),ob->short()));
					ob->move(obj);
					obj->save();
					tell_object(obj,HIM"���ں��м��۵�"+ob->query("name")+"����24Сʱ���˹����ѷ��ر�����"NOR"\n");
					delete("data/"+user[i]);
					save();
				}
			}
		}
	}
}

public string do_list(object me, string arg)
{
	string *owner, *msg, *user,type,name;
	string file;
	mapping data, m, om;
	int i,j,ye,yeall;
	string str,id;

	data = query("data");
	if( !mapp(data) ) 
		return "Ŀǰ��û�г����κλ��";
		
	msg = ({});
	user = keys(data);

	if( sscanf(arg, "%s %s %d",type,name,ye)!=3)
		if( sscanf(arg, "%s %d",type, ye)!=2)
			return "��Ҫ�鿴ʲô��";

	for( i = 0; i < sizeof(user); i++ ) {
		if( mapp(om = data[user[i]])) {
			owner = explode(user[i],"-");
			if((time()-atoi(owner[1]))>86400) continue;
			if(type=="ȫ��"||type==om["type"]||(type=="����"&&strsrch(om["name"], name) != -1)||(type=="mine"&&owner[0]==me->query("name")))
					msg+=({sprintf(" %s[%d]"+ZJBR+WHT" �۸�%d%s"NOR":jychakan %s",om["name"],om["num"],om["value"],om["money"],user[i])});
		}
	}

	if(msg==({}))
		return "û����Ҫ�ҵĻ��";

	str = ZJOBLONG+sprintf("�����еġ�%s���͡�����Ʒ��(%d��)��\n",type,sizeof(msg));

	str += ZJOBACTS2+ZJMENUF(2,2,8,30);

	yeall = sizeof(msg)/10;
	if(sizeof(msg)%10) yeall += 1;
	if(ye<1) ye = 1;
	if(ye>yeall) ye = yeall;
	j = (ye-1)*10;
	i = ye*10;
	if (i >= sizeof(msg)) i = sizeof(msg);
	i--;
	if(yeall>1)
		str += "��һҳ:jylist "+type+" "+(ye-1)+ZJSEP"��һҳ:jylist "+type+" "+(ye+1)+ZJSEP;
	str += implode(msg[j..i], ZJSEP);

	return str+"\n";
}       

public string do_buy(object me, string arg)
{
	string username,pay_type,*ks, id;
	string file;
	object sob,ob,obj,owner;
	mapping data;
	int value, money, fees;
	int i;
		
	if( me->is_busy() )
		return "����æ���أ�";

	if( !arg )
		return "��Ҫ��ʲô������";
	arg = lower_case(arg);

	if( !(data=query("data/"+arg)) )
		return "��Ҫ��ʲô������";
	
	ks = explode(arg,"-");

	pay_type = data["money"];
	value = data["value"];
	fees = value - value * TAX / 100;
	if(fees<1) fees = 1;
	if(pay_type=="Ԫ��")
	{
		money = me->query("yuanbao");
		if( money < value )
			return "��û��ô��Ԫ����";
	}
	else if(pay_type=="���")
	{
		if( !MONEY_D->player_pay(me,value*10000) )
			return "��û��ô���ֽ�ͺ���Ʊ��";
	}
	
	file = data["file"];
	if(!objectp(ob=find_object(file)))
	{
		sscanf(file, "%s#%*s", file);
		ob = new(file);
		if( data["dbase"] ) {
			ob->set_name(data["name"],data["id"]);
			ob->set_dbase(restore_variable(data["dbase"]));
		}
	}
	if(objectp(ob))
	{
		if(pay_type=="Ԫ��")
			me->add("yuanbao",-value);
		ob->move(me,1);				
		delete("data/"+arg);
		save();
		me->start_busy(1);

		if(!(obj=find_player(data["seller"])))
		{
			sob = new(LOGIN_OB);
			sob->set("id",data["seller"]);
			sob->set("body", USER_OB);
			obj = LOGIN_D->make_body(sob);
			destruct(sob);
			if(obj->restore())
			{
				obj->setup();
				if(pay_type=="Ԫ��")
					obj->add("yuanbao",value*(100-TAX)/100);
				else
					obj->add("balance",value*100*(100-TAX));
				obj->save();
				log_file("saled/buy",sprintf("%s��%s(%s)��%d%s����%s(%s)��%s��\n",ctime(time()),me->query("name"),me->query("id"),value,pay_type,obj->query("name"),obj->query("id"),ob->short()));
				destruct(obj);
			}
		}
		else
		{
			if(pay_type=="Ԫ��")
				obj->add("yuanbao",value*(100-TAX)/100);
			else
				obj->add("balance",value*100*(100-TAX));
			obj->save();
			log_file("saled/buy",sprintf("%s��%s(%s)��%d%s����%s(%s)��%s��\n",ctime(time()),me->query("name"),me->query("id"),value,pay_type,obj->query("name"),obj->query("id"),ob->short()));
			tell_object(obj,HIM"���ں��м��۵�"+ob->query("name")+"�ѳɹ��۳�������"+(value*(100-TAX)/100)+pay_type+"��"NOR"\n");
		}
		me->save();
		return "����ɹ� ��";
	}
	return "û���������";
}

