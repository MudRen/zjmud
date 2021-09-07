
#include <ansi.h>
 
inherit F_CLEAN_UP;

string status_color(int current, int max);
 
int main(object me, string arg)
{
	object ob;
	mapping my;
	string sp;

	seteuid(getuid(me));
	ob = me;
 
	my = ob->query_entire_dbase();

	if (my["max_jing"] < 1 || my["max_qi"] < 1)
		return notify_fail("无法察看" + ob->name(1) + "的状态。\n");

	sp  = ZJHPTXT+ZJMENUF(5,5,28,45)+sprintf("%s:100/100:%s",my["name"],"#000000");
	sp += "║" + sprintf("气血.%d:%d/%d/%d:%s:%s",my["qi"],my["qi"],my["eff_qi"],my["max_qi"]+ob->query_gain_qi(),"#99FF0000","exert recover");
	sp += "║" + sprintf("内力.%d:%d/%d/%d:%s",my["neili"],my["neili"],my["max_neili"],ob->query_current_neili_limit(),"#990066FF");
	sp += "║" + sprintf("精神.%d:%d/%d/%d:%s:%s",my["jing"],my["jing"],my["eff_jing"],my["max_jing"],"#996600CC","exert regenerate");
	sp += "║" + sprintf("精力.%d:%d/%d/%d:%s",my["jingli"],my["jingli"],my["max_jingli"],ob->query_current_jingli_limit(),"#99006600",);
	sp += "║" + sprintf("怒气.%d:%d/%d:%s",ob->query_craze(),ob->query_craze(),ob->query_max_craze(),"#99990000");
	sp += "║" + sprintf("食物.%d:%d/%d:%s",my["food"],my["food"],ob->max_food_capacity(),"#99FF6600");
	sp += "║" + sprintf("饮水.%d:%d/%d:%s",my["water"],my["water"],ob->max_water_capacity(),"#990000FF");
	sp += "║" + sprintf("经验.%d:%d/%d:%s",my["combat_exp"],my["combat_exp"],F_LEVEL->level_max_exp(ob),"#99FF0066");
	sp += "║" + sprintf("潜能.%d:%d/%d/%d:%s",my["potential"]-my["learned_points"],my["potential"]-my["learned_points"],ob->query_potential_limit()-my["potential"],ob->query_potential_limit(),"#99FF00FF");
	sp += "\n";
	tell_object(me, sp);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : hp
	  hp <对象名称>		  (巫师专用)
 
这个指令可以显示你(你)或指定对象(含怪物)的精, 气, 神数值。
 
see also : score
HELP );
    return 1;
}


