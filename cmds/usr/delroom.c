// updateall.c
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string str,list,dir,*dirs,*attr,file,*files;
	string room_type,txt1,txt2,txt3;
	int i,k;
	mapping obs;
	object env;

	seteuid(geteuid(me));

	env = environment(me);
	if(env->query("price_build"))
		room_type = "price";
	else if(env->query("owner_build"))
		room_type = "owner";
	else
		room_type = "system";

	if(room_type=="system"&&!SECURITY_D->valid_grant(me, "(admin)"))
		return notify_fail(HIY"ϵͳ����ֻ������ʦ�������"NOR"\n");

	if(!arg)
	{
		str = ZJOBLONG"����ɾ���ĸ�����ĳ�����"ZJBR+ZJBR;
		str += "����������������"ZJURL("cmds:delroom north")+ZJSIZE(15)"����"NOR+ZJBR+ZJBR;
		str += "��"ZJURL("cmds:delroom west")+ZJSIZE(15)"����"NOR"��������������������";
		str += ZJURL("cmds:delroom east")+ZJSIZE(15)"����"NOR+ZJBR+ZJBR;
		str += "����������������"ZJURL("cmds:delroom south")+ZJSIZE(15)"����"NOR+ZJBR;
		write(str+"\n");
		return 1;
	}

	dirs = explode(base_name(env),"/");
	dirs = dirs[0..(sizeof(dirs)-2)];
	dir = "/"+implode(dirs,"/")+"/";
	obs = env->query("exits");
	if(!mapp(obs)||!obs[arg])
		return notify_fail("�Ǹ�����û�г�����\n");

	if(obs[arg]->query("owner_build")!=me->query("id"))
		return notify_fail(obs[arg]->query("short")+"������ĸ��˵��̣����ܲ����\n");
	if(obs[arg]->query("objects")&&sizeof(keys(obs[arg]->query("objects")))>0)
		return notify_fail("���Ƚ���"+obs[arg]->query("short")+"ɾ��NPC���úͶ���������ӡ�\n");
	if(obs[arg]->query("exits")&&sizeof(keys(obs[arg]->query("exits")))>1)
		return notify_fail(obs[arg]->query("short")+"���ӵ�����������������ֱ��ɾ����\n");
	if(sizeof(all_inventory(find_object(obs[arg]))))
		return notify_fail(obs[arg]->query("short")+"����δ�����������������ȥ�����\n");

	dirs = keys(obs);
	
	list = BUILD_D->get_file_code(env);
	if(sscanf(list,"%sset(\"exits\"%*s]));%s",txt1,txt2)==3)
	{
		BUILD_D->del_file(me,obs[arg]+".c");
		map_delete(obs,arg);
		files = keys(obs);
		list = txt1+"set(\"exits\", ([\n";
		for(i=0;i<sizeof(files);i++)
		{
			list += "		\""+files[i]+"\" : \""+obs[files[i]]+"\",\n";
		}
		list += "	]));"+txt2;
		list = replace_string(list,"\""+dir,"__DIR__\"");
		BUILD_D->build_file(me,base_name(env)+".c",list);
		env->delete("exits/"+arg);
		write(HIY"����ɾ���ɹ�������"NOR"\n");
	}
	else
		write(HIY"�����������ݶ�ȡʧ�ܣ�ɾ��ʧ�ܡ�����"NOR"\n");

	return 1;
}

void update_here(object me)
{
	me->force_me("update here");
	me->force_me("look");
}
