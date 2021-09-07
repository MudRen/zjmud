
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
		set_name("巫师",({  "wizard", "wushi" }) );
		set("gender", "男性" );
		set("age", 30);
		set("long", "这是一个成天无所事事的巫师。\n");

		set("str", 17);
		set("dex", 16);
		set("con", 15);
		set("int", 17);
		set("shen_type", 1);
		set("combat_exp", 100);
		set("attitude", "peaceful");

		setup();

		set("inquiry", ([
			//"礼物": (: ask_gift :),
//			"81潜能奖励": (: ask_buchang :),
//			"81师门奖励": (: ask_shimen :),
			"储物袋": (: ask_baibao :),
			"弟子贡献": (: ask_fanli :),
			"仙丹": (: ask_xiandan :),
			//"改变性格" : (: ask_character(0) :),
			//"暗疾": (: ask_illness :),
			"孟子": (: ask_mengzi :),
			"替身傀儡": (: ask_kuilei :),
	        "VIP成就": (: ask_viplv :),
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
		command("say 你已经领取过圣诞礼物了！");
		return 1;
	}

	command("nod "+ob->query("id"));
	command("say 我这就发给你。");
	ob->set("zjvip/gift/2016christmas",1);
	gift = new("/clone/gift/gift_christmas");
	gift->move(ob);
	tell_object(ob,HIM"你获得了一个红苹果。"NOR"\n");  

	log_file("buchang", sprintf("%s：%s(%s)领取了圣诞礼物。\n",ctime(time()),ob->query("name"),ob->query("id")));
	return 1;
}

int ask_viplv()
{
	int i,lv;
	object me;
	string str;

	me = this_player();
	str = ZJOBLONG"合理消费，快乐游戏，坚持签到每天来江湖中走一遭，终有一天你会成为一代宗师，加油！"ZJBR"你的vip成就如下：\n";
	str += ZJOBACTS2+ZJMENUF(1,1,10,30);
	str += "VIP2[无极仙丹6颗]["+((me->query("zjvip/level")>1)?"已达成":"需300贡献")+"]["
			+(me->query("zjvip/vipgift/vip2")?"已领取":"未领取")
			+"]:getvip 2"ZJSEP;
	str += "VIP3[公共技能随机奖励]["+((me->query("zjvip/level")>2)?"已达成":"需900贡献")+"]["
			+(me->query("zjvip/vipgift/vip3")?"已领取":"未领取")
			+"]:getvip 3"ZJSEP;
	str += "VIP4[公共技能自选1次]["+((me->query("zjvip/level")>3)?"已达成":"需1600贡献")+"]["
			+(me->query("zjvip/vipgift/vip4")?"已领取":"未领取")
			+"]:getvip 4"ZJSEP;
	str += "VIP5[洗基础点1次]["+((me->query("zjvip/level")>4||me->query("zjvip/reset_att_times"))?"已达成":"需3000贡献")+"]["
			+((me->query("zjvip/vipgift/vip5")&&!me->query("zjvip/reset_att_times"))?"已领取":"未领取")
			+"]:getvip 5"ZJSEP;
	str += "VIP6[洗性格1次]["+((me->query("zjvip/level")>5||me->query("zjvip/reset_cha_times"))?"已达成":"需5500贡献")+"]["
			+((me->query("zjvip/vipgift/vip6")&&!me->query("zjvip/reset_cha_times"))?"已领取":"未领取")
			+"]:getvip 6"ZJSEP;
//	str += "VIP7[未开放]"+":getvip 7"ZJSEP;
//	str += "VIP8[未开放]"+":getvip 8"ZJSEP;
//	str += "VIP9[未开放]"+":getvip 9"ZJSEP;
//	str += "VIP10[未开放]"+":getvip 10";
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
		tell_object(me,"你没有vip，不能领取vip成就！\n");
		return 1;
	}
	lv = me->query("zjvip/level");
	if(!arg)
	{
		tell_object(me,"你要干什么！\n");
		return 1;
	}
	else if(arg=="2")
	{
		if(lv<2)
		{
			tell_object(me,"加油，达到vip2你就可以领取成就奖励了哦！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip2"))
		{
			tell_object(me,"你已经领取过vip2成就奖励了！\n");
			return 1;
		}
		ob = new("/clone/shizhe/dan_wuji");
		ob->set_amount(6);
		tell_object(me,"你领取到了 6 颗无极仙丹！\n");
		log_ufile(me,"viplvgift","领取到了6颗无极仙丹！\n");
		me->set("zjvip/vipgift/vip2",1);
		ob->move(me);
	}
	else if(arg=="3")
	{
		if(lv<3)
		{
			tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip3"))
		{
			tell_object(me,"你已经领取过vip3成就奖励了！\n");
			return 1;
		}
		if(random(30)==10)
			sk = "jiuyang-shengong";
		else
			sk = sk_list[random(sizeof(sk_list))];

		me->set("zjvip/vipgift/vip3",1);
		if(me->query_skill(sk,1))
		{
			tell_object(me,"你抽中了"+to_chinese(sk)+"，只可惜你已经会了！\n");
			return 1;
		}
		me->set_skill(sk, 50);

		log_ufile(me,"viplvgift","随机领取到了"+sk+"！\n");
		if(sk=="jiuyang-shengong")
		{
			tell_object(me, "你得到了一本九阳秘录！\n" );
			ob = new("/clone/book/jiuyang-copy");
			ob->move(me, 1);
		}
		tell_object(me, "你的"+to_chinese(sk)+"提升到了50级！\n" );
	}
	else if(arg=="4")
	{
		if(lv<4)
		{
			tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip4"))
		{
			tell_object(me,"你已经领取过vip4成就奖励了！\n");
			return 1;
		}
		str = ZJOBLONG"请选择你想要的技能：\n";
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
			tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip5")&&!me->query("zjvip/reset_att_times"))
		{
			tell_object(me,"你已经领取过vip5成就奖励了！\n");
			return 1;
		}
		ask_xidian();
	}
	else if(arg=="6")
	{
		if(lv<6&&!me->query("zjvip/reset_cha_times"))
		{
			tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
			return 1;
		}
		else if(me->query("zjvip/vipgift/vip6")&&!me->query("zjvip/reset_cha_times"))
		{
			tell_object(me,"你已经领取过vip6成就奖励了！\n");
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
		tell_object(me,"你没有vip，不能领取vip成就！\n");
		return 1;
	}
	lv = me->query("zjvip/level");
	if(!arg || member_array(arg,sk_list2)==-1)
	{
		tell_object(me,"你要干什么！\n");
		return 1;
	}
	if(lv<4)
	{
		tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
		return 1;
	}
	else if(me->query("zjvip/vipgift/vip4"))
	{
		tell_object(me,"你已经领取过vip4成就奖励了！\n");
		return 1;
	}

	if(me->query_skill(arg,1))
	{
		tell_object(me,"你选择了"+to_chinese(arg)+"，只可惜你已经会了，请换一个吧！\n");
		return 1;
	}

	me->set("zjvip/vipgift/vip4",1);
	me->set_skill(arg, 50);
	log_ufile(me,"viplvgift","自选领取到了"+arg+"！\n");

	if(arg=="jiuyang-shengong")
	{
		tell_object(me, "你得到了一本九阳秘录！\n" );
		ob = new("/clone/book/jiuyang-copy");
		ob->move(me, 1);
	}
	tell_object(me, "你的"+to_chinese(arg)+"提升到了50级！\n" );
	return 1;
}

int ask_shimen()
{
	int last,t;
	object zhi,qi,jiu,gao,dan,sha,putao,ob = this_player();
/*
	if (!wizardp(ob)) {
		command("say 稍后开放！");
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
		command("say 你已经领取过500师门奖励了！");
	}
	else if(ob->query("shimen/today")>=500)
	{
		ob->set("zjvip/buchang_sm500",1);
		ob->set("zjvip/buchang_last",time());
		putao = new("/clone/shizhe/putao");
		putao->set_amount(10);
		putao->move(ob);
		command("say 你本周500师门已达标，领取了10葡萄奖励！");
		log_file("buchang", sprintf("%s：%s(%s)领取了18-08-01的500师门奖励。\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say 你本周500师门尚未达标，请努力！");

	if (ob->query("zjvip/buchang_sm1000")) {
		command("say 你已经领取过1000师门奖励了！");
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
		command("say 你本周1000师门已达标，领取了10葡萄和30下品冲脉丹奖励！");
		log_file("buchang", sprintf("%s：%s(%s)领取了18-08-01的1000师门奖励。\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say 你本周1000师门尚未达标，请努力！");

	if (ob->query("zjvip/buchang_sm1500")) {
		command("say 你已经领取过1500师门奖励了！");
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
		command("say 你本周1500师门已达标，领取了10葡萄、30下品冲脉丹和10金砂奖励！");
		log_file("buchang", sprintf("%s：%s(%s)领取了18-08-01的1500师门奖励。\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say 你本周1500师门尚未达标，请努力！");

	if (ob->query("zjvip/buchang_sm2000")) {
		command("say 你已经领取过2000师门奖励了！");
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
		command("say 你本周2000师门已达标，领取了10葡萄、30下品冲脉丹、10金砂和5福寿膏奖励！");
		log_file("buchang", sprintf("%s：%s(%s)领取了18-08-01的2000师门奖励。\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say 你本周2000师门尚未达标，请努力！");

	if (ob->query("zjvip/buchang_sm2500")) {
		command("say 你已经领取过2500师门奖励了！");
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
		command("say 你本周2500师门已达标，领取了10葡萄、30下品冲脉丹、10金砂和5福寿膏、10灵芝奖励！");
		log_file("buchang", sprintf("%s：%s(%s)领取了18-08-01的2500师门奖励。\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say 你本周2500师门尚未达标，请努力！");

	if (ob->query("zjvip/buchang_sm3000")) {
		command("say 你已经领取过3000师门奖励了！");
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
		command("say 你本周3000师门已达标，领取了10葡萄、30下品冲脉丹、10金砂和5福寿膏、10灵芝、1神奇葡萄！");
		log_file("buchang", sprintf("%s：%s(%s)领取了18-08-01的3000师门奖励。\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say 你本周3000师门尚未达标，请努力！");

	if (ob->query("zjvip/buchang_sm3500")) {
		command("say 你已经领取过3500师门奖励了！");
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
		command("say 你本周3500师门已达标，领取了10葡萄、30下品冲脉丹、10金砂和5福寿膏、10灵芝、1神奇葡萄、1九转金丹！");
		log_file("buchang", sprintf("%s：%s(%s)领取了18-08-01的3500师门奖励。\n",ctime(time()),ob->query("name"),ob->query("id")));
	}
	else
		command("say 你本周3500师门尚未达标，请努力！");

	return 1;
}

int ask_buchang()
{
	object ob = this_player();

	if (ob->query("zjvip/buchang180801")) {
		command("say 你已经领取过相应补偿了！");
		return 1;
	}

	command("nod "+ob->query("id"));
	command("say 我这就发给你。");
	ob->set("zjvip/buchang180801",1);
	ob->delete("zjvip/buchang180723");
	ob->add("potential",40000);
	tell_object(ob,HIC"你获得了40000点潜能的奖励，并祝你游戏快乐！"NOR"\n");  

	log_file("buchang", sprintf("%s：%s(%s)领取了18-07-23的宕机补偿。\n",ctime(time()),ob->query("name"),ob->query("id")));
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
		tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
		return 1;
	}
	else if(me->query("zjvip/vipgift/vip6")&&!me->query("zjvip/reset_cha_times"))
	{
		tell_object(me,"你已经领取过vip6成就奖励了！\n");
		return 1;
	}

	if (!arg || arg == 0) {
		msg = ZJOBLONG+HIR"注意：改变性格之后不符合目前学习条件的技能将被删除！"NOR ZJBR
			"心狠手辣，宗师心法-九阴神功，提高攻击"ZJBR
			"光明磊落，宗师心法-南海玄功，增加防御"ZJBR
			"狡黠多变，宗师心法-不败神功，提高命中"ZJBR
			"阴险奸诈，宗师心法-葵花魔功，增加闪避"ZJBR
			"请选择你的性格：\n";

		msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
		msg += "光明磊落:washme 光明磊落";
		msg += ZJSEP"狡黠多变:washme 狡黠多变";
		msg += ZJSEP"阴险奸诈:washme 阴险奸诈";
		msg += ZJSEP"心狠手辣:washme 心狠手辣";
		write(msg + "\n");
	} else {
		if(sscanf(arg,"%s %s", type, cs) == 2)
		{
			if (me->query("character") == type) {
				tell_object(me, "你本来就是这种性格。\n");
				return 1;
			}

			if (cs == "yes") {
				if (type == "光明磊落" || type == "心狠手辣" || type == "狡黠多变" || type == "阴险奸诈") {
					log_ufile(me,"viplvgift","成功将性格由"+me->query("character")+"改变为"+type+"！\n");
					me->set("character", type);
					tell_object(me, "你成功将性格改变为"+type+"。\n");

					skl = me->query_skills();
					skills = keys(skl);
					for(i=0;i<sizeof(skills);i++)
					{
						if(!SKILL_D(skills[i])->valid_learn(me) && strsrch(skills[i],"-cognize")==-1)
						{
							tell_object(me, to_chinese(skills[i])+"已经不符合学习条件，自动删除，如有错误请联系代码管理恢复。\n");
							log_ufile(me,"viplvgift",me->query_skill(skills[i],1)+"级"+skills[i]+"洗点后已经不符合学习条件，自动删除。\n");
							me->set("valid_skill/"+skills[i],me->query_skill(skills[i],1));
							me->delete_skill(skills[i]);
						}
					}
					if(me->query("zjvip/reset_cha_times"))
						me->delete("zjvip/reset_cha_times");
					else
						me->set("zjvip/vipgift/vip6",1);
				} else {
					tell_object(me, "没有这种性格，请认真选择。\n");
					return 1;
				}
			}
		} else {
			msg = ZJOBLONG+"你确定选择性格为"+HIG+arg+NOR"吗？\n";			
			msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
			msg += "确定:washme "+arg + " yes";
			msg += ZJSEP"取消: ";
			
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
		tell_object(me,"你还没有达成该成就，不能领取奖励！\n");
		return 1;
	}
	else if(me->query("zjvip/vipgift/vip5")&&!me->query("zjvip/reset_att_times"))
	{
		tell_object(me,"你已经领取过vip5成就奖励了！\n");
		return 1;
	}

	all = me->query("str") + me->query("int") + me->query("con") + me->query("dex");
	if(!me->query("gift/lighting"))
	{
		leipi = HIM"你尚未遭遇过雷劈天赋事件，本次洗点将赠送你雷劈天赋！"ZJBR;
		all++;
	}else leipi = "";
	
	if (!arg) {
		tell_object(me,INPUTTXT(leipi+"注意："HIR"洗点后所有不符合学习条件的技能都将删除，请认真考虑。"NOR"$br#请输入你想分配的方案：$br#"
						"按照臂力、悟性、根骨、身法次序输入4个用"
						"空格分开的数，注意每个数不能低于13或大于39，4个数之和必须为"+all+"。","xidian $txt#")+"\n");
		return 1;
	}
	else if(sscanf(arg, "yes %d %d %d %d",tmpstr,tmpint,tmpcon,tmpdex) == 4)
	{
		if(tmpstr<13||tmpint<13||tmpcon<13||tmpdex<13||tmpstr>39||tmpint>39||tmpcon>39||tmpdex>39||(tmpstr+tmpint+tmpcon+tmpdex)!=all)
		{
			tell_object(me,INPUTTXT(leipi+"注意："HIR"洗点后所有不符合学习条件的技能都将删除，请认真考虑。"NOR"$br#请输入你想分配的方案：$br#"
					"按照臂力、悟性、根骨、身法次序输入4个用"
					"空格分开的数，注意每个数不能低于13或大于39，4个数之和必须为"+all+"。","xidian $txt#")+"\n");
			return 1;
		}
		me->set("str",tmpstr);
		me->set("int",tmpint);
		me->set("con",tmpcon);
		me->set("dex",tmpdex);
		if(leipi != "")
			me->add("gift/lighting", 1);

		log_ufile(me,"viplvgift",sprintf("成功洗点，目前：臂力[%d]，悟性[%d]，根骨[%d]，身法[%d]。\n",me->query("str"),me->query("int"),me->query("con"),me->query("dex")));
		skl = me->query_skills();
		skills = keys(skl);
		for(i=0;i<sizeof(skills);i++)
		{
			if(!SKILL_D(skills[i])->valid_learn(me) && strsrch(skills[i],"-cognize")==-1)
			{
				tell_object(me, to_chinese(skills[i])+"已经不符合学习条件，自动删除，如有错误请联系代码管理恢复。\n");
				log_ufile(me,"viplvgift",me->query_skill(skills[i],1)+"级"+skills[i]+"洗点后已经不符合学习条件，自动删除。\n");
				me->set("valid_skill/"+skills[i],me->query_skill(skills[i],1));
				me->delete_skill(skills[i]);
			}
		}
		tell_object(me, "洗点成功，祝您游戏愉快。\n");
		if(me->query("zjvip/reset_att_times"))
			me->delete("zjvip/reset_att_times");
		else
			me->set("zjvip/vipgift/vip5",1);
	}
	else if(sscanf(arg, "%d %d %d %d",tmpstr,tmpint,tmpcon,tmpdex)  == 4)
	{
		msg = ZJOBLONG+"臂力["+tmpstr+"]，悟性["+tmpint+"]，根骨["+tmpcon+"]，身法["+tmpdex+"]，你确定吗？\n";			
		msg += ZJOBACTS2+ZJMENUF(2,2,9,30);
		msg += "确定:xidian yes "+arg;
		msg += ZJSEP"取消:look";
		tell_object(me,msg+"\n");
	}
	else
	{
		tell_object(me,INPUTTXT("输入格式不对，请重新输入你想分配的方案：$br#"
						"按照臂力、悟性、根骨、身法次序输入4个用"
						"空格分开的数，注意每个数不能低于13或大于39，4个数之和必须为"+all+"。","xidian $txt#")+"\n");
	}
	
	return 1;
}

int ask_fanli()
{
		int i;
		object ob = this_player();
		i=ob->query("zjvip/dizi_pay");
	 
		if(ob->query("zjvip/dizi_pay")<1){
				command("say 你目前的弟子贡献太低，无法领取奖励。");
				message_vision("$N已累计获得了"+ob->query("zjvip/dizi_fanli")+"个元宝的奖励。\n",ob,  this_object());
				return 1;
		}
		else {
				command("nod "+ob->query("id"));
				command("say 你已符合领取弟子贡献奖励条件。");
			ob->add("yuanbao",i);
				ob->add("zjvip/dizi_pay",-i);
				ob->add("zjvip/dizi_fanli",i);
				message_vision("$N获得了"+i+"个元宝的奖励。\n",ob,  this_object());
				message_vision("$N已累计获得了"+ob->query("zjvip/dizi_fanli")+"个元宝的奖励。\n",ob,  this_object());
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
		command("say 对不起，我只处理东方族人的事情！");
		return 1;
	}
	else {
		command("nod "+ob->query("id"));
		command("say 我来帮你查一下记录。");
		command("say 这位" + RANK_D->query_respect(ob) +"，你已经吃了："+chinese_number(a)+"颗"HIY"醍醐仙丹"NOR"，"+chinese_number(b)+"颗"HIR"火红仙丹"NOR"，"+chinese_number(c)+"颗"HIG"神力丸"NOR"，"+chinese_number(d)+"颗"YEL"洗髓丹"NOR"。");
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
			command("say 对不起，我只处理东方族人的事情！");
			return 1;
		}
		else {
			command("nod "+ob->query("id"));
			command("say 我来帮你查一下记录。");
			command("say 这位" + RANK_D->query_respect(ob) +"，你吃了"HIY "醍醐仙丹" NOR"有"+chinese_number(a)+"处暗疾，吃了"HIR "火红仙丹" NOR"有"+chinese_number(b)+"处暗疾，吃了"HIG "神力丸" NOR"有"+chinese_number(c)+"处暗疾，吃了"YEL "洗髓丹" NOR"有"+chinese_number(d)+"处暗疾。");
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
		
	//if(!myfam) return "你还是先加入门派吧？";

	if (ob->query("combat_exp") < 10000)
		return "虽然我这里有只乾坤袋，可是你战斗经验这么差，被人抢走了怎么办？\n";

	if (ob->query("chuwudai"))
		return "你之前不是已经领过了吗？你还是赶紧联系管理员去处理一下吧。\n";
		
	if ( present("chuwu dai", ob))
		return "你已经有了一个储物袋，别贪得无厌！\n";

	nang=new("/clone/misc/baibao");
	nang->set("owner_id", ob->query("id"));
	nang->move(ob);
	ob->set("chuwudai", 1);
	write("你得到一个储物袋!\n");
	return "这可是个宝贝，好好利用它吧。";
}

int ask_kuilei()
{
	object ob = this_player();
	object yao;
	int last = ob->query("zjvip/last_get_kuilei");
	int now = time();
	 
	if (ob->query("zjvip/times") <1) {
		command("say 对不起，我只处理东方族人的事情！");
		return 1;
	}
	if ((ob->query("zjvip/all_pay")+ob->query("gongxians"))<1000) {
		command("say 对不起，你的贡献不够，不符合领取替身傀儡的条件！");
		return 1;
	}
	if(localtime(last)[4] != localtime(now)[4])
	{
		ob->set("zjvip/last_get_kuilei",now);
		ob->delete("zjvip/get_kuilei");
	}

	if (ob->query("zjvip/get_kuilei")>=((ob->query("zjvip/all_pay")+ob->query("gongxians"))/1000)) {
		command("say 以你目前的贡献只能领"+chinese_number((ob->query("zjvip/all_pay")+ob->query("gongxians"))/1000)+"个替身傀儡！");
		return 1;
	}

	command("nod "+ob->query("id"));
	command("say 我这就给你。");
	yao = new("/clone/shizhe/kuilei");
	yao->move(ob);
	ob->add("zjvip/get_kuilei",1);

	message_vision("$N给了$n一个" + yao->query("name") + "。\n",this_object(),ob);
	log_file("gift", sprintf(ob->query("id")+"在%s：领取了一个替身傀儡。\n",ctime(time())));
	return 1;
		
}

int ask_mengzi()
{
		object ob = this_player();
		object yao;

	 
	if (ob->query("zjvip/times") <1) {
		command("say 对不起，我只处理东方族人的事情！");
		return 1;
	}
	if (ob->query("zjvip/all_pay")+ob->query("gongxians")<1000) {
		command("say 对不起，你的贡献不够，不符合领取《孟子》的条件！");
		return 1;
	}

	if ( present("mengzi book", ob)) {
		command("say 你已经有了一本《孟子》了，别贪得无厌！");
		return 1;
	}

	command("nod "+ob->query("id"));
	command("say 我这就给你。");
	yao = new("/clone/shizhe/mengzi");
	yao->move(ob);
	message_vision("$N给了$n一本《" + yao->query("name") + "》。\n",this_object(),ob);
	return 1;
		
}
