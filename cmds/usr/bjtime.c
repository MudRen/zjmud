// time.c					  
#include <ansi.h>

// #define END_TIME 874425565
#define END_TIME 875981023
#define FETEDAY "�����"
inherit F_CLEAN_UP;

int main(object me, string arg)
{   int time, date;
    time = time();
	write(sprintf("���ڵ�ʱ���Ǳ���ʱ�� " + ctime( time ) + "��\n"));
    date = (END_TIME-time) / 24 / 3600;
    if (date > 1)
    {
	write(sprintf("����" + FETEDAY + "����"BBLU YEL"%s"NOR"�졣\n", 
	    chinese_number(date)));
    }
    else if (date == 1)
    {
	write(sprintf(BBLU YEL "\n\t\t�������" + FETEDAY + "�ˣ�"NOR"\n"));
    }
    else if (!date)
    {
	write(sprintf(BBLU YEL "\n\t\t������" + FETEDAY + "��\n"NOR"\n"));
    }
	return 1;
}

int help(object me)
{
     write(@HELP
ָ���ʽ: time

���ָ���������ʵ���������ڵ�ʱ�䡣

HELP
    );
    return 1;
}
