// learnto.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string userid;
	object ob;
	int last_learnto,exp;

	if(!arg)
		return notify_fail("��Ҫ��˭��������\n");
	else if(sscanf(arg,"dizi %s",userid)==1)
	{
		if(!objectp(ob = find_player(userid))||!present(ob,environment(me))||ob->query("p_master/id")!=me->query("id")||!me->query("p_dizi/"+ob->query("id")))
			return notify_fail("��Ҫָ��˭����\n");
		if(!(last_learnto=me->query("p_dizi/"+ob->query("id")+"/last_learnto")))
		{
			me->set("p_dizi/"+ob->query("id")+"/last_learnto",me->query("combat_exp"));
			return notify_fail("����ʦͽ֮�侭��һ���������������Ժ�Ľ�ѧ���ȣ�����������ҪŬ����ʱ���ˣ����Ͱɣ���\n");
		}
		if((last_learnto+10)>=me->query("combat_exp"))
			return notify_fail("�����ϴν���ͽ��֮��û��ɶ���Խ�������ʱ������ָ�����ͽ���ˣ���\n");
		if(ob->query("combat_exp")>1000000)
			return notify_fail("����ͽ���Ѿ��ﵽ�˳�ʦ�ĵز����������ָ���ˣ���\n");
		exp = (me->query("combat_exp")-last_learnto)/10;
		if(exp>10000) exp = 10000;
		ob->add("combat_exp",exp);
		ob->add("potential",exp/3);
		me->set("p_dizi/"+ob->query("id")+"/last_learnto",me->query("combat_exp"));
		write("���ͽ��"HIG+ob->query("name")+NOR"�����ָ���»����"HIY+exp+NOR"�㾭���"HIY+exp/3+NOR"��Ǳ�ܡ�\n");
		tell_object(ob,"�������ʦ��"HIG+me->query("name")+NOR"��ָ���»����"HIY+exp+NOR"�㾭���"HIY+exp/3+NOR"��Ǳ�ܡ�\n");
	}
	else if(sscanf(arg,"master %s",userid)==1)
	{
		if(!objectp(ob = find_player(userid))||!present(ob,environment(me))||me->query("p_master/id")!=ob->query("id")||!ob->query("p_dizi/"+me->query("id")))
			return notify_fail("��Ҫ��˭�밲����\n");
		if(!(last_learnto=me->query("p_master/last_learnto")))
		{
			me->set("p_master/last_learnto",me->query("combat_exp"));
			return notify_fail("����ʦͽ֮�侭��һ���������������Ժ�Ľ�ѧ���ȣ�����������ҪŬ����ʱ���ˣ����Ͱɣ���\n");
		}
		if((last_learnto+20)>=me->query("combat_exp"))
			return notify_fail("��������ʦ���밲֮��û��ɶ���Խ���������ȥ�밲����ʦ���᲻����ɣ���\n");
		if(me->query("combat_exp")>1000000)
			return notify_fail("���Ѿ��ﵽ�˳�ʦ�ĵز��������ڻ�����ȥ��ʦ�ɣ���\n");
		exp = (me->query("combat_exp")-last_learnto)/20;
		if(exp>10000) exp = 10000;
		ob->add("combat_exp",exp);
		ob->add("potential",exp/3);
		me->set("p_master/last_learnto",me->query("combat_exp"));
		write("���ʦ��"HIG+ob->query("name")+NOR"���������ʮ�����⣬��Ϊ����֮����Ϊ�����������\n");
		tell_object(ob,"�㿴�����ͽ��"HIG+me->query("name")+NOR"��Ϊ�õ���������ߣ���ϲ֮�»�Ȼ��ͨ�������"HIY+exp+NOR"�㾭���"HIY+exp/3+NOR"��Ǳ�ܡ�\n");
	}
	return 1;
}

int help(object me)
{
     write(@HELP
ָ���ʽ: time

���ʦͽ֮��ľ��齻��

HELP
    );
    return 1;
}
