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

	if (! update_dir(me, "/data/user/", 2, total))
	{
		write(HIR "���������������������ֹ��"NOR"\n");
	}
	else
		write(HIR "�������������ϡ�"NOR"\n");

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
	int i,j,k,m;
	int l,pay,used,leav;
	int filecount, compcount;
	mixed *file;
	object ob,card;
	string str,*strs,npcs,filename,cname,tit,name,ids,id2,txt,tx2;
	mapping dizi,dizi2,dz;

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
			if(sscanf(file[i][0],"%s.o",filename)==1)
			{
				ob = UPDATE_D->global_find_player(filename);

				if(ob)
				{
					if(NAME_D->query_id(ob->query("name"))&&NAME_D->query_id(ob->query("name"))!=ob->query("id"))
					{
						ob->set("name",ob->query("name")+"��");
						ob->add_autoload("/clone/shizhe/card_name");
						tell_object(me,ob->query("name")+"("+ob->query("name")+")�����ظ������������һ�š�\n");
					}

					NAME_D->map_name(ob->query("name"),ob->query("id"));
					TOP_D->map_user(ob);
					UPDATE_D->global_destruct_player(ob, 1);
				}
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
			file[i][0] += "/";
			write("\n");

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
