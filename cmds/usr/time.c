// time.c

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	write(sprintf("MUDʱ�䣺%s��\n" ,NATURE_D->game_time()));
	write(sprintf("��ʵʱ�䣺%s��\n" ,CHINESE_D->chinese_date(time(),1)));
	write (HIY"��Աʱ�仹ʣ��"+CHINESE_D->short_time(me->query("zjvip/times"))+ "��"NOR"\n");	

	return 1;
}

int help(object me)
{
     write(@HELP
ָ���ʽ: time

���ָ������(��)֪�����ڵ�ʱ����

HELP
    );
    return 1;
}
