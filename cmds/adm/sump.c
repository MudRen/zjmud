// sp.c

#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	string id,txt,*line;
	int i,k,sum;
	object ob;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;
	sum = 0;

	txt = read_file("/log/pay/success");
	line = explode(txt,"\n");
	for(i=0;i<sizeof(line);i++)
	{
		if(sscanf(line[i],"%*s��ֵ%fԪ%*s",k)==3)
			sum += k;
	}
	write("���ƣ�"+sum+"Ԫ��\n");

	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: sp <class> <info>

��Ȩ������վ��ĳЩ�����ʹ��Ȩ�ޡ�info ���Ϊ�ջ��� clear ��
��ʾȡ�������ʹ��Ȩ�ޡ�
HELP );
	return 1;
}
