// updateall.c
#include <ansi.h>

inherit F_CLEAN_UP;

int update_dir(object me, string dir, int continueable, int *total);

string strs;

int main(object me, string arg)
{
	string dir;
	object ob,obj,env;
	int continueable;
	int *total = ({0});

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	seteuid(geteuid(me));
	continueable = 0;

	message_system("���������У����Ժ�...");

	if (! update_dir(me, "/data/home/", 2, total))
	{
		write(HIR "������ҷ����ļ�����������ֹ��"NOR"\n");
	}
	else
		write(HIR "��ҷ���������ϡ�"NOR"\n");

	if (total[0] > 0)
	{
		write(HIC "�ܹ���" + HIW + total[0] + HIC "���������ɹ�����"NOR"\n");
	}
	else
		write(HIC "û�������κε�����"NOR"\n");

	return 1;
}

int update_dir(object me, string dir, int continueable, int *total)
{
	int i,j,k;
	int l,pay,used,leav;
	int filecount, compcount;
	mixed *file;
	object ob;
	string npcs,filename,cname,tit,name,ids,id2,txt,tx2;

	if (! is_root(previous_object()))
		return 0;
	file = get_dir(dir, -1);
	if (! sizeof(file))
	{
		if (file_size(dir) == -2)
			write(dir + "���Ŀ¼�ǿյġ�\n");
		else
			write("û��" + dir + "���Ŀ¼��\n");
		return 1;
	}

	write (HIY "��ʼ����Ŀ¼" + dir + "����������ļ���"NOR"\n");
	i = sizeof(file);
	compcount = 0;
	filecount = 0;
	k = 0;
	while (i--)
	{
		reset_eval_cost();
		if (file[i][1] != -2)
		{
			filecount++;
			filename = file[i][0];
			cname = read_file(dir+filename);
			if(sscanf(cname,"%*s(\"owner_build\",\"%s\")%*s",ids))
			{
				cname = replace_string(cname,"\""+ids+"\"","\""+ids+ZJGAMEPART"\"");
				cname = replace_string(cname,"/"+ids+"/","/"+ids+ZJGAMEPART"/");
				write_file(dir+filename,cname,1);
				compcount++;
				total[0]++;
			}

			if ((compcount%70)==0) write("\n");
		}

		// continue to compile next file
	}
	write(HIC "\n������Ŀ¼" + dir + "�µ�" + HIW + filecount + HIC + "���ļ����޸�������" + HIW + compcount + HIC + "��������"NOR"\n" );

	i = sizeof(file);
	while (i--)
	{
		reset_eval_cost();
		if (file[i][1] == -2)
		{
			if(sizeof(explode(dir,"/"))==3)
			{
				rename(dir+file[i][0],dir+file[i][0]+ZJGAMEPART);
				write(dir+file[i][0]+"\n");
				file[i][0] += ZJGAMEPART;
			}
			file[i][0] += "/";
			if (!update_dir(me, dir + file[i][0], continueable, total))
				return 0;
		}
	}
	return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : updateall <·����> [1]
 
���ָ����Ը���ĳ��·���µ�ȫ������, �����µ������������
������. �������β���־1�� �������������ʱ��������ֹ��
HELP
	);
	return 1;
}
