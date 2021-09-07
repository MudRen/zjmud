// level.c 
#pragma save_binary
#include <dbase.h>
#include <ansi.h>;

//����������Ҫ���ľ���
int level_max_exp(object me)
{
	int max_exp,lvl;
	lvl=(int)me->query("level");
	if(lvl<5)
		max_exp=lvl*10+1000;
	if(lvl<10 && lvl>4)
		max_exp=lvl*15+20000;
	if(lvl<20 && lvl>9)
		max_exp=lvl*20+50000;
	if(lvl<30 && lvl>19)
		max_exp=lvl*30+100000;
	if(lvl<40 && lvl>29)
		max_exp=lvl*40+200000;
	if(lvl<50 && lvl>39)
		max_exp=lvl*50+300000;
	if(lvl<59 && lvl>49)
		max_exp=lvl*100+500000;
	if(lvl<69 && lvl>58)
		max_exp=lvl*1000+1000000;
	if(lvl<79 && lvl>68)
		max_exp=lvl*1000+2000000;
	if(lvl<89 && lvl>78)
		max_exp=lvl*1000+3000000;
	if(lvl<99 && lvl>88)
		max_exp=lvl*1000+4000000;
	if(lvl<109 && lvl>98)
		max_exp=lvl*1000+5000000;
	if(lvl>=109)
		max_exp=lvl*5000+500000000;
	return max_exp;
}
//�����ж�--������������ʵս���顣
varargs void improve_level(object me)
{
	int exp_num;
	exp_num=me->query("combat_exp");
	if(exp_num >= level_max_exp(me))
	{
		tell_object(me, HIG"ֻ��һ��Ѥ���Ĺ�â������������  "NOR"\n");
		printf(HIC"��"HIY"��������������������������������������������������������"HIC"��"NOR"\n");
		tell_object(me, HIR" ��ϲ:"+NOR" ��� "+YEL+"��Level��: "HIY" ������ ��"+NOR"��"+HIG"    ��: +5  ��: +3 "+NOR+"\n");
		me->add("max_neili",5); 
		me->add("max_jingli",3);     
		if(exp_num>=level_max_exp(me))
		{
			me->add("level",1);
			if((int)me->query("level")%3==0)
			{
				me->add("skill_point",1);
				write(HIG"��ϲ��  <���ø��Ӽ��ܵ�> + 1 "NOR"\n");
			}
			if((int)me->query("level")%10==0)
			{
				me->add("tianfu_point",1);
				write(HIG"��ϲ��  <���ø����츳��> + 1 "NOR"\n");
			}
		}
		else
		{
			me->set("combat_exp",0);
			me->add("level",1);
		}
		printf(HIC"��"HIY"��������������������������������������������������������"HIC"��"NOR"\n");
	}  
	else
	{
		write(HIR"���ʵս���鲻���������ȼ�!"NOR"\n");
	}   
}
//�����츳����
varargs void up_tianfu(object me)
{
	int i;
	if((int)me->query("tianfu_point"))
	{
		i=random(400);
		write(HIY"�㽫һ�㱦��ġ��츳�㡹��ע�������壬��ʱһƬ���������"NOR"\n");
		if(i<=100) 
		{
			me->add("str",1) ;
			write(HIR"��ϲ��   "HIG"��ġ����������������!"NOR"\n");
		}
		if(i>100 && i<=200) 
		{
			me->add("int",1) ;
			write(HIR"��ϲ��   "HIG"��ġ��������ԡ�������!"NOR"\n");
		}
		if(i>200 && i<=300) 
		{
			me->add("con",1) ;
			write(HIR"��ϲ��   "HIG" ��ġ�������ǡ�������!"NOR"\n");
		}
		if(i>300) 
		{
			me->add("dex",1) ;
			write(HIR"��ϲ��   "HIG"��ġ���������������!"NOR"\n");
		}
		me->add("tianfu_point",-1);
	}
	else
	{
		write(HIR"����츳�㲻����������������! "NOR"\n");
	}
}

//�������װ�������⼼�ܵȼ�
varargs void up_skills(object me)
{
	int skill_point;
	mixed me_skills;
	mixed sky_skills;
	mapping skills;
	int i;
	int exp,level;
	me_skills=me->query_skill_map();
	if(sizeof(me_skills))
	{
		if((int)me->query("skill_point"))
		{
			i=random(sizeof(me_skills));
			sky_skills=keys(me_skills);
			skills=me->query_skills();
			exp=me->query("combat_exp");
			level=skills[me_skills[sky_skills[i]]];
			if(level*level*level/10 < exp)
			{
				skills[me_skills[sky_skills[i]]]++;
				tell_object(me, "��������һ�����ܵ㣬ֻ��һ��"HIM"��ɫ"NOR"�Ĺ�â������������������  "NOR"\n");
				printf(HIC"��"HIY"��������������������������������������������������������"HIC"��"NOR"\n");
				tell_object(me,HIR"  ��ϲ��"NOR" ��������书"MAG" [ "+to_chinese(me_skills[sky_skills[i]])+" ]"NOR" ������ "HIM"��"NOR" ."NOR"\n");
				printf(HIC"��"HIY"��������������������������������������������������������"HIC"��"NOR"\n");
				me->add("skill_point",-1);
			}
			else
			{
				write(HIR"��ľ��鲻����֧�ּ��ܵ�����!"NOR"\n");
			}
		}
		else
		{
			write(HIR"��ļ��ܵ㲻��!"NOR"\n");
		}
	}
	else
	{
		write(HIR"���ܵ�ֻ������װ���ŵ������书!"NOR"\n");
	}
}

