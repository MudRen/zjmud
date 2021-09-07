// right.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj;
	string str;
      mapping du;

	if(!arg)
		return notify_fail("��Ҫ�鿴ʲô��Ʒ��\n");
	if(!objectp(obj=present(arg,me)))
		return notify_fail("��Ҫ�鿴ʲô��Ʒ��\n");

	str = ZJOBLONG+obj->short()+"\n";
	str += "һһһһһһһһһһһһһһһһһһһһһһ\n";
	str += obj->long();
	if(obj->long()=="") return 1;
	//����Ļ�
	if(obj->query("poison_type")=="poison")
	{
		if(mapp(du=obj->query("poison")))
		{
			str += HIG"���ࡡ��: "+du["name"]+NOR"\n";
			str += HIG"��������: "+chinese_number((int)du["level"])+NOR"\n";
			str += HIG"�������ȡ�: "+chinese_number((int)du["duration"])+NOR"\n";
			str += HIG"�������ߡ�: "+du["id"]+NOR"\n";
			if(obj->query("value"))
			{
				str += YEL"���ۡ�ֵ��: "+MONEY_D->money_str((int)obj->query("value"))+NOR"\n";
			}
		}
	}
	else
	{
		if(obj->item_owner() && obj->apply_damage())
		{
			str += YEL"�������顿: "+obj->weapon_exp()+NOR" / "HIY+obj->level_max_exp(obj->weapon_level())+NOR" / "HIY+chinese_number(obj->level_now())+NOR"��\n"; 
			if(obj->query("magic/imbue_ob"))
				str += MAG"��ʥ������: ��ʥ������"+obj->query("magic/imbue_name")+"��͸"+NOR"\n";
			else if (obj->query("magic/imbue_ok"))
				str += MAG"��ʥ������: ����ȫʥ����"+NOR"\n";
			else
				str += MAG"��ʥ������: δʥ��"+NOR"\n";
			if (obj->query("magic/imbue_ok"))
				str += HIM"������͸��: �ѳ�ֽ�͸��"+NOR"\n";
			else
				str += HIM"������͸��: "+chinese_number((int)obj->query("magic/imbue"))+NOR"\n";
			str += HIR"��Ѫ���ȡ�: "+chinese_number((int)obj->query("combat/MKS")+(int)obj->query("combat/PKS"))+NOR"\n"; 
			str += HIM"��ħ������: "+chinese_number((int)obj->query("magic/power"))+NOR"\n";
		}
		else if(obj->item_owner())
		{
			str += HIY"���ȡ�����: "+chinese_number((int)obj->armor_level())+NOR"\n"; 
		}
		if(obj->query("weapon_prop/damage"))
		{
			str += HIR"����������: "+chinese_number((int)obj->query("weapon_prop/damage"))+NOR"\n";
		}
		if(obj->query("armor_prop/unarmed_damage"))
		{
			str += HIR"����������: "+chinese_number((int)obj->query("armor_prop/unarmed_damage"))+HIR"����--<ע����������Ч>\n"NOR;
		}
		if(obj->query("power"))
		{
			str += HIR"���ƻ�����: "+chinese_number((int)obj->query("power"))+NOR"\n";
		}
		if(obj->query("accuracy"))
		{
			str += HIG"����ȷ�ȡ�: "+chinese_number((int)obj->query("accuracy"))+NOR"\n";
		}
		if(obj->query("armor_prop/armor"))
		{
			str += HIG"����������: "+chinese_number((int)obj->query("armor_prop/armor"))+NOR"\n";
		}
		if(obj->query("armor_prop/warm"))
		{
			str += HIG"����ů�ȡ�: "+chinese_number((int)obj->query("armor_prop/warm"))+NOR"\n";
		}
		if(obj->query("armor_buwei"))
		{
		  str += GRN"������λ��: "+obj->query("armor_buwei")+NOR"\n";
		}
		if(obj->query("material") && !obj->item_owner())
		{
			str += GRN"���ġ��ʡ�: "+to_chinese(obj->query("material"))+NOR"\n";
		}
	
		if(obj->query("value") && !obj->item_owner() )
		{
			str += YEL"���ۡ�ֵ��: "+MONEY_D->money_str((int)obj->query("value"))+NOR"\n";
		}
		if(obj->item_owner() && obj->apply_damage())
		{
			if (me->query("can_summon/"+obj->query("id")))
			{
				str += GRN"�������⡿: "GRN"�Ѱ�\n"NOR;
			}
			else
			{
				str += GRN"�������⡿: "WHT"δ���� < Ѱ������ʦ���� > \n"NOR;
			}   
		}	 
	}
	str = replace_string(str,"\n",ZJBR);
	if(str[(strlen(str)-4)..(strlen(str)-1)]=="$br#")
		str = str[0..(strlen(str)-5)];
	str += "\n";
	write(str);
	return 1;
}

int help(object me)
{
   write( @HELP
ָ���ʽ: lookmore <something>

�鿴��Ʒ����ϸ��Ϣ��
HELP );
   return 1;
}
