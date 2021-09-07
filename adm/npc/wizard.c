
inherit NPC;
#include <ansi.h>

string ask_baibao();
int ask_character(string arg);
int ask_fanli();
int ask_xiandan();
int ask_illness();
int ask_kuilei();
int ask_mengzi();
int ask_buchang();
int ask_shimen();
int ask_gift();
int ask_viplv();
int ask_xidian();

string *sk_list = ({
		"qishang-quan",
		"zhuihun-jian",
		"zhuihun-jian",
		"zhuihun-jian",
		"baihua-quan",
		"baihua-quan",
		"hanbing-mianzhang",
		"hanbing-mianzhang",
		"hanbing-mianzhang",
		"sougu",
		"sougu",
		"yunlong-bian",
		"yunlong-bian",
		"yunlong-bian",
		"yunlong-shenfa",
		"yunlong-shenfa",
		"hanxing-bada",
		"hanxing-bada",
		"huanyin-zhi",
		"zijinbagua-dao",
		"sanfen-jianshu",
		"ningxue-shenzhao",
		"sanfen-jianshu",
		"huanyin-zhi",
		"zijinbagua-dao",
		"xuanming-zhang",
		"ningxue-shenzhao",
		"xuanming-zhang",
		"shenzhaojing",
});
string *sk_list2 = ({
		"qishang-quan",
		"zhuihun-jian",
		"baihua-quan",
		"hanbing-mianzhang",
		"sougu",
		"yunlong-bian",
		"yunlong-shenfa",
		"hanxing-bada",
		"xuanming-zhang",
		"sanfen-jianshu",
		"huanyin-zhi",
		"ningxue-shenzhao",
		"zijinbagua-dao",
		"shenzhaojing",
		"jiuyang-shengong",
});

void create()
{
		set_name("��ʦ",({  "wizard", "wushi" }) );
		set("gender", "����" );
		set("age", 30);
		set("long", "����һ�������������µ���ʦ��\n");

		set("str", 17);
		set("dex", 16);
		set("con", 15);
		set("int", 17);
		set("shen_type", 1);
		set("combat_exp", 100);
		set("attitude", "peaceful");

		setup();

		set("inquiry", ([
			//"����": (: ask_gift :),
//			"81Ǳ�ܽ���": (: ask_buchang :),
//			"81ʦ�Ž���": (: ask_shimen :),
			"�����": (: ask_baibao :),
			"���ӹ���": (: ask_fanli :),
			"�ɵ�": (: ask_xiandan :),
			//"�ı��Ը�" : (: ask_character(0) :),
			//"����": (: ask_illness :),
			"����": (: ask_mengzi :),
			"�������": (: ask_kuilei :),
	        "VIP�ɾ�": (: ask_viplv :),
		]));

		carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("ask_character","washme");
	add_action("ask_xidian","xidian");
	add_action("do_getvip","getvip");
	add_action("do_getsk","getsk");
}

int ask_gift()
{
	object ob = this_player();
	object gift;

	if (ob->query("zjvip/gift/2016christmas")) {
		command("say ���Ѿ���ȡ��ʥ�������ˣ�");
		return 1;
	}

	command("nod "+ob->query("id"));
	command("say ����ͷ����㡣");
	ob->set("zjvip/gift/2016christmas",1);
	gift = new("/clone/gift/gift_christmas");
	gift->move(ob);
	tell_object(ob,HIM"������һ����ƻ����"NOR"\n");  

	log_file("buchang", sprintf("%s��%s(%s)��ȡ��ʥ�����\n",ctime(time()),ob->query("name"),ob->query("id")));
	return 1;
}

