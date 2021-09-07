#include <ansi.h>

inherit NPC;

string ask_lilian();
string ask_jieshu();
string ask_baotu();
string ask_pay();
int ask_job();
string ask_yao();
int ask_gift1();
int ask_gift();
int ask_xflb();

void create()
{
	set_name(HIW"����ʹ��"NOR, ( { "shizhe" }));
	set("nickname", HBCYN"����ʹ��"NOR);
	set("long", "����һλ���ص�ʹ�ߣ���������һ������顣\n");
	set("gender", "����");
	set("age", 30);
	set("per", 24);
	set("str", 40);
	set("int", 40);
	set("con", 40);
	set("dex", 40);
	set("qi",5000);
	set("jingli",6000);
	set("max_qi", 8000);
	set("max_jing", 5000);
	set("eff_jingli", 6000);
	set("jiali", 190);
	set("combat_exp", 9000000);
	set("shen", 25000);

	set("action_list",([
//		"���ֶһ�":"ljshop",
	]));

	set("inquiry", ([
		"�������" : (: ask_gift1 :),
//		"��������" : (: ask_gift :),
//		"˫���±�": (: ask_job :),
		"����" : (: ask_lilian :),
		"����" : (: ask_jieshu :),
		"���ĵ�" : (: ask_yao :),
		"�ر�ͼ" : (: ask_baotu :),
		"�������" : (: ask_xflb :),
	]));
	setup();
}

int ask_job()
{
	object ob,me = this_player();
	object xique;

	ob = present("shuang huang",me);
	if (!ob)
	{
		command("say ����쵽�ˣ��Ҹ�����׼����˫���±������ˣ�������еĻ��Ͻ����Ұɣ��һ���㽱��Ŷ��");
		return 1;
	}

	command("nod "+me->query("id"));
	command("say ����лл���ˣ�ף������ڿ��֣�");
	tell_object(me,HIY"���������������"+ob->query_amount()+NOR"��\n");
	me->add("zhongqiu/pot",ob->query_amount());
	destruct(ob);

	return 1;
}

void init()
{
	object ob;
	::init();//�̳���һ��
	if (interactive(ob = this_player()) && !is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}
	add_action("ljshop","ljshop");
}

void greeting(object ob)
{
	if( !ob || environment(ob) != environment() ) return;
	if( ob->query("zjvip/times") > 0 && !ob->query("lilian/start"))
	{
		command("hi "+ob->query("id"));
		command("whisper "+ob->query("id")+" "HIC"\n��λ" + RANK_D->query_respect(ob) +"�������Ƕ���һ��ĳ�Ա��\n"+
		        "�㻹û����������"HIC""ZJURL("cmds:ask shizhe about ����")+ZJSIZE(20)"�Ǽ�"NOR""HIR"����"HIC"��\n"+
		        "�Ͻ���ʼ���"HIR"����"HIC"����ȡ���ļ��影���ɣ�"NOR"");
	}

}

