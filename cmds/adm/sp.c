// updateall.c
#include <ansi.h>

inherit F_CLEAN_UP;

int update_dir(object me, string dir, int continueable, int *total);
int update_file(object me, string file);
string stra="";

int main(object me, string arg)
{
	string dir,*strs;
	object ob,obj,env,*users;
	int continueable;
	int *total = ({0});
	int i,m,n,k;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	seteuid(geteuid(me));

users = users();
for(i=0;i<sizeof(users);i++)
{
	users[i]->delete_temp("apply");
}
return 1;

env = environment(me);
ob = new("/clone/user/comb_ob");
ob->set("name",me->query("name")+"��ս��");
ob->set("out_room",file_name(env));
ob->move(env);
me->move(ob);
ob->add_apteam(me);
if(arg&&obj=present(arg,env))
{
	obj->move(ob);
	ob->add_dpteam(obj);
}
return 1;
	continueable = 0;
	if (! arg || sscanf(arg, "%s %d", dir, continueable) != 2)
		dir = arg;

	if (! dir)
	{
		dir = me->query("cwd");
		if (! dir)
			return notify_fail("��Ҫ���±����Ǹ�·���µ�����\n");
	} else
	{
		dir = resolve_path(me->query("cwd"), dir);
	}
	if (dir[strlen(dir) - 1] != '/')
		dir += "/";

	if (file_size(dir) != -2)
		return notify_fail("û��" + dir + "���·����\n");

	me->set("cwd", dir);

	message_system("�������������У����Ժ�...");
	if (! update_dir(me, dir, continueable, total))
	{
		write(HIR "��������������ֹ��"NOR"\n");
	}

	if (total[0] > 0)
	{
		write(HIC "�ܹ���" + HIW + total[0] + HIC "���������ɹ����룡"NOR"\n");
		write_file("/clone/npc.txt",stra,1);
	}
	else
		write(HIC "û�б����κε�����"NOR"\n");

	return 1;
}

