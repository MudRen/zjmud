// uptime.c
#include <mudlib.h>
#include <getconfig.h>
inherit F_CLEAN_UP;

int main()
{
	int t, d, h, m, s;
	string time;

	t = uptime();
	s = t % 60;		t /= 60;
	m = t % 60;		t /= 60;
	h = t % 24;		t /= 24;
	d = t;

	if (d) time = chinese_number(d) + "��";
	else time = "";

	if (h) time += chinese_number(h) + "Сʱ";
	if (m) time += chinese_number(m) + "��";
	time += chinese_number(s) + "��\n";

	write(LOCAL_MUD_NAME() + "�Ѿ�ִ����" + time + "\n");
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : uptime
 
���ָ���������������Ϸ�Ѿ�����ִ���˶�á�
 
HELP
    );
    return 1;
}
