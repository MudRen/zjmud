// who.c
#include <ansi.h>
#include <net/dns.h>
#include <mudlib.h>
#include <tomud.h>
#define ENGLISH_MUD_NAME INTERMUD_MUD_NAME
inherit F_CLEAN_UP;

void create();
nosave int busy=0;

void create() { seteuid(getuid()); }

int sort_exp(string user1,string user2)
{
	return (int)TOP_D->query_user(user2+"/combat_exp")-(int)TOP_D->query_user(user1+"/combat_exp");
}

int sort_gold(string user1,string user2)
{
	return (int)TOP_D->query_user(user2+"/gold")-(int)TOP_D->query_user(user1+"/gold");
}

int sort_pay(string user1,string user2)
{
	return (int)TOP_D->query_user(user2+"/all_pay")-(int)TOP_D->query_user(user1+"/all_pay");
}

int sort_per(string user1,string user2)
{
	return (int)TOP_D->query_user(user2+"/per")-(int)TOP_D->query_user(user1+"/per");
}

int sort_PKS(string user1,string user2)
{
	return (int)TOP_D->query_user(user2+"/PKS")-(int)TOP_D->query_user(user1+"/PKS");
}

int sort_shimen(string user1,string user2)
{
	int m1=0,m2=0;
	if(user1 == "player")
		m1 = TOP_D->query_user(user1+"/shimen")/7;
	else
		m1 = TOP_D->query_user(user1+"/shimen");

	if(user2 == "player")
		m2 = TOP_D->query_user(user2+"/shimen")/7;
	else
		m2 = TOP_D->query_user(user2+"/shimen");

	return m2-m1;
}

