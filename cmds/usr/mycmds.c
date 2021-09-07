// time.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int i,bt;
	string str,cmd;

	if(!arg)
	{
		write(ZJBTSET"b12:"HIG"常用"ZJBR"指令"NOR":mycmds ofen"ZJSEP"b13:"HIY"技能"ZJBR"相关"NOR":mycmds skill"ZJSEP"b14:"HIR"战斗"ZJBR"相关"NOR":mycmds fight"ZJSEP
			"b15:"HIM"任务"ZJBR"相关"NOR":mycmds quest"ZJSEP"b16:"HIW"游戏"ZJBR"指南"NOR":mycmds help"ZJSEP"b17:"HIC"频道"ZJBR"交流"NOR":liaotian"+"\n");
		write(ZJTTMENU" 飞行 :help mapb"ZJSEP" 附近 :map view\n");
	}
	else if(arg=="ofen")
		write(ZJBTSET"b1:查看"ZJBR"背包:i"ZJSEP"b2:综合"ZJBR"属性:score"ZJSEP"b3:健康"ZJBR"状态:hp"
			ZJSEP"b4:查看"ZJBR"装备:arm"ZJSEP"b5:角色↑"ZJBR"家园↑:uplv"ZJSEP"b6:地图"ZJBR"相关:help mapb"ZJSEP"b8:帮会"ZJBR"相关:banghui"
			ZJSEP"b7:队伍"ZJBR"信息"NOR":team"ZJSEP"b9:"YEL"随身"ZJBR"商城"NOR":myshop"ZJSEP"b10:玩家"ZJBR"排行:tops"ZJSEP"b11:乘雕"ZJBR"飞行:help mapb"+"\n");
	else if(arg=="skill")
		write(ZJBTSET"b1:查看"ZJBR"技能:skills"ZJSEP"b2:日常"ZJBR"练功:help liangong"ZJSEP"b3:内力"ZJBR"回血:exert recover"
			ZJSEP"b4:内力"ZJBR"回精:exert regenerate"ZJSEP"b5:内力"ZJBR"疗伤:exert heal"ZJSEP"b6:内力"ZJBR"疗神:exert inspire"
			ZJSEP"b7:内力"ZJBR"疗疾:exert dispel"ZJSEP"b8:内功"ZJBR"加力:enforce"ZJSEP"b9:战斗"ZJBR"信息:set combatd"ZJSEP"b10:暂未"ZJBR"设定:look"ZJSEP"b11:乘雕"ZJBR"飞行:help mapb"+"\n");
	else if(arg=="fight")
	{
		str = ZJBTSET;
		for(i=1;i<11;i++)
		{
			if(cmd=me->query("mycmds/fight/b"+i))
				str += "b"+i+":"+cmd;
			else
				str += "b"+i+":点击"ZJBR"选择"+i+":mycmds reset "+i;
			str += ZJSEP;
		}
		str += "b11:重新"ZJBR"定义:mycmds reset";
		write(str+"\n");
	}
	else if(arg=="quest")
		write(ZJBTSET"b1:查看"ZJBR"任务:quest"ZJSEP"b2:使用"ZJBR"八卦:use ba gua"ZJSEP"b3:中止"ZJBR"挂机:unset sign1"
			ZJSEP"b4:暂未"ZJBR"设定:look"ZJSEP"b5:暂未"ZJBR"设定:look"ZJSEP"b7:充值"ZJBR"说明:help pay"ZJSEP"b8:会员"ZJBR"福利:help vip"
			ZJSEP"b6:地图"ZJBR"相关:help mapb"ZJSEP"b9:搜索"ZJBR"本地:search"ZJSEP"b10:随身"ZJBR"购买:myshop"ZJSEP"b11:乘雕"ZJBR"飞行:help mapb"+"\n");
	else if(arg=="help")
		write(ZJBTSET"b1:更新"ZJBR"公告:help anews"ZJSEP"b2:"HIG"新手"ZJBR"指南"NOR":help newbie"ZJSEP"b3:基本"ZJBR"系统:help"ZJSEP"b4:门派"ZJBR"世家:help menpai"
			ZJSEP"b5:游戏"ZJBR"特色:help feature"ZJSEP"b6:技能"ZJBR"介绍:help skills"ZJSEP"b7:充值"ZJBR"说明:help pay"ZJSEP"b8:会员"ZJBR"福利:help vip"
			ZJSEP"b9:搜索"ZJBR"本地:search"ZJSEP"b10:自杀"ZJBR"重来:suicide"ZJSEP"b11:乘雕"ZJBR"飞行:help mapb"+"\n");
	else if(arg=="reset")
	{
		str = ZJBTSET;
		for(i=1;i<11;i++)
		{
			str += "b"+i+":点击"ZJBR"选择"+i+":mycmds reset "+i;
			str += ZJSEP;
		}
		str += "b11:返回:mycmds fight";
		write(str+"\n");
		write(ZJTMPSAY"请点击你想要定义的按钮选择新功能。\n");
	}
	else if(sscanf(arg,"reset %d %s",bt,cmd)==2)
	{
		string a,b;

		if(bt<1||bt>10)
			return notify_fail(ZJOBLONG"没有这个按钮。。。\n");
		if(cmd == "自定义")
		{
			write(INPUTTXT("请输入自定义字串：标题:命令(查看:look)","mycmds reset "+bt+" $txt#")+"\n");
			return 1;
		}
		cmd = replace_string(cmd,"：",":");
		cmd = replace_string(cmd,"#E",ESA);
		cmd = replace_string(cmd,"/",ZJBR);
		cmd = replace_string(cmd,"\n",ZJBR);
		if(sscanf(cmd,"%s:%s",a,b)!=2)
			return notify_fail(HIR"格式错误，请重新定义！"NOR"\n");
		me->set("mycmds/fight/b"+bt,cmd);
		write(ZJBTSET"b"+bt+":"+cmd+"\n");
	}
	else if(sscanf(arg,"reset %d",bt)==1)
	{
		mapping smap, pmap, pfms,skips;
		string force_ski,weapon_ski,*pfm,ski_type,uski_type;
		int k,flag;
		string msg,*valid_types,*skis,*cmdd;
		object weapon;

		if(bt<1||bt>10)
			return notify_fail(ZJOBLONG"没有这个按钮。。。\n");

		valid_types = ({"finger","hand","cuff","claw","strike","unarmed"});
		skips = ([]);
		if(!smap = me->query_skill_map()) smap=([]);
		if(!pmap = me->query_skill_prepare()) pmap=([]);
		msg = "";

		if(objectp(weapon = me->query_temp("weapon")))
			ski_type = weapon->query("skill_type");

		if(force_ski=smap["force"])
		{
			pfms = SKILL_D(force_ski)->query_pfm("force");
			if(mapp(pfms)&&pfms!=([]))
			{
				pfm = sort_array(keys(pfms), (: strcmp :) );
				for(i=0;i<sizeof(pfm);i++)
				{
					cmdd = explode(pfms[pfm[i]],":");
					msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"："+ cmdd[1]+" force."+pfm[i]+ZJSEP;
					skips[force_ski+pfm[i]]=1;
				}
			}
		}

		if(force_ski=smap["xinfa"])
		{
			pfms = SKILL_D(force_ski)->query_pfm("xinfa");
			if(mapp(pfms)&&pfms!=([]))
			{
				pfm = sort_array(keys(pfms), (: strcmp :) );
				for(i=0;i<sizeof(pfm);i++)
				{
					if(skips[force_ski+pfm[i]]) continue;
					cmdd = explode(pfms[pfm[i]],":");
					msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"："+ cmdd[1]+" xinfa."+pfm[i]+ZJSEP;
					skips[force_ski+pfm[i]]=1;
				}
			}
		}

		if(force_ski=smap["parry"])
		{
			pfms = SKILL_D(force_ski)->query_pfm("parry");
			if(mapp(pfms)&&pfms!=([]))
			{
				pfm = sort_array(keys(pfms), (: strcmp :) );
				for(i=0;i<sizeof(pfm);i++)
				{
					if(skips[force_ski+pfm[i]]) continue;
					cmdd = explode(pfms[pfm[i]],":");
					msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"："+ cmdd[1]+" parry."+pfm[i]+ZJSEP;
					skips[force_ski+pfm[i]]=1;
				}
			}
		}

		if(force_ski=smap["dodge"])
		{
			pfms = SKILL_D(force_ski)->query_pfm("dodge");
			if(mapp(pfms)&&pfms!=([]))
			{
				pfm = sort_array(keys(pfms), (: strcmp :) );
				for(i=0;i<sizeof(pfm);i++)
				{
					if(skips[force_ski+pfm[i]]) continue;
					cmdd = explode(pfms[pfm[i]],":");
					msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"："+ cmdd[1]+" dodge."+pfm[i]+ZJSEP;
					skips[force_ski+pfm[i]]=1;
				}
			}
		}

		if(objectp(weapon))
		{
			if(stringp(weapon_ski=smap[ski_type]))
			{
				pfms = SKILL_D(weapon_ski)->query_pfm(ski_type);
				if(mapp(pfms)&&pfms!=([]))
				{
					pfm = sort_array(keys(pfms), (: strcmp :) );
					for(i=0;i<sizeof(pfm);i++)
					{
						if(skips[weapon_ski+pfm[i]]) continue;
						cmdd = explode(pfms[pfm[i]],":");
						msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"："+ cmdd[1]+" "+ski_type+"."+pfm[i]+ZJSEP;
						skips[weapon_ski+pfm[i]] = 1;
					}
				}
			}
		}
		else if(!objectp(weapon))
		{
			if(mapp(pmap)&&pmap!=([]))
			{//首先推送准备技能
				skis = sort_array(keys(pmap), (: strcmp :) );
				for(k=0;k<sizeof(skis);k++)
				{
					if(skips[pmap[skis[k]]]) continue;
					pfms = SKILL_D(pmap[skis[k]])->query_pfm(skis[k]);
					if(mapp(pfms)&&pfms!=([]))
					{
						pfm = sort_array(keys(pfms), (: strcmp :) );
						for(i=0;i<sizeof(pfm);i++)
						{
							if(skips[pmap[skis[k]]+pfm[i]]) continue;
							cmdd = explode(pfms[pfm[i]],":");
							msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"："+ cmdd[1]+" "+skis[k]+"."+pfm[i]+ZJSEP;
							skips[pmap[skis[k]]+pfm[i]] = 1;
						}
					}
				}
			}

			skis = sort_array(keys(smap), (: strcmp :) );
			for(k=0;k<sizeof(skis);k++)
			{
				flag = 1;
				for(i=0;i<sizeof(valid_types);i++)
				{
					if(SKILL_D(smap[skis[k]])->valid_enable(valid_types[i]))
					{
						uski_type = valid_types[i];
						flag = 2;
					}
				}
				if(!skips[smap[skis[k]]]&&flag==2)
				{
					pfms = SKILL_D(smap[skis[k]])->query_pfm(uski_type);
					if(mapp(pfms)&&pfms!=([]))
					{
						pfm = sort_array(keys(pfms), (: strcmp :) );
						for(i=0;i<sizeof(pfm);i++)
						{
							if(skips[smap[skis[k]]+pfm[i]]) continue;
							cmdd = explode(pfms[pfm[i]],":");
							msg += cmdd[0] + ":mycmds reset "+ bt+" " +replace_string(cmdd[0],ESA,"#E")+"："+ cmdd[1]+" "+skis[k]+"."+pfm[i]+ZJSEP;
							skips[smap[skis[k]]+pfm[i]] = 1;
						}
					}
				}
			}
		}
		write(ZJOBLONG"你想设定按钮"HIG+chinese_number(bt)+NOR"为什么功能？\n"ZJOBACTS2+ZJMENUF(5,5,8,30)
			+msg
			+"拉弓"ZJBR"射箭:mycmds reset "+bt+" 拉弓"ZJBR"射箭：shot"ZJSEP
			+"内力"ZJBR"回气:mycmds reset "+bt+" 内力"ZJBR"回气：exert recover"ZJSEP
			+"内力"ZJBR"回精:mycmds reset "+bt+" 内力"ZJBR"回精：exert regenerate"ZJSEP
		      +"内力"ZJBR"疗伤:mycmds reset "+bt+" 内力"ZJBR"疗伤：exert heal"ZJSEP
			+"内力"ZJBR"疗疾:mycmds reset "+bt+" 内力"ZJBR"疗疾：exert dispel"ZJSEP
			+"释放"ZJBR"怒气:mycmds reset "+bt+" 释放"ZJBR"怒气：burning"ZJSEP
			+"吃护"ZJBR"心丹:mycmds reset "+bt+" 吃护"ZJBR"心丹：use huxin dan"ZJSEP
			+"绝技"ZJBR"一:mycmds reset "+bt+" 绝技"ZJBR"一：aa"ZJSEP
			+"绝技"ZJBR"二:mycmds reset "+bt+" 绝技"ZJBR"二：bb"ZJSEP
			+"绝技"ZJBR"三:mycmds reset "+bt+" 绝技"ZJBR"三：cc"ZJSEP
			+"\n");
	}
	return 1;
}

int help(object me)
{
     write(@HELP

这个指令让设定游戏默认的自定义按钮。

HELP
    );
    return 1;
}