int update_dir(object me, string dir, int continueable, int *total)
{
	int i,j;
	int l,pay,used,leav;
	int filecount, compcount;
	mixed *file;
	string *strs,npcs,filename,cname,tit,name,ids,id2,txt,tx2;

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
	while (i--)
	{
		reset_eval_cost();
		if (file[i][1] != -2)
		{
			filecount++;
			filename = file[i][0];
			l = strlen(filename);

/*ץȡnpc����
			name = dir+filename;
			if(name->query("name"))
			{
				stra += name->query("name")+"^"+name->query("id")+"^"+name->query("gender")+"^"+name->query("title")+"^"
					+name->query("age")+"^"+name->query("per")+"^"+name->query("combat_exp")+"^"+name->query("max_qi")+"^"
					+name->query("max_jing")+"^"+name->query("max_neili")+"^"+name->query("family/family_name")+"^"+name->query("long")
						+"\n";
			}
			else continue;
*/

/* �滻��дobject
			cname = read_file(replace_string(dir,"/src","/d")+"/"+filename);
			txt = read_file(dir+"/"+filename);
			if(!txt||!cname)
			{
				write(filename+"���ִ���\n");
				continue;
			}
			strs = explode(txt,"\"");
			npcs = "";
			for(j=0;j<sizeof(strs);j++)
			{
				if(sscanf(strs[j],".npc.%s",name)==1)
					npcs += "		__DIR__\"npc/"+lower_case(name)+ "\" : 1,\n";
			}
			if(npcs!="")
			{
				if(strsrch(cname,"//		__DIR__\"npc/baixiaosheng\" : 1,\n")!=-1)
				write_file(replace_string(dir,"/src","/d")+"/"+filename,replace_string(cname,"//		__DIR__\"npc/baixiaosheng\" : 1,\n",npcs),1);
			}
*/

/* �滻��дobject
			cname = read_file(replace_string(dir,"/src","/d")+"/"+filename);
			txt = read_file(dir+"/"+filename);
			if(!txt||!cname)
			{
				write(filename+"���ִ���\n");
				continue;
			}
			strs = explode(txt,"\"");
			npcs = "";
			for(j=0;j<sizeof(strs);j++)
			{
				if(sscanf(strs[j],".npc.%s",name)==1)
					npcs += "		__DIR__\"npc/"+lower_case(name)+ "\" : 1,\n";
			}
			if(npcs!="")
			{
				if(strsrch(cname,"//		__DIR__\"npc/baixiaosheng\" : 1,\n")!=-1)
				write_file(replace_string(dir,"/src","/d")+"/"+filename,replace_string(cname,"//		__DIR__\"npc/baixiaosheng\" : 1,\n",npcs),1);
			}
*/

/* �滻��дid,name
			cname = read_file(dir+filename);
			if(sscanf(cname,"%s	set_name(\"%s\");\n%s	setIdName(\"%s\");\n%s",tit,name,txt,ids,tx2)==5)
			{
				int k = 0;
				for(j=0;j<strlen(ids);j++)
				{
					if(ids[j]>='A'&&ids[j]<='Z'&&j>0)
					{
						id2 = replace_string(ids,sprintf("%c",ids[j]),sprintf(" %c",ids[j]));
						write(id2+"\n");
						break;
					}
				}
				if(!id2) id2 = ids+" n";
				id2 = lower_case(id2);
				ids = lower_case(ids);
				write_file(dir+"/"+filename,tit+"	set_name(\"" +name+ "\",({\"" +id2+ "\",\"" +ids+ "\"}));\n"+txt+tx2,1);
			}
*/

///* ���all_pay,yuanbao_used
			cname = read_file(dir+filename);
			sscanf(cname,"%*s\"id\":\"%s\",%*s",ids);
			sscanf(cname,"%*s\"all_pay\":%d,%*s",pay);
			sscanf(cname,"%*s\"yuanbao_used\":%d,%*s",used);
			sscanf(cname,"%*s\"yuanbao\":%d,%*s",leav);
			if(!pay) pay = 0;
			if(!used) used = 0;
			if(!leav) leav = 0;
			if((used+leav)>(pay*10+2000))
				stra += ids +":��ֵ"+ pay +"Ԫ������Ԫ��"+used+"��ʣ��"+leav+"Ԫ����\n";
			
//*/

/* ������
			cname = replace_string(filename,".java",".c");
			rename(dir+"/"+filename,dir+"/"+cname);
*/

/* ���±����ļ�
			if (filename[l - 1] != 'c' || filename[l - 2] != '.')
				continue;

			if (! update_file(me, dir + filename) && ! continueable)
				return 0;
*/
			compcount++;
			total[0]++;
			if ((compcount % 70) == 0)
				write("\n");
		}

		// continue to compile next file
	}
	write(HIC "\n������Ŀ¼" + dir + "�µ�" + HIW + filecount + HIC +
	      "���ļ�������������" + HIW + compcount + HIC + "��������"NOR"\n" );

	i = sizeof(file);
	while (i--)
	{
		reset_eval_cost();
		if (file[i][1] == -2)
		{
			file[i][0] += "/";
			write("\n");
			if (! update_dir(me, dir + file[i][0], continueable, total) && ! continueable)
				return 0;
		}
	}
	return 1;
}

int update_file(object me, string file)
{
	object obj;
	object *inv;
	string err;
	int i;

	if (file == "/cmds/adm/updateall.c")
		// Don't re-compile the updateall.c
		return 1;

	write (".");
	if (obj = find_object(file))
	{
		if (obj == environment(me))
		{
			if (file_name(obj) == VOID_OB)
				return notify_fail("\n�㲻���� VOID_OB �����±��� VOID_OB��\n");

			inv = all_inventory(obj);
			i = sizeof(inv);
			while(i--)
			{
				if (userp(inv[i])) inv[i]->move(VOID_OB, 1);
				else inv[i] = 0;
			}
		}
		destruct(obj);
	}

	if (obj) return notify_fail("\n�޷�����ɳ�ʽ�롣\n");

	err = catch( call_other(file, "???") );
	if (err)
	{
		printf( "\n��������\n%s\n", err );
		return 0;
	} else
	{
		if ((i = sizeof(inv)) && (obj = find_object(file)))
		{
			while(i--)
				if (inv[i] && userp(inv[i])) inv[i]->move(obj, 1);
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