int ask_viplv()
{
	int i,lv;
	object me;
	string str;

	me = this_player();
	str = ZJOBLONG"�������ѣ�������Ϸ�����ǩ��ÿ������������һ�⣬����һ������Ϊһ����ʦ�����ͣ�"ZJBR"���vip�ɾ����£�\n";
	str += ZJOBACTS2+ZJMENUF(1,1,10,30);
	str += "VIP2[�޼��ɵ�6��]["+((me->query("zjvip/level")>1)?"�Ѵ��":"��300����")+"]["
			+(me->query("zjvip/vipgift/vip2")?"����ȡ":"δ��ȡ")
			+"]:getvip 2"ZJSEP;
	str += "VIP3[���������������]["+((me->query("zjvip/level")>2)?"�Ѵ��":"��900����")+"]["
			+(me->query("zjvip/vipgift/vip3")?"����ȡ":"δ��ȡ")
			+"]:getvip 3"ZJSEP;
	str += "VIP4[����������ѡ1��]["+((me->query("zjvip/level")>3)?"�Ѵ��":"��1600����")+"]["
			+(me->query("zjvip/vipgift/vip4")?"����ȡ":"δ��ȡ")
			+"]:getvip 4"ZJSEP;
	str += "VIP5[ϴ������1��]["+((me->query("zjvip/level")>4||me->query("zjvip/reset_att_times"))?"�Ѵ��":"��3000����")+"]["
			+((me->query("zjvip/vipgift/vip5")&&!me->query("zjvip/reset_att_times"))?"����ȡ":"δ��ȡ")
			+"]:getvip 5"ZJSEP;
	str += "VIP6[ϴ�Ը�1��]["+((me->query("zjvip/level")>5||me->query("zjvip/reset_cha_times"))?"�Ѵ��":"��5500����")+"]["
			+((me->query("zjvip/vipgift/vip6")&&!me->query("zjvip/reset_cha_times"))?"����ȡ":"δ��ȡ")
			+"]:getvip 6"ZJSEP;
//	str += "VIP7[δ����]"+":getvip 7"ZJSEP;
//	str += "VIP8[δ����]"+":getvip 8"ZJSEP;
//	str += "VIP9[δ����]"+":getvip 9"ZJSEP;
//	str += "VIP10[δ����]"+":getvip 10";
	tell_object(me,str+"\n");
}

int do_getvip(string arg)
{
	int i,lv;
	object ob,me;
	string sk,str;

	me = this_player();
	if(!me->query("zjvip/times"))
	{
		tell_object(me,"��û��vip��������ȡvip�ɾͣ�\n");
		return 1;
	}
	lv = me->query("zjvip/level");
	if(!arg)
	{
		tell_object(me,"��Ҫ��ʲô��\n");
		return 1;
	}
	else if(arg=="2")
	{
		if(lv<2)
		{
			tell_object(me,"���ͣ��ﵽvip2��Ϳ�����ȡ�ɾͽ�����Ŷ��\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip2"))
		{
			tell_object(me,"���Ѿ���ȡ��vip2�ɾͽ����ˣ�\n");
			return 1;
		}
		ob = new("/clone/shizhe/dan_wuji");
		ob->set_amount(6);
		tell_object(me,"����ȡ���� 6 ���޼��ɵ���\n");
		log_ufile(me,"viplvgift","��ȡ����6���޼��ɵ���\n");
		me->set("zjvip/vipgift/vip2",1);
		ob->move(me);
	}
	else if(arg=="3")
	{
		if(lv<3)
		{
			tell_object(me,"�㻹û�д�ɸóɾͣ�������ȡ������\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip3"))
		{
			tell_object(me,"���Ѿ���ȡ��vip3�ɾͽ����ˣ�\n");
			return 1;
		}
		if(random(30)==10)
			sk = "jiuyang-shengong";
		else
			sk = sk_list[random(sizeof(sk_list))];

		me->set("zjvip/vipgift/vip3",1);
		if(me->query_skill(sk,1))
		{
			tell_object(me,"�������"+to_chinese(sk)+"��ֻ��ϧ���Ѿ����ˣ�\n");
			return 1;
		}
		me->set_skill(sk, 50);

		log_ufile(me,"viplvgift","�����ȡ����"+sk+"��\n");
		if(sk=="jiuyang-shengong")
		{
			tell_object(me, "��õ���һ��������¼��\n" );
			ob = new("/clone/book/jiuyang-copy");
			ob->move(me, 1);
		}
		tell_object(me, "���"+to_chinese(sk)+"��������50����\n" );
	}
	else if(arg=="4")
	{
		if(lv<4)
		{
			tell_object(me,"�㻹û�д�ɸóɾͣ�������ȡ������\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip4"))
		{
			tell_object(me,"���Ѿ���ȡ��vip4�ɾͽ����ˣ�\n");
			return 1;
		}
		str = ZJOBLONG"��ѡ������Ҫ�ļ��ܣ�\n";
		str += ZJOBACTS2+ZJMENUF(2,2,10,30);
		for(i=0;i<sizeof(sk_list2);i++)
		{
			str += to_chinese(sk_list2[i])+":getsk "+sk_list2[i];
			if(i<(sizeof(sk_list2)-1)) str += ZJSEP;
		}
		tell_object(me,str+"\n");
	}
	else if(arg=="5")
	{
		if(lv<5&&!me->query("zjvip/reset_att_times"))
		{
			tell_object(me,"�㻹û�д�ɸóɾͣ�������ȡ������\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip5")&&!me->query("zjvip/reset_att_times"))
		{
			tell_object(me,"���Ѿ���ȡ��vip5�ɾͽ����ˣ�\n");
			return 1;
		}
		ask_xidian();
	}
	else if(arg=="6")
	{
		if(lv<6&&!me->query("zjvip/reset_cha_times"))
		{
			tell_object(me,"�㻹û�д�ɸóɾͣ�������ȡ������\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip6")&&!me->query("zjvip/reset_cha_times"))
		{
			tell_object(me,"���Ѿ���ȡ��vip6�ɾͽ����ˣ�\n");
			return 1;
		}
		ask_character(0);
	}

	return 1;
}

