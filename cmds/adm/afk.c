// updateall.c
#include <ansi.h>

int main(object me, string arg)
{
	string *strs,str;
	object ob,obj,env;
	int i;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;
	seteuid(geteuid(me));

	if(!arg)
	{
		strs = AFK_D->afk_list();
		str = ZJOBLONG"��ѡ��һ�����\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
		for(i=0;i<sizeof(strs);i++)
		{
			str += AFK_D->query(strs[i]+"/name")+":"+"afk "+strs[i];
			if(i<(sizeof(strs)-1)) str += ZJSEP;
		}
		str += ZJSEP"��������:afk -u";
		write(str+"\n");
		return 1;
	}

	if(arg == "-u")
	{
		AFK_D->load_afks();
		write("�һ��������ݸ�����ϡ�\n");
		return 1;
	}

	if(!mapp(AFK_D->query(arg)))
		return notify_fail("ϵͳ��û����Ҫ�һ��Ĺһ�����\n");

	me->delete("afk");
	me->set("afk/file",arg);
	me->set("afk/room",environment(me));
	write("��ʼ׼���һ���"+AFK_D->query(arg+"/name")+"��....\n");
	return 1;
}