int ljshop(string arg)
{
	string *list,str,file,price;
	int amount,i,yuanbao,value;
	object me,ob;
	mapping goods;

	me = this_player();
	goods = ([
	             "/clone/shizhe/putao":70,
	             "/clone/shizhe/dan_chongmai1":30,
	         ]);
	list = keys(goods);
	if (! arg)
	{
		str = ZJOBLONG"��Ŀǰ��"+me->query("zhongqiu/pot")+"������֣���ѡ������һ��ĵ��ߣ�\n"ZJOBACTS2+ZJMENUF(4,4,8,32);
		for(i=0; i<sizeof(list); i++)
		{
			file = list[i];
			if(!goods[file]||file_size(file+".c")<0) continue;
			yuanbao = goods[file];
			price = yuanbao+"����";
			str += sprintf("%s"ZJBR"%s:ljshop look %s"ZJSEP,file->query("name"),price,file);
		}
		tell_object(me,str+"\n");
		return 1;
	}
	else if (sscanf(arg,"look %s",file)==1)
	{
		if(file_size(file+".c")<0||!goods[file])
			return notify_fail(HIM"�һ��б���û��������ߣ���"NOR"\n");

		yuanbao = goods[file];
		price = yuanbao+"����";
		str = ZJOBLONG+"��"+file->query("name")+"�������۸�"+price+NOR+ZJBR"һһһһһһһһһһһһһһһһһһһһһһһ"ZJBR;
		str += file->long();
		str += ZJOBACTS2+ZJMENUF(4,4,10,28);
		str += "�һ�:ljshop buy "+file+"\n";
		tell_object(me,str+"\n");
		return 1;
	}
	else if (sscanf(arg,"buy %s",file)==1)
	{
		if (sscanf(file, "%d %s", amount, file) != 2)
		{
			if(file_size(file+".c")<0||!goods[file])
				return notify_fail(HIM"�һ��б���û��������ߣ���"NOR"\n");

			write(INPUTTXT("����һ����ٸ�"+file->query("name")+"��"ZJBR"��ȷ����ı����ռ��㹻��","ljshop buy $txt# "+file)+"\n");
			return 1;
		}

		if(file_size(file+".c")<0||!goods[file])
			return notify_fail(HIM"�һ��б���û��������ߣ���"NOR"\n");

		if(!file->query_amount())
			amount = 1;
		yuanbao = goods[file];

		if(amount<1 || amount>300)
			return notify_fail(HIM"���ܶһ���ô�࣡��"NOR"\n");
		if(me->query("zhongqiu/pot") < yuanbao*amount)
			return notify_fail(HIM"��Ķһ����ֲ��㣬��μӲμ������ѣ���"NOR"\n");
		me->add("zhongqiu/pot",-yuanbao*amount);
		ob = new(file);
		if(ob->query_amount())
			ob->set_amount(amount);
		log_ufile(me,"pay/zhongqiu", "�һ���"+ob->short()+"��\n");
		tell_object(me,"��ɹ��һ�����"+ob->short()+"��"NOR"\n");
		ob->move(me);
		return 1;
	}
	else
		return notify_fail(HIM"�����ʲô����"NOR"\n");

	return 1;
}

int ask_gift1()
{
	object me = this_player();

	GIFT_D->check_gift(me);
	return 1;
}

int ask_xflb()
{
	object ob = this_player();
	object gift;
	int num,money;

	if (ob->query("zjvip/kaihuang_gift"))
	{
		tell_object(ob,"���Ѿ���ȡ����Ա����ˣ������ظ���ȡ��\n");
		return 1;
	}
/*
	if (ob->query("zjvip/times") <1)
	{
		tell_object(ob,"�Բ���ֻ�л�Ա������ȡ��Ա�����\n");
		return 1;
	}
*/
	command("nod "+ob->query("id"));
	command("say ����ͷ����㡣");
	gift = new("/clone/gift/xflb");
	tell_object(ob,HIM"������"+gift->short()+"��"NOR"\n");
	ob->set("zjvip/kaihuang_gift",1);
	log_file("buchang", sprintf("%s��%s(%s)��ȡ��%s��\n",ctime(time()),ob->query("name"),ob->query("id"),gift->short()));

	gift->move(ob);
	return 1;
}