mixed main(object me, string arg, int remote)
{
	string *list,*text,str;
	object *ob;
	int page,i,j,all,k,m;
	string type,name;
	string *all_users;

	if(!arg)
	{
		if (SECURITY_D->valid_grant(me, "(admin)"))
			write(ZJOBLONG"��ѡ���������ͣ�\n"ZJOBACTS2+ZJMENUF(4,4,9,30)+"��Ϊ��:tops ��Ϊ"ZJSEP"��ò��:tops ��ò"ZJSEP
				"�Ƹ���:tops �Ƹ�"ZJSEP"ɱ�ְ�:tops ɱ��"ZJSEP"ʦ�Ű�:tops ʦ��"ZJSEP"��ֵ��:tops ��ֵ\n");
		else
			write(ZJOBLONG"��ѡ���������ͣ�\n"ZJOBACTS2+ZJMENUF(4,4,9,30)+"��Ϊ��:tops ��Ϊ"ZJSEP"��ò��:tops ��ò"ZJSEP
				"�Ƹ���:tops �Ƹ�"ZJSEP"ɱ�ְ�:tops ɱ��"ZJSEP"ʦ�Ű�:tops ʦ��\n");
		return 1;
	}
	else if( sscanf(arg,"%s %d",type,page)!=2 )
	{
		type = arg;
		page = 1;
	}

	if(type!="��Ϊ"&&type!="��ò"&&type!="�Ƹ�"&&type!="ɱ��"&&type!="ʦ��"&&type!="��ֵ")
		return notify_fail("����"+type+"�����У�����\n");

	all_users = TOP_D->all_users();
	if(!all_users)
		return notify_fail("�����������ݣ�����\n");
	k = 0;

	if(type=="�Ƹ�")
	{
		reset_eval_cost();
		all_users = filter_array(all_users,(: TOP_D->query_user($1+"/gold")>10 :));
		if(!sizeof(all_users))
			return notify_fail("����"+type+"�������ݣ�����\n");
		all_users = sort_array(all_users, (: sort_gold :) );
		text = ({});
		for(i=0;i<sizeof(all_users);i++)
		{
			text += ({ GRN"��"+(i+1)+"�� - "+TOP_D->get_name(all_users[i])+NOR+ZJBR+YEL+"�Ƹ���"+TOP_D->query_user(all_users[i]+"/gold")+NOR":look "+all_users[i] });
//			text += ({ GRN"��"+(i+1)+"�� - "+all_users[i]+NOR+ZJBR+YEL+"�Ƹ���"+TOP_D->query_user(all_users[i]+"/gold")+NOR":look" });
		}
	}
	else if(type=="��ֵ")
	{
		reset_eval_cost();
		if (! SECURITY_D->valid_grant(me, "(admin)"))
			return notify_fail("����Ȩ�鿴��ֵ���У�\n");

		all_users = filter_array(all_users,(: TOP_D->query_user($1+"/all_pay")>10 :));
		if(!sizeof(all_users))
			return notify_fail("����"+type+"�������ݣ�����\n");
		all_users = sort_array(all_users, (: sort_pay :) );
		text = ({});
		for(i=0;i<sizeof(all_users);i++)
		{
			text += ({ GRN"��"+(i+1)+"�� - "+TOP_D->get_name(all_users[i])+NOR+ZJBR+YEL+"��ֵ��"+TOP_D->query_user(all_users[i]+"/all_pay")+NOR":look "+all_users[i] });
//			text += ({ GRN"��"+(i+1)+"�� - "+all_users[i]+NOR+ZJBR+YEL+"��ֵ��"+TOP_D->query_user(all_users[i]+"/all_pay")+NOR":look "+all_users[i] });
		}
	}
	else if(type=="��ò")
	{
		reset_eval_cost();
		all_users = filter_array(all_users,(: TOP_D->query_user($1+"/per")>10 :));
		if(!sizeof(all_users))
			return notify_fail("����"+type+"�������ݣ�����\n");
		all_users = sort_array(all_users, (: sort_per :) );
		text = ({});
		for(i=0;i<sizeof(all_users);i++)
		{
			text += ({ GRN"��"+(i+1)+"�� - "+TOP_D->get_name(all_users[i])+NOR+ZJBR+YEL+"���ۣ�"+TOP_D->query_user(all_users[i]+"/per")+NOR":look "+all_users[i] });
//			text += ({ GRN"��"+(i+1)+"�� - "+all_users[i]+NOR+ZJBR+YEL+"���ۣ�"+TOP_D->query_user(all_users[i]+"/per")+NOR":look "+all_users[i] });
		}
	}
	else if(type=="ɱ��")
	{
		reset_eval_cost();
		all_users = filter_array(all_users,(: TOP_D->query_user($1+"/PKS")>10 :));
		if(!sizeof(all_users))
			return notify_fail("����"+type+"�������ݣ�����\n");
		all_users = sort_array(all_users, (: sort_PKS :) );
		text = ({});
		for(i=0;i<sizeof(all_users);i++)
		{
			text += ({ GRN"��"+(i+1)+"�� - "+TOP_D->get_name(all_users[i])+NOR+ZJBR+YEL+"ɱ����"+TOP_D->query_user(all_users[i]+"/PKS")+NOR":look "+all_users[i] });
		}
	}
	else if(type=="ʦ��")
	{
		reset_eval_cost();
		all_users = filter_array(all_users,(: TOP_D->query_user($1+"/shimen")>10 :));
		if(!sizeof(all_users))
			return notify_fail("����"+type+"�������ݣ�����\n");
		all_users = sort_array(all_users, (: sort_shimen :) );
		text = ({});
		for(i=0;i<sizeof(all_users);i++)
		{
			if(all_users[i]=="player")
				m = TOP_D->query_user(all_users[i]+"/shimen")/7;
			else
				m = TOP_D->query_user(all_users[i]+"/shimen");
			text += ({ GRN"��"+(i+1)+"�� - "+TOP_D->get_name(all_users[i])+NOR+ZJBR+YEL+"���ܣ�"+m+NOR":look "+all_users[i] });
		}
	}
	else
	{
		reset_eval_cost();
		all_users = filter_array(all_users,(: TOP_D->query_user($1+"/combat_exp")>100000 :));
		if(!sizeof(all_users))
			return notify_fail("����"+type+"�������ݣ�����\n");
		all_users = sort_array(all_users, (: sort_exp :) );
		text = ({});
		for(i=0;i<sizeof(all_users);i++)
		{
			text += ({ GRN"��"+(i+1)+"�� - "+TOP_D->get_name(all_users[i])+NOR+ZJBR+YEL+TOP_D->query_user(all_users[i]+"/combat_exp")+NOR":look "+all_users[i] });
//			text += ({ GRN"��"+(i+1)+"�� - "+all_users[i]+NOR+ZJBR+YEL+TOP_D->query_user(all_users[i]+"/combat_exp")+NOR":look "+all_users[i] });
		}
	}

	str = ZJOBLONG+LOCAL_MUD_NAME()+HIG+type+NOR"���а�\n";

	str += ZJOBACTS2+ZJMENUF(2,2,10,30);

	all = sizeof(text)/10;
	if(sizeof(text)%10) all += 1;
	if(page<1) page = 1;
	if(page>all) page = all;
	j = (page-1)*10;
	i = page*10;
	if (i >= sizeof(text)) i = sizeof(text);
	i--;
	if(all>1)
		str += "��һҳ:tops "+type+" "+(page-1)+ZJSEP"��һҳ:tops "+type+" "+(page+1)+ZJSEP;
	str += implode(text[j..i], ZJSEP);
	tell_object(me,str+"\n");
	return 1;		   
}

int help(object me)
{
write(@HELP
������а�
HELP
	);
	return 1;
}