int do_getsk(string arg)
{
	int i,lv;
	object ob,me;
	string sk,str;

	me = this_player();
	if(!me->query("zjvip/times"))
	{
		tell_object(me,"��û��vip��������ȡvip�ɾͣ�\n");
		return 1;
	}
	lv = me->query("zjvip/level");
	if(!arg || member_array(arg,sk_list2)==-1)
	{
		tell_object(me,"��Ҫ��ʲô��\n");
		return 1;
	}
	if(lv<4)
	{
		tell_object(me,"�㻹û�д�ɸóɾͣ�������ȡ������\n");
		return 1;
	}
	else if(me->query("zjvip/vipgift/vip4"))
	{
		tell_object(me,"���Ѿ���ȡ��vip4�ɾͽ����ˣ�\n");
		return 1;
	}

	if(me->query_skill(arg,1))
	{
		tell_object(me,"��ѡ����"+to_chinese(arg)+"��ֻ��ϧ���Ѿ����ˣ��뻻һ���ɣ�\n");
		return 1;
	}

	me->set("zjvip/vipgift/vip4",1);
	me->set_skill(arg, 50);
	log_ufile(me,"viplvgift","��ѡ��ȡ����"+arg+"��\n");

	if(arg=="jiuyang-shengong")
	{
		tell_object(me, "��õ���һ��������¼��\n" );
		ob = new("/clone/book/jiuyang-copy");
		ob->move(me, 1);
	}
	tell_object(me, "���"+to_chinese(arg)+"��������50����\n" );
	return 1;
}