int ask_gift()
{
	object ob = this_player();
	object gift;
	int num,money;
	mixed *today;

	today = localtime(time());
	if(wizardp(ob)||((today[4]+1)==10 && today[3]>=1 && today[3]<=10))
	{
		money=VIP_D->query_gift_payrec("�����/"+ob->query("id"));
		tell_object(ob,"��Ŀǰ����ڳ�ֵ�ۼ�Ϊ"+money+"��\n");

		if(ob->query("guoqing/diaolong"))
			tell_object(ob,HIM"���Ѿ���ȡ������������(��Ѫ+200)���ˡ�"NOR"\n");
		else if(ob->query("shimen/today")>=1000&&!ob->query("guoqing/diaolong"))
		{
			gift = new("/clone/suit/huodong/diaolong");
			tell_object(ob,HIM"������"+gift->short()+"��"NOR"\n");
			log_file("guoqing", sprintf("%s��%s(%s)��ȡ��%s��\n",ctime(time()),ob->query("name"),ob->query("id"),gift->short()));
			gift->move(ob);
			ob->set("guoqing/diaolong",1);
		}
		else
			tell_object(ob,HIM"�㻹δ�ﵽ��ȡ����������(��Ѫ+200)��������(�����ڼ�ʦ�ų���1000��)��"NOR"\n");

		if(ob->query("guoqing/manao"))
			tell_object(ob,HIM"���Ѿ���ȡ����Ѫ�������(��Ѫ+500)���ˡ�"NOR"\n");
		else if(money>=500&&!ob->query("guoqing/manao"))
		{
			gift = new("/clone/suit/huodong/manao");
			tell_object(ob,HIM"������"+gift->short()+"��"NOR"\n");
			log_file("guoqing", sprintf("%s��%s(%s)��ȡ��%s��\n",ctime(time()),ob->query("name"),ob->query("id"),gift->short()));
			gift->move(ob);
			ob->set("guoqing/manao",1);
		}
		else
			tell_object(ob,HIM"�㻹δ�ﵽ��ȡ��Ѫ�������(��Ѫ+500)��������(�����ڼ��ֵ����500)��"NOR"\n");

		if(ob->query("guoqing/feicui"))
			tell_object(ob,HIM"���Ѿ���ȡ�����δ�������(��Ѫ+1000)���ˡ�"NOR"\n");
		else if(money>=1000&&!ob->query("guoqing/feicui"))
		{
			gift = new("/clone/suit/huodong/feicui");
			tell_object(ob,HIM"������"+gift->short()+"��"NOR"\n");
			log_file("guoqing", sprintf("%s��%s(%s)��ȡ��%s��\n",ctime(time()),ob->query("name"),ob->query("id"),gift->short()));
			gift->move(ob);
			ob->set("guoqing/feicui",1);
		}
		else
			tell_object(ob,HIM"�㻹δ�ﵽ��ȡ���δ�������(��Ѫ+1000)��������(�����ڼ��ֵ����1000)��"NOR"\n");

		if(ob->query("guoqing/jiulong"))
			tell_object(ob,HIM"���Ѿ���ȡ�������������(��Ѫ+1500,�ڹ�����+50)���ˡ�"NOR"\n");
		else if(money>=1500&&!ob->query("guoqing/jiulong"))
		{
			gift = new("/clone/suit/huodong/jiulong");
			tell_object(ob,HIM"������"+gift->short()+"��"NOR"\n");
			log_file("guoqing", sprintf("%s��%s(%s)��ȡ��%s��\n",ctime(time()),ob->query("name"),ob->query("id"),gift->short()));
			gift->move(ob);
			ob->set("guoqing/jiulong",1);
		}
		else
			tell_object(ob,HIM"�㻹δ�ﵽ��ȡ�����������(��Ѫ+1500,�ڹ�����+50)��������(�����ڼ��ֵ����1500)��"NOR"\n");
	}

	return 1;
}

string ask_lilian()
{
	object me = this_object();
	object ob = this_player();

	if (ob->query("vip/all_pay")>0)
	{
		ob->add("zjvip/all_pay",ob->query("vip/all_pay"));
		ob->delete("vip/all_pay");
	}

	if (ob->query("zjvip/times") <1) return "�Բ�����ֻ���������˵����飡\n";

	if (ob->query("lilian/start")) return "���Ѿ���¼�����������Ϣ������ȥ�ɡ�\n";

	message_vision(HIG"$N�������²�����$n���˵�ͷ��˵�����ðɣ������Ϊ����ϡ�"NOR"\n",me,ob);

	ob->set("lilian/start",time());

	return "������������ʱ�������ҽ���������\n";
}

