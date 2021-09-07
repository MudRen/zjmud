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

void more_str(string tab, string str, int line, int page)
{
	int i, j, now, all;
	string show,*text,*topics,topic;

	show = tab;
	text = explode(str,"\n");
	all = sizeof(text)/line;
	if(sizeof(text)%line) all += 1;
	if(page<1) page = 1;
	if(page>all) page = all;
	j = (page-1)*line;
	i = page*line;
	if (i >= sizeof(text)) i = sizeof(text);
	i--;
	topics = explode(str,"/");
	topic = topics[sizeof(topics)-1];
	show += sprintf("�� %s(Wulin)�������(%d/%dҳ)��\n",CHINESE_MUD_NAME,page,all);
	show += ZJOBACTS2+ZJMENUF(2,2,9,35);
	show += "��һҳ:who "+(page-1)+ZJSEP"��һҳ:who "+(page+1)+ZJSEP;
	show += implode(text[j..i], ZJSEP);
	write(show+"\n");
}

mixed main(object me, string arg, int remote)
{
	string str;
	object *ob;
	int page,i;
	string name, *option;
	object *list;
	int j, ppl_cnt,wiz_cnt;
	int opt_long, opt_id, opt_wiz;
	int SendInterMud=0;
	string HostName,strMsg;
  
	str="";
	i=0;

	wiz_cnt = 0;
	ppl_cnt = 0;
	if(remote && sizeof(arg)<2) arg="";

	if( !arg )
	{
		page = 1;
	}
	else if(sscanf(arg,"%d",page)!=1)
	{
		page = 1;
	}
	list = sort_array(children(USER_OB), "sort_user2", this_object());
	j = sizeof(list);
	while( j-- )
	{
		if( !environment(list[j]) ) continue;
		if(me && !me->visible(list[j]) ) continue;
		if(!me && (int)list[j]->query("env/invisibility")>0 ) continue;
		str += sprintf("%s"ZJBR+WHT"%s"NOR"("HIG"%s"NOR"):look %s\n",list[j]->query("title"),list[j]->query("name"),list[j]->query("id"),list[j]->query("id"));
//		str += sprintf("%s"ZJURL("cmds:look "+list[j]->query("id"))+ZJSIZE(20)"%s"NOR"\n",list[j]->query("title"),list[j]->query("name"));
		ppl_cnt ++;
		wiz_cnt ++;
	}

	more_str(ZJOBLONG, str, 10, page);
	return 1;		   
}

int sort_user(object ob1, object ob2)
{
	if( wizardp(ob1) && !wizardp(ob2) ) return -1;
	
	if( wizardp(ob2) && !wizardp(ob1) ) return 1;

	if( wizardp(ob1) && wizardp(ob2) )
	return (int)SECURITY_D->get_wiz_level(ob2) 
		- (int)SECURITY_D->get_wiz_level(ob1);

	if( ob1->query("id") && !ob2->query("id") )
	return -1;
	if( ob2->query("id") && !ob1->query("id") )
	return 1;
	if( !ob1->query("id") && !ob2->query("id") )
	return (int)ob2->query("combat_exp") - (int)ob1->query("combat_exp");
	return strcmp(ob2->query("id"), ob1->query("id"));
}

int sort_user2(object ob1, object ob2)
{
	 return (int)ob1->query("combat_exp") - (int)ob2->query("combat_exp");
}

int help(object me)
{
write(@HELP
ָ���ʽ : who [@<MudName>] [-l|-i|-w]

���ָ������г����������ϻ������е� Mud ����Ҽ���ȼ���
@<MudName> [-l|-i|-w] ����who @The.Master.Of.Hero -w

-l ѡ���г��ϳ���ѶϢ��
-i ֻ�г���ҵ�Ӣ�Ĵ��š�
-w ֻ�г��������е���ʦ��
 
���ָ� finger
HELP
	);
	return 1;
}

