#include <ansi.h>

#define MYSHOP_DIR	"/clone/vip/"

inherit F_CLEAN_UP;

mapping mtypes = ([
	"宝石类":"baoshi",
	"属性类":"attrib",
	"装备类":"weapon",
	"技能类":"skill",
	"丹药类":"medicine",
	"任务类":"job",
	"特殊类":"special",
	"限时特价":"jieri",
]);

int main(object me, string arg)
{
	string str,*all_file,file,price,type,*types;
	int fix,i,yuanbao,value;
	object ob;
	mixed today;
	int jieri,amount;

	all_file = list_dirs(MYSHOP_DIR);

	if(!sizeof(all_file))
		return notify_fail("商城中暂无商品出售。\n");

	today = localtime(time());
	if((today[4]+1)==1 && today[3]>=1 && today[3]<=3)
		fix = 80;
	else fix = 100;

	if (! arg)
	{
		str = ZJOBLONG"你目前有"+me->query("yuanbao")+"元宝，请选择您想购买的道具：\n"ZJOBACTS2+ZJMENUF(4,4,8,30);
		today = localtime(time());
//		if(jieri == 1)
//			str += "限时特价:myshop type 限时特价"ZJSEP;
		str += "特殊道具:myshop type 特殊类"ZJSEP;
		str += "宝石商店:myshop type 宝石类"ZJSEP;
		for(i=0;i<sizeof(all_file);i++)
		{
			file = MYSHOP_DIR+all_file[i];
			if(file_size(file)<0) continue;
			if(file->query("no_shop")) continue;
			yuanbao = file->query("yuanbao");
			if(yuanbao)
			{
				yuanbao = yuanbao*fix/100;
				if(yuanbao<1) yuanbao = 1;
			}
			price = yuanbao?(yuanbao+"元宝"):(MONEY_D->money_str(file->query("value")));
			str += sprintf("%s"ZJBR"%s:myshop look %s"ZJSEP,file->query("name"),price,file);
		}
		write(str+"\n");
		return 1;
	}
	else if(arg=="type")
	{
		str = ZJOBLONG"你目前有"+me->query("yuanbao")+"元宝，请选择您想购买的道具类别：\n"ZJOBACTS2+ZJMENUF(4,4,8,30);
		types = sort_array(keys(mtypes),(:strcmp:));
		for(i=0;i<sizeof(types);i++)
		{
			str += sprintf("%s:myshop type %s"ZJSEP,types[i],types[i]);
		}
		write(str+"\n");
		return 1;
	}
	else if (sscanf(arg,"type %s",type)==1)
	{
		if(!mtypes[type])
			return notify_fail("商城中暂无"HIG+type+NOR"类商品出售。\n");
		all_file = list_dirs(MYSHOP_DIR+mtypes[type]+"/");
		if(!sizeof(all_file))
			return notify_fail("商城中暂无"HIG+type+NOR"类商品出售。\n");
		if(type == "限时特价")
			str = ZJOBLONG"你目前有"+me->query("yuanbao")+"元宝，请选择您想购买的"HIG+type+NOR"类道具："ZJBR HIR"注意：本类道具为绑定道具！"NOR"\n"ZJOBACTS2+ZJMENUF(4,4,8,30);
		else
			str = ZJOBLONG"你目前有"+me->query("yuanbao")+"元宝，请选择您想购买的"HIG+type+NOR"类道具：\n"ZJOBACTS2+ZJMENUF(4,4,8,30);
		for(i=0;i<sizeof(all_file);i++)
		{
			file = MYSHOP_DIR+mtypes[type]+"/"+all_file[i];
			if(file_size(file)<0) continue;
			if(file->query("no_shop")) continue;
			yuanbao = file->query("yuanbao");
			price = yuanbao?(yuanbao+"元宝"):(MONEY_D->money_str(file->query("value")));
			str += sprintf("%s"ZJBR"%s:myshop look %s"ZJSEP,file->query("name"),price,file);
		}
		write(str+"\n");
		return 1;
	}
	else if (sscanf(arg,"look %s",file)==1)
	{
		yuanbao = file->query("yuanbao");
			if(yuanbao)
			{
				yuanbao = yuanbao*fix/100;
				if(yuanbao<1) yuanbao = 1;
			}
		price = yuanbao?(yuanbao+"元宝"):(MONEY_D->money_str(file->query("value")));
		str = ZJOBLONG+"【"+file->query("name")+"】　　价格："+price+NOR+ZJBR"一一一一一一一一一一一一一一一一一一一一一一一"ZJBR;
		str += file->long();
		str += ZJOBACTS2+ZJMENUF(4,4,10,28);
		str += "购买1个:myshop buy 1 "+file+ZJSEP"批量购买:myshop buy "+file+"\n";
		write(str+"\n");
		return 1;
	}
	else if (sscanf(arg,"buy %s",file)==1)
	{
		if (sscanf(file, "%d %s", amount, file) != 2)
		{
			if(file_size(file)<0||strsrch(file,MYSHOP_DIR)!=0)
				return notify_fail(HIM"没有这个道具！！"NOR"\n");

			write(INPUTTXT("你想买多少个"+file->query("name")+"？"ZJBR"请确认你的背包空间足够。","myshop buy $txt# "+file)+"\n");
			return 1;
		}

		if(file_size(file)<0||strsrch(file,MYSHOP_DIR)!=0)
			return notify_fail(HIM"没有这个道具！！"NOR"\n");

		if(file->query("no_shop"))
			return notify_fail(HIM"已下架商品，无法购买！！"NOR"\n");
		if(file->query("jieri")&&!jieri)
			return notify_fail(HIM"特殊节日商品，非开放时间无法购买！！"NOR"\n");
		if(amount<1)
			return notify_fail(HIM"你要买多少个？？"NOR"\n");
		if(amount>999)
			return notify_fail(HIM"你要买多少个？？"NOR"\n");
		if(!file->query_amount()&&amount>10)
			return notify_fail(HIM"不可叠加物品一次最多买10个！！"NOR"\n");

		if(file->query("max_buy"))
		{
			if(me->query("buy_max/"+file->query("id"))+amount>file->query("max_buy"))
				return notify_fail(HIM"限量购买道具，你还能购买"+(file->query("max_buy")-me->query("buy_max/"+file->query("id")))+"个！！"NOR"\n");
		}
		yuanbao = file->query("yuanbao");
			if(yuanbao)
			{
				yuanbao = yuanbao*fix/100;
				if(yuanbao<1) yuanbao = 1;
			}
		if(!value=file->query("base_value"))
			value = file->query("value");
		if(!yuanbao&&!value)
			return notify_fail(HIM"购买失败！！"NOR"\n");

		if(yuanbao)
		{
			if(!me->query("yuanbao")||me->query("yuanbao")<(yuanbao*amount))
				return notify_fail(HIM"你的元宝不足，请充值！！"NOR"\n");
			me->add("yuanbao",-yuanbao*amount);
			log_file("pay/myshop", sprintf("%s:%s(%s)消费%d元宝，从随身商城购买%d个%s(%s)。\n",
				ctime(time()),me->query("name"),me->query("id"),yuanbao*amount,amount,file->query("name"),file->query("id")));
			me->add("zjvip/yuanbao_used",yuanbao*amount);
		}
		else
		{
			if(!MONEY_D->player_pay(me, value * amount))
				return notify_fail(HIM"你的钱没那么多了！！"NOR"\n");
			log_file("pay/myshop2", sprintf("%s:%s(%s)消费%s，从随身商城购买%d个%s。\n",
				ctime(time()),me->query("name"),me->query("id"),MONEY_D->money_str(value*amount),amount,file->query("name")));
		}
		if(file->query_amount())
		{
			ob = new(file);
			ob->set_amount(amount);
			write("你从商城中成功购买到"+ob->short()+"。"NOR"\n");
			ob->move(me,1);
		}
		else
		{
			for(i=0;i<amount;i++)
			{
				ob = new(file);
				ob->move(me,1);
			}
			write("你从商城中成功购买到"+amount+ob->query("unit")+ob->short()+"。"NOR"\n");
		}
		if(file->query("max_buy"))
		{
			me->add("buy_max/"+file->query("id"),amount);
		}
		return 1;
	}
	else
		return notify_fail(HIM"你想干什么？？"NOR"\n");

	return 1;
}

int help(object me)
{
     write(@HELP

随身商城。

HELP
    );
    return 1;
}