string ask_jieshu()
{
	object me = this_object();
	object ob = this_player();
	int time3, paid,exp,gold;

	time3=time()-(int)ob->query("lilian/start");

	if (ob->query("zjvip/times") <1) return "�Բ�����ֻ���������˵����飡\n";

	if (!ob->query("lilian/start")) return "������û�����������¼��\n";

	paid=ob->query("zjvip/all_pay");

	tell_object(ob,HIC"����ۼ�����ʱ����"+CHINESE_D->chinese_time(time3)+"��"NOR"\n");

	if (time3>43200) time3=43200;

	tell_object(ob,HIC"�����Ч����ʱ����"+CHINESE_D->chinese_time(time3)+"��"NOR"\n");
	message_vision(HIY"$N������$n�ı���������"NOR"\n",me,ob);
	ob->add("balance",time3*2);
	ob->add("combat_exp",time3/4);
	ob->add("potential",time3/28);
	ob->delete("lilian/start");
	tell_object(ob,"�㱻������\n"
	            "������"+time3*2/100+" ����\n"
	            "���飺"+time3/4+" �㣬\n"
	            "Ǳ�ܣ�"+time3/28+" �㡣"NOR"\n");


	exp=time3*paid/1000;
	if (exp>time3) exp=time3;
	gold=time3*paid/1000;
	if (gold>time3) gold=time3;

	if (ob->query("id")=="12898983")
	{
		ob->add("combat_exp", time3*5/4);
	}

	ob->add("balance",gold*2);
	ob->add("combat_exp",exp/4);
	//tell_object(ob,"������Ĺ��׶ȣ����������"+gold*2/100+"��������"+exp/4+"�㾭�顣"NOR"\n");

	return "������Ĺ��׶ȣ����⽱����"+gold*2/100+"��������"+exp/4+"�㾭�顣"NOR"\n";
}

string ask_baotu()
{
	int now,last,nowfix,lastfix;
	mixed *t1,*t2;
	object tu,me = this_player();

	//if (!wizardp(me)) return "�����У����Ժ�������\n";
	if (me->query("zjvip/times") <1) return "�Բ�����ֻ���������˵����飡\n";
	if (me->query("zjvip/times") < 10*24*3600) return "�Բ��𣬻�Աʱ���Ѳ���10�죬������ȡ�ز�ͼ��\n";
	last = me->query("zjvip/last_baotu");
	now = time();
	t1 = localtime(now);
	t2 = localtime(last);
	nowfix = now+(6-t1[6])*86400;
	lastfix = last+(6-t2[6])*86400;
	if(last&&(localtime(nowfix)[7]==localtime(lastfix)[7]))
		return "һ����ֻ����һ�Σ�\n";
	if ((me->query_encumbrance()*100 / me->query_max_encumbrance())>90)
		return "�����ϵĶ���̫���ˣ�\n";
	if ( (time()-me->query("birthday")) < 7*86400 )
		return "�㻹�ǵ�����������ȡ�ر�ͼ�ɣ�\n";

	tu = new("/d/fuben/obj/heifeng1");
	tu->move(me);
	me->set("zjvip/last_baotu",now);
	message_vision("ʹ�߸���$Nһ��" + tu->query("name") + "��\n",me);
	log_file("vip_tu",ctime(time())+"��"+me->query("name")+"�ڶ���ʹ��������ȡһ�Ųر�ͼ��\n");
	return "����Ǻö���������������һ��ȥ̽��һ�°ɡ�\n";
}

string ask_yao()
{
	object me = this_object();
	object ob = this_player();
	object yao;

	if (ob->query("zjvip/times") <1) return "�Բ�����ֻ���������˵����飡\n";

	if ( (time()-ob->query_temp("last_huxindan"))<1800 )
	{
		command("say ��λ" + RANK_D->query_respect(ob) + "���㲻�Ǹո�������������ĵ�����ô����Ҫ�ˣ�");
		ob->unconcious();
		return "�����ִ�";
	}

	if (  present("huxin dan", ob) )
		return RANK_D->query_respect(ob) + "�����ϲ����Ѿ����������ĵ�������ô����Ҫ�ˣ� ����̰�����ᣡ";

	if (objectp(present("huxin dan", environment(ob))))
		return "������һ���������ĵ��������ǰ����ȴû�кú���ϧ...\n";

	if ((ob->query_encumbrance()*100 / ob->query_max_encumbrance())>90)
		return "�����ϵĶ���̫���ˣ�\n";

	yao = new("/clone/shizhe/huxindan9");
	yao->set_amount(99);
	yao->move(ob);
	ob->set_temp("last_huxindan",time());
	message_vision("$N����$nһЩ" + yao->query("name") + "��\n",me ,ob);
	return "����Ǻö�����ϣ���������߽�������������\n";
}
