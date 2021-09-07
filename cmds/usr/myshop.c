#include <ansi.h>

#define MYSHOP_DIR	"/clone/vip/"

inherit F_CLEAN_UP;

mapping mtypes = ([
	"��ʯ��":"baoshi",
	"������":"attrib",
	"װ����":"weapon",
	"������":"skill",
	"��ҩ��":"medicine",
	"������":"job",
	"������":"special",
	"��ʱ�ؼ�":"jieri",
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
		return notify_fail("�̳���������Ʒ���ۡ�\n");

	today = localtime(time());
	if((today[4]+1)==1 && today[3]>=1 && today[3]<=3)
		fix = 80;
	else fix = 100;

	if (! arg)
	{
		str = ZJOBLONG"��Ŀǰ��"+me->query("yuanbao")+"Ԫ������ѡ�����빺��ĵ��ߣ�\n"ZJOBACTS2+ZJMENUF(4,4,8,30);
		today = localtime(time());
//		if(jieri == 1)
//			str += "��ʱ�ؼ�:myshop type ��ʱ�ؼ�"ZJSEP;
		str += "�������:myshop type ������"ZJSEP;
		str += "��ʯ�̵�:myshop type ��ʯ��"ZJSEP;
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
			price = yuanbao?(yuanbao+"Ԫ��"):(MONEY_D->money_str(file->query("value")));
			str += sprintf("%s"ZJBR"%s:myshop look %s"ZJSEP,file->query("name"),price,file);
		}
		write(str+"\n");
		return 1;
	}
	else if(arg=="type")
	{
		str = ZJOBLONG"��Ŀǰ��"+me->query("yuanbao")+"Ԫ������ѡ�����빺��ĵ������\n"ZJOBACTS2+ZJMENUF(4,4,8,30);
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
			return notify_fail("�̳�������"HIG+type+NOR"����Ʒ���ۡ�\n");
		all_file = list_dirs(MYSHOP_DIR+mtypes[type]+"/");
		if(!sizeof(all_file))
			return notify_fail("�̳�������"HIG+type+NOR"����Ʒ���ۡ�\n");
		if(type == "��ʱ�ؼ�")
			str = ZJOBLONG"��Ŀǰ��"+me->query("yuanbao")+"Ԫ������ѡ�����빺���"HIG+type+NOR"����ߣ�"ZJBR HIR"ע�⣺�������Ϊ�󶨵��ߣ�"NOR"\n"ZJOBACTS2+ZJMENUF(4,4,8,30);
		else
			str = ZJOBLONG"��Ŀǰ��"+me->query("yuanbao")+"Ԫ������ѡ�����빺���"HIG+type+NOR"����ߣ�\n"ZJOBACTS2+ZJMENUF(4,4,8,30);
		for(i=0;i<sizeof(all_file);i++)
		{
			file = MYSHOP_DIR+mtypes[type]+"/"+all_file[i];
			if(file_size(file)<0) continue;
			if(file->query("no_shop")) continue;
			yuanbao = file->query("yuanbao");
			price = yuanbao?(yuanbao+"Ԫ��"):(MONEY_D->money_str(file->query("value")));
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
		price = yuanbao?(yuanbao+"Ԫ��"):(MONEY_D->money_str(file->query("value")));
		str = ZJOBLONG+"��"+file->query("name")+"�������۸�"+price+NOR+ZJBR"һһһһһһһһһһһһһһһһһһһһһһһ"ZJBR;
		str += file->long();
		str += ZJOBACTS2+ZJMENUF(4,4,10,28);
		str += "����1��:myshop buy 1 "+file+ZJSEP"��������:myshop buy "+file+"\n";
		write(str+"\n");
		return 1;
	}
	else if (sscanf(arg,"buy %s",file)==1)
	{
		if (sscanf(file, "%d %s", amount, file) != 2)
		{
			if(file_size(file)<0||strsrch(file,MYSHOP_DIR)!=0)
				return notify_fail(HIM"û��������ߣ���"NOR"\n");

			write(INPUTTXT("��������ٸ�"+file->query("name")+"��"ZJBR"��ȷ����ı����ռ��㹻��","myshop buy $txt# "+file)+"\n");
			return 1;
		}

		if(file_size(file)<0||strsrch(file,MYSHOP_DIR)!=0)
			return notify_fail(HIM"û��������ߣ���"NOR"\n");

		if(file->query("no_shop"))
			return notify_fail(HIM"���¼���Ʒ���޷����򣡣�"NOR"\n");
		if(file->query("jieri")&&!jieri)
			return notify_fail(HIM"���������Ʒ���ǿ���ʱ���޷����򣡣�"NOR"\n");
		if(amount<1)
			return notify_fail(HIM"��Ҫ����ٸ�����"NOR"\n");
		if(amount>999)
			return notify_fail(HIM"��Ҫ����ٸ�����"NOR"\n");
		if(!file->query_amount()&&amount>10)
			return notify_fail(HIM"���ɵ�����Ʒһ�������10������"NOR"\n");

		if(file->query("max_buy"))
		{
			if(me->query("buy_max/"+file->query("id"))+amount>file->query("max_buy"))
				return notify_fail(HIM"����������ߣ��㻹�ܹ���"+(file->query("max_buy")-me->query("buy_max/"+file->query("id")))+"������"NOR"\n");
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
			return notify_fail(HIM"����ʧ�ܣ���"NOR"\n");

		if(yuanbao)
		{
			if(!me->query("yuanbao")||me->query("yuanbao")<(yuanbao*amount))
				return notify_fail(HIM"���Ԫ�����㣬���ֵ����"NOR"\n");
			me->add("yuanbao",-yuanbao*amount);
			log_file("pay/myshop", sprintf("%s:%s(%s)����%dԪ�����������̳ǹ���%d��%s(%s)��\n",
				ctime(time()),me->query("name"),me->query("id"),yuanbao*amount,amount,file->query("name"),file->query("id")));
			me->add("zjvip/yuanbao_used",yuanbao*amount);
		}
		else
		{
			if(!MONEY_D->player_pay(me, value * amount))
				return notify_fail(HIM"���Ǯû��ô���ˣ���"NOR"\n");
			log_file("pay/myshop2", sprintf("%s:%s(%s)����%s���������̳ǹ���%d��%s��\n",
				ctime(time()),me->query("name"),me->query("id"),MONEY_D->money_str(value*amount),amount,file->query("name")));
		}
		if(file->query_amount())
		{
			ob = new(file);
			ob->set_amount(amount);
			write("����̳��гɹ�����"+ob->short()+"��"NOR"\n");
			ob->move(me,1);
		}
		else
		{
			for(i=0;i<amount;i++)
			{
				ob = new(file);
				ob->move(me,1);
			}
			write("����̳��гɹ�����"+amount+ob->query("unit")+ob->short()+"��"NOR"\n");
		}
		if(file->query("max_buy"))
		{
			me->add("buy_max/"+file->query("id"),amount);
		}
		return 1;
	}
	else
		return notify_fail(HIM"�����ʲô����"NOR"\n");

	return 1;
}

int help(object me)
{
     write(@HELP

�����̳ǡ�

HELP
    );
    return 1;
}
