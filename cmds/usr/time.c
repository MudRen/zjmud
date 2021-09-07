// time.c

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	write(sprintf("MUD时间：%s。\n" ,NATURE_D->game_time()));
	write(sprintf("现实时间：%s。\n" ,CHINESE_D->chinese_date(time(),1)));
	write (HIY"会员时间还剩："+CHINESE_D->short_time(me->query("zjvip/times"))+ "。"NOR"\n");	

	return 1;
}

int help(object me)
{
     write(@HELP
指令格式: time

这个指令让你(你)知道现在的时辰。

HELP
    );
    return 1;
}