int ask_shimen()
{
	int last,t;
	object zhi,qi,jiu,gao,dan,sha,putao,ob = this_player();
/*
	if (!wizardp(ob)) {
		command("say �Ժ󿪷ţ�");
		return 1;
	}
*/
	t = time();
	last = ob->query("shimen/last");
	if(!last || !same_week(last,t))
	{
		ob->set("shimen/today",0);
	}

	t = time();
	last = ob->query("zjvip/buchang_last");
	if(!last || !same_week(last,t))
	{
		ob->delete("zjvip/buchang_sm500");
		ob->delete("zjvip/buchang_sm1000");
		ob->delete("zjvip/buchang_sm1500");
		ob->delete("zjvip/buchang_sm2000");
		ob->delete("zjvip/buchang_sm2500");
		ob->delete("zjvip/buchang_sm3000");
		ob->delete("zjvip/buchang_sm3500");
	}

	if (ob->query("zjvip/buchang_sm500")) {
		command("say ���Ѿ���ȡ��500ʦ�Ž����ˣ�");
	}
	else if(ob->query("shimen/today")>=500)
	{
		ob->set("zjvip/buchang_sm500",1);
		ob->set("zjvip/buchang_last",time());
		putao = new("/clone/shizhe/putao");
		putao->set_amount(10);
		putao->move(ob);
		command("say �㱾��500ʦ���Ѵ�꣬��ȡ��10���ѽ�����");
		log_file("buchang", sprintf("%s��%s(%s)��ȡ��18-08-01��500ʦ�Ž�����\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say �㱾��500ʦ����δ��꣬��Ŭ����");

	if (ob->query("zjvip/buchang_sm1000")) {
		command("say ���Ѿ���ȡ��1000ʦ�Ž����ˣ�");
	}
	else if(ob->query("shimen/today")>=1000)
	{
		ob->set("zjvip/buchang_sm1000",1);
		ob->set("zjvip/buchang_last",time());
		putao = new("/clone/shizhe/putao");
		putao->set_amount(10);
		putao->move(ob);
		dan = new("/clone/shizhe/dan_chongmai1");
		dan->set_amount(30);
		dan->move(ob);
		command("say �㱾��1000ʦ���Ѵ�꣬��ȡ��10���Ѻ�30��Ʒ������������");
		log_file("buchang", sprintf("%s��%s(%s)��ȡ��18-08-01��1000ʦ�Ž�����\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say �㱾��1000ʦ����δ��꣬��Ŭ����");

	if (ob->query("zjvip/buchang_sm1500")) {
		command("say ���Ѿ���ȡ��1500ʦ�Ž����ˣ�");
	}
	else if(ob->query("shimen/today")>=1500)
	{
		ob->set("zjvip/buchang_sm1500",1);
		ob->set("zjvip/buchang_last",time());
		putao = new("/clone/shizhe/putao");
		putao->set_amount(10);
		putao->move(ob);
		dan = new("/clone/shizhe/dan_chongmai1");
		dan->set_amount(30);
		dan->move(ob);
		sha = new("/clone/shizhe/jinsha");
		sha->set_amount(10);
		sha->move(ob);
		command("say �㱾��1500ʦ���Ѵ�꣬��ȡ��10���ѡ�30��Ʒ��������10��ɰ������");
		log_file("buchang", sprintf("%s��%s(%s)��ȡ��18-08-01��1500ʦ�Ž�����\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say �㱾��1500ʦ����δ��꣬��Ŭ����");

	if (ob->query("zjvip/buchang_sm2000")) {
		command("say ���Ѿ���ȡ��2000ʦ�Ž����ˣ�");
	}
	else if(ob->query("shimen/today")>=2000)
	{
		ob->set("zjvip/buchang_sm2000",1);
		ob->set("zjvip/buchang_last",time());
		putao = new("/clone/shizhe/putao");
		putao->set_amount(10);
		putao->move(ob);
		dan = new("/clone/shizhe/dan_chongmai1");
		dan->set_amount(30);
		dan->move(ob);
		sha = new("/clone/shizhe/jinsha");
		sha->set_amount(10);
		sha->move(ob);
		gao = new("/clone/shizhe/fushougao");
		gao->set_amount(5);
		gao->move(ob);
		command("say �㱾��2000ʦ���Ѵ�꣬��ȡ��10���ѡ�30��Ʒ��������10��ɰ��5���ٸཱ����");
		log_file("buchang", sprintf("%s��%s(%s)��ȡ��18-08-01��2000ʦ�Ž�����\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say �㱾��2000ʦ����δ��꣬��Ŭ����");

	if (ob->query("zjvip/buchang_sm2500")) {
		command("say ���Ѿ���ȡ��2500ʦ�Ž����ˣ�");
	}
	else if(ob->query("shimen/today")>=2500)
	{
		ob->set("zjvip/buchang_sm2500",1);
		ob->set("zjvip/buchang_last",time());
		putao = new("/clone/shizhe/putao");
		putao->set_amount(10);
		putao->move(ob);
		dan = new("/clone/shizhe/dan_chongmai1");
		dan->set_amount(30);
		dan->move(ob);
		sha = new("/clone/shizhe/jinsha");
		sha->set_amount(10);
		sha->move(ob);
		gao = new("/clone/shizhe/fushougao");
		gao->set_amount(5);
		gao->move(ob);
		zhi = new("/clone/shizhe/xiaohuan");
		zhi->set_amount(10);
		zhi->move(ob);
		command("say �㱾��2500ʦ���Ѵ�꣬��ȡ��10���ѡ�30��Ʒ��������10��ɰ��5���ٸࡢ10��֥������");
		log_file("buchang", sprintf("%s��%s(%s)��ȡ��18-08-01��2500ʦ�Ž�����\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say �㱾��2500ʦ����δ��꣬��Ŭ����");

	if (ob->query("zjvip/buchang_sm3000")) {
		command("say ���Ѿ���ȡ��3000ʦ�Ž����ˣ�");
	}
	else if(ob->query("shimen/today")>=3000)
	{
		ob->set("zjvip/buchang_sm3000",1);
		ob->set("zjvip/buchang_last",time());
		putao = new("/clone/shizhe/putao");
		putao->set_amount(10);
		putao->move(ob);
		dan = new("/clone/shizhe/dan_chongmai1");
		dan->set_amount(30);
		dan->move(ob);
		sha = new("/clone/shizhe/jinsha");
		sha->set_amount(10);
		sha->move(ob);
		gao = new("/clone/shizhe/fushougao");
		gao->set_amount(5);
		gao->move(ob);
		zhi = new("/clone/shizhe/xiaohuan");
		zhi->set_amount(10);
		zhi->move(ob);
		qi = new("/clone/shizhe/putao1");
		qi->set_amount(1);
		qi->move(ob);
		command("say �㱾��3000ʦ���Ѵ�꣬��ȡ��10���ѡ�30��Ʒ��������10��ɰ��5���ٸࡢ10��֥��1�������ѣ�");
		log_file("buchang", sprintf("%s��%s(%s)��ȡ��18-08-01��3000ʦ�Ž�����\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say �㱾��3000ʦ����δ��꣬��Ŭ����");

	if (ob->query("zjvip/buchang_sm3500")) {
		command("say ���Ѿ���ȡ��3500ʦ�Ž����ˣ�");
	}
	else if(ob->query("shimen/today")>=3500)
	{
		ob->set("zjvip/buchang_sm3500",1);
		ob->set("zjvip/buchang_last",time());
		putao = new("/clone/shizhe/putao");
		putao->set_amount(10);
		putao->move(ob);
		dan = new("/clone/shizhe/dan_chongmai1");
		dan->set_amount(30);
		dan->move(ob);
		sha = new("/clone/shizhe/jinsha");
		sha->set_amount(10);
		sha->move(ob);
		gao = new("/clone/shizhe/fushougao");
		gao->set_amount(5);
		gao->move(ob);
		zhi = new("/clone/shizhe/lingzhi");
		zhi->set_amount(10);
		zhi->move(ob);
		qi = new("/clone/shizhe/putao1");
		qi->set_amount(1);
		qi->move(ob);
		jiu = new("/clone/shizhe/dan_jiuzhuan");
		jiu->move(ob);
		command("say �㱾��3500ʦ���Ѵ�꣬��ȡ��10���ѡ�30��Ʒ��������10��ɰ��5���ٸࡢ10��֥��1�������ѡ�1��ת�𵤣�");
		log_file("buchang", sprintf("%s��%s(%s)��ȡ��18-08-01��3500ʦ�Ž�����\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say �㱾��3500ʦ����δ��꣬��Ŭ����");

	return 1;
}

int ask_buchang()
{
	object ob = this_player();

	if (ob->query("zjvip/buchang180801")) {
		command("say ���Ѿ���ȡ����Ӧ�����ˣ�");
		return 1;
	}

	command("nod "+ob->query("id"));
	command("say ����ͷ����㡣");
	ob->set("zjvip/buchang180801",1);
	ob->delete("zjvip/buchang180723");
	ob->add("potential",40000);
	tell_object(ob,HIC"������40000��Ǳ�ܵĽ�������ף����Ϸ���֣�"NOR"\n");  

	log_file("buchang", sprintf("%s��%s(%s)��ȡ��18-07-23��崻�������\n",ctime(time()),ob->query("name"),ob->query("id")));
	return 1;
}

int ask_character(string arg)
{
	int i,lv;
	object me = this_player();
	string *skills,msg, type, cs;
	mapping skl;

	lv = me->query("zjvip/level");
	if(lv<6&&!me->query("zjvip/reset_cha_times"))
	{
		tell_object(me,"�㻹û�д�ɸóɾͣ�������ȡ������\n");
		return 1;
	}
	else if(me->query("zjvip/vipgift/vip6")&&!me->query("zjvip/reset_cha_times"))
	{
		tell_object(me,"���Ѿ���ȡ��vip6�ɾͽ����ˣ�\n");
		return 1;
	}

	if (!arg || arg == 0) {
		msg = ZJOBLONG+HIR"ע�⣺�ı��Ը�֮�󲻷���Ŀǰѧϰ�����ļ��ܽ���ɾ����"NOR ZJBR
			"�ĺ���������ʦ�ķ�-�����񹦣���߹���"ZJBR
			"�������䣬��ʦ�ķ�-�Ϻ����������ӷ���"ZJBR
			"�����䣬��ʦ�ķ�-�����񹦣��������"ZJBR
			"���ռ�թ����ʦ�ķ�-����ħ������������"ZJBR
			"��ѡ������Ը�\n";

		msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
		msg += "��������:washme ��������";
		msg += ZJSEP"������:washme ������";
		msg += ZJSEP"���ռ�թ:washme ���ռ�թ";
		msg += ZJSEP"�ĺ�����:washme �ĺ�����";
		write(msg + "\n");
	} else {
		if(sscanf(arg,"%s %s", type, cs) == 2)
		{
			if (me->query("character") == type) {
				tell_object(me, "�㱾�����������Ը�\n");
				return 1;
			}

			if (cs == "yes") {
				if (type == "��������" || type == "�ĺ�����" || type == "������" || type == "���ռ�թ") {
					log_ufile(me,"viplvgift","�ɹ����Ը���"+me->query("character")+"�ı�Ϊ"+type+"��\n");
					me->set("character", type);
					tell_object(me, "��ɹ����Ը�ı�Ϊ"+type+"��\n");

					skl = me->query_skills();
					skills = keys(skl);
					for(i=0;i<sizeof(skills);i++)
					{
						if(!SKILL_D(skills[i])->valid_learn(me) && strsrch(skills[i],"-cognize")==-1)
						{
							tell_object(me, to_chinese(skills[i])+"�Ѿ�������ѧϰ�������Զ�ɾ�������д�������ϵ�������ָ���\n");
							log_ufile(me,"viplvgift",me->query_skill(skills[i],1)+"��"+skills[i]+"ϴ����Ѿ�������ѧϰ�������Զ�ɾ����\n");
							me->set("valid_skill/"+skills[i],me->query_skill(skills[i],1));
							me->delete_skill(skills[i]);
						}
					}
					if(me->query("zjvip/reset_cha_times"))
						me->delete("zjvip/reset_cha_times");
					else
						me->set("zjvip/vipgift/vip6",1);
				} else {
					tell_object(me, "û�������Ը�������ѡ��\n");
					return 1;
				}
			}
		} else {
			msg = ZJOBLONG+"��ȷ��ѡ���Ը�Ϊ"+HIG+arg+NOR"��\n";			
			msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
			msg += "ȷ��:washme "+arg + " yes";
			msg += ZJSEP"ȡ��: ";
			
			write(msg + "\n");
		}
	}
	
	return 1;
}

int ask_xidian(string arg)
{
	int i,rand,all,tmpstr,tmpcon,tmpdex,tmpint,lv;
	int dstr,dcon,ddex,dint;
	string leipi,*skills,msg, type, cs;
	mapping skl;

	object me = this_player();

	lv = me->query("zjvip/level");
	if(lv<5&&!me->query("zjvip/reset_att_times"))
	{
		tell_object(me,"�㻹û�д�ɸóɾͣ�������ȡ������\n");
		return 1;
	}
	else if(me->query("zjvip/vipgift/vip5")&&!me->query("zjvip/reset_att_times"))
	{
		tell_object(me,"���Ѿ���ȡ��vip5�ɾͽ����ˣ�\n");
		return 1;
	}

	all = me->query("str") + me->query("int") + me->query("con") + me->query("dex");
	if(!me->query("gift/lighting"))
	{
		leipi = HIM"����δ�����������츳�¼�������ϴ�㽫�����������츳��"ZJBR;
		all++;
	}else leipi = "";
	
	if (!arg) {
		tell_object(me,INPUTTXT(leipi+"ע�⣺"HIR"ϴ������в�����ѧϰ�����ļ��ܶ���ɾ���������濼�ǡ�"NOR"$br#�������������ķ�����$br#"
						"���ձ��������ԡ����ǡ�����������4����"
						"�ո�ֿ�������ע��ÿ�������ܵ���13�����39��4����֮�ͱ���Ϊ"+all+"��","xidian $txt#")+"\n");
		return 1;
	}
	else if(sscanf(arg, "yes %d %d %d %d",tmpstr,tmpint,tmpcon,tmpdex) == 4)
	{
		if(tmpstr<13||tmpint<13||tmpcon<13||tmpdex<13||tmpstr>39||tmpint>39||tmpcon>39||tmpdex>39||(tmpstr+tmpint+tmpcon+tmpdex)!=all)
		{
			tell_object(me,INPUTTXT(leipi+"ע�⣺"HIR"ϴ������в�����ѧϰ�����ļ��ܶ���ɾ���������濼�ǡ�"NOR"$br#�������������ķ�����$br#"
					"���ձ��������ԡ����ǡ�����������4����"
					"�ո�ֿ�������ע��ÿ�������ܵ���13�����39��4����֮�ͱ���Ϊ"+all+"��","xidian $txt#")+"\n");
			return 1;
		}
		me->set("str",tmpstr);
		me->set("int",tmpint);
		me->set("con",tmpcon);
		me->set("dex",tmpdex);
		if(leipi != "")
			me->add("gift/lighting", 1);

		log_ufile(me,"viplvgift",sprintf("�ɹ�ϴ�㣬Ŀǰ������[%d]������[%d]������[%d]����[%d]��\n",me->query("str"),me->query("int"),me->query("con"),me->query("dex")));
		skl = me->query_skills();
		skills = keys(skl);
		for(i=0;i<sizeof(skills);i++)
		{
			if(!SKILL_D(skills[i])->valid_learn(me) && strsrch(skills[i],"-cognize")==-1)
			{
				tell_object(me, to_chinese(skills[i])+"�Ѿ�������ѧϰ�������Զ�ɾ�������д�������ϵ�������ָ���\n");
				log_ufile(me,"viplvgift",me->query_skill(skills[i],1)+"��"+skills[i]+"ϴ����Ѿ�������ѧϰ�������Զ�ɾ����\n");
				me->set("valid_skill/"+skills[i],me->query_skill(skills[i],1));
				me->delete_skill(skills[i]);
			}
		}
		tell_object(me, "ϴ��ɹ���ף����Ϸ��졣\n");
		if(me->query("zjvip/reset_att_times"))
			me->delete("zjvip/reset_att_times");
		else
			me->set("zjvip/vipgift/vip5",1);
	}
	else if(sscanf(arg, "%d %d %d %d",tmpstr,tmpint,tmpcon,tmpdex)  == 4)
	{
		msg = ZJOBLONG+"����["+tmpstr+"]������["+tmpint+"]������["+tmpcon+"]����["+tmpdex+"]����ȷ����\n";			
		msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
		msg += "ȷ��:xidian yes "+arg;
		msg += ZJSEP"ȡ��:look";
		tell_object(me,msg+"\n");
	}
	else
	{
		tell_object(me,INPUTTXT("�����ʽ���ԣ������������������ķ�����$br#"
						"���ձ��������ԡ����ǡ�����������4����"
						"�ո�ֿ�������ע��ÿ�������ܵ���13�����39��4����֮�ͱ���Ϊ"+all+"��","xidian $txt#")+"\n");
	}
	
	return 1;
}

int ask_fanli()
{
		int i;
		object ob = this_player();
		i=ob->query("zjvip/dizi_pay");
	 
		if(ob->query("zjvip/dizi_pay")<1){
				command("say ��Ŀǰ�ĵ��ӹ���̫�ͣ��޷���ȡ������");
				message_vision("$N���ۼƻ����"+ob->query("zjvip/dizi_fanli")+"��Ԫ���Ľ�����\n",ob,  this_object());
				return 1;
		}
		else {
				command("nod "+ob->query("id"));
				command("say ���ѷ�����ȡ���ӹ��׽���������");
			ob->add("yuanbao",i);
				ob->add("zjvip/dizi_pay",-i);
				ob->add("zjvip/dizi_fanli",i);
				message_vision("$N�����"+i+"��Ԫ���Ľ�����\n",ob,  this_object());
				message_vision("$N���ۼƻ����"+ob->query("zjvip/dizi_fanli")+"��Ԫ���Ľ�����\n",ob,  this_object());
				return 1;
		}
}

int ask_xiandan()
{
	int a,b,c,d;
	object ob = this_player();

	a=ob->query("gift/xiandan");
	b=ob->query("gift/unknowdan");
	c=ob->query("gift/shenliwan");
	d=ob->query("gift/xisuidan");
	 
	if (ob->query("zjvip/times") <1) {
		command("say �Բ�����ֻ���������˵����飡");
		return 1;
	}
	else {
		command("nod "+ob->query("id"));
		command("say ���������һ�¼�¼��");
		command("say ��λ" + RANK_D->query_respect(ob) +"�����Ѿ����ˣ�"+chinese_number(a)+"��"HIY"�����ɵ�"NOR"��"+chinese_number(b)+"��"HIR"����ɵ�"NOR"��"+chinese_number(c)+"��"HIG"������"NOR"��"+chinese_number(d)+"��"YEL"ϴ�赤"NOR"��");
		return 1;
	}
}

int ask_illness()
{
	int a,b,c,d;
	object ob = this_player();

	a=ob->query("gift/xiandan_fail");
	b=ob->query("gift/unknowdan_fail");
	c=ob->query("gift/shenliwan_fail");
	d=ob->query("gift/xisuidan_fail");
	 
	if (ob->query("zjvip/times") <1) {
			command("say �Բ�����ֻ���������˵����飡");
			return 1;
		}
		else {
			command("nod "+ob->query("id"));
			command("say ���������һ�¼�¼��");
			command("say ��λ" + RANK_D->query_respect(ob) +"�������"HIY "�����ɵ�" NOR"��"+chinese_number(a)+"������������"HIR "����ɵ�" NOR"��"+chinese_number(b)+"������������"HIG "������" NOR"��"+chinese_number(c)+"������������"YEL "ϴ�赤" NOR"��"+chinese_number(d)+"��������");
			return 1;
		}
}

string ask_baibao()
{
	object ob;
	mapping myfam;
	object nang;

	ob = this_player();
	myfam = (mapping)ob->query("family");
		
	//if(!myfam) return "�㻹���ȼ������ɰɣ�";

	if (ob->query("combat_exp") < 10000)
		return "��Ȼ��������ֻǬ������������ս��������ô�������������ô�죿\n";

	if (ob->query("chuwudai"))
		return "��֮ǰ�����Ѿ���������㻹�ǸϽ���ϵ����Աȥ����һ�°ɡ�\n";
		
	if ( present("chuwu dai", ob))
		return "���Ѿ�����һ�����������̰�����ᣡ\n";

	nang=new("/clone/misc/baibao");
	nang->set("owner_id", ob->query("id"));
	nang->move(ob);
	ob->set("chuwudai", 1);
	write("��õ�һ�������!\n");
	return "����Ǹ��������ú��������ɡ�";
}

int ask_kuilei()
{
	object ob = this_player();
	object yao;
	int last = ob->query("zjvip/last_get_kuilei");
	int now = time();
	 
	if (ob->query("zjvip/times") <1) {
		command("say �Բ�����ֻ���������˵����飡");
		return 1;
	}
	if ((ob->query("zjvip/all_pay")+ob->query("gongxians"))<1000) {
		command("say �Բ�����Ĺ��ײ�������������ȡ������ܵ�������");
		return 1;
	}
	if(localtime(last)[4] != localtime(now)[4])
	{
		ob->set("zjvip/last_get_kuilei",now);
		ob->delete("zjvip/get_kuilei");
	}

	if (ob->query("zjvip/get_kuilei")>=((ob->query("zjvip/all_pay")+ob->query("gongxians"))/1000)) {
		command("say ����Ŀǰ�Ĺ���ֻ����"+chinese_number((ob->query("zjvip/all_pay")+ob->query("gongxians"))/1000)+"��������ܣ�");
		return 1;
	}

	command("nod "+ob->query("id"));
	command("say ����͸��㡣");
	yao = new("/clone/shizhe/kuilei");
	yao->move(ob);
	ob->add("zjvip/get_kuilei",1);

	message_vision("$N����$nһ��" + yao->query("name") + "��\n",this_object(),ob);
	log_file("gift", sprintf(ob->query("id")+"��%s����ȡ��һ��������ܡ�\n",ctime(time())));
	return 1;
		
}

int ask_mengzi()
{
		object ob = this_player();
		object yao;

	 
	if (ob->query("zjvip/times") <1) {
		command("say �Բ�����ֻ���������˵����飡");
		return 1;
	}
	if (ob->query("zjvip/all_pay")+ob->query("gongxians")<1000) {
		command("say �Բ�����Ĺ��ײ�������������ȡ�����ӡ���������");
		return 1;
	}

	if ( present("mengzi book", ob)) {
		command("say ���Ѿ�����һ�������ӡ��ˣ���̰�����ᣡ");
		return 1;
	}

	command("nod "+ob->query("id"));
	command("say ����͸��㡣");
	yao = new("/clone/shizhe/mengzi");
	yao->move(ob);
	message_vision("$N����$nһ����" + yao->query("name") + "����\n",this_object(),ob);
	return 1;
		
}
