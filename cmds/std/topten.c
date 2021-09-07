#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;
int top_list(object ob1,object ob2);
int get_score(object ob);
int main(object me, string arg)
{
	
	object *list,*ob;
	int i,a;
	string msg;
	
	ob = filter_array(users(), (: userp($1) && !wizardp($1) && environment($1) && $1->query("combat_exp")>3000 :));
	list = sort_array(ob, (: top_list :));
	
	if(!arg ) 
	a=10;
	else {
		if(sscanf(arg,"%d",a)) {
			if( a > sizeof(list)) a=sizeof(list);
		}
		else return 0;
	}
	
	msg =  "\n	     "+HIG+MUD_NAME+"���߸������а�"NOR" \n";
	msg += "\n";
	 msg += " ����     ��	��	 ��  ��     ��  �� \n";
	msg += "\n";
	for (i = 0 ;i < a ; i++) {
	if( i >= sizeof(list)) msg += "��ʱ��ȱ�� \n";
		else {
		if(list[i] == me) msg += BBLU HIY;
		msg += sprintf(HIW"  %-5s"+HIY" %-22s"+HIC"%-10s"+HIR" %5d  "NOR"\n",chinese_number(i+1),list[i]->query("name")+"("+
	capitalize(list[i]->query("id"))+")", list[i]->query("family")?  list[i]->query("family/family_name"):"��ͨ����",
	get_score(list[i]));
		}
			 }
	msg += "\n";
	msg += "  " + NATURE_D->game_time() + "�ǡ�\n";
	 msg += HIM"���������ǣ�"+get_score(this_player())+"\n"NOR"\n";
	write(msg);
	return 1;

}
int top_list(object ob1, object ob2)
{
      int score1,score2;

	score1 = get_score(ob1);
	score2 = get_score(ob2);

      return score2 - score1;
}

int get_score(object ob)
{
	int tlvl,i,score;
	string *ski;
	mapping skills;

      reset_eval_cost();
	skills = ob->query_skills();
	if (!sizeof(skills)) return 1; 
	ski  = keys(skills);
	for(i = 0; i<sizeof(ski); i++) {
			tlvl += skills[ski[i]];
			}  // count total skill levels
	score = tlvl/10;
	score += ob->query("max_neili")/10;
	score += ob->query_str() + ob->query_int() + ob->query_dex() + ob->query_con();
	score += (int)ob->query("combat_exp")/2500;

	return score;
}

int help(object me)
{
write(@HELP
ָ���ʽ : top 
 
���ָ���������֪������ʮ���������Щ����ȥ�����ǡ� 
 
HELP
    );
    return 1;
}
