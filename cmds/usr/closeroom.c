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

	if(room_type!="price")
		return notify_fail(HIY"ֻ�����ſ����趨���أ���"NOR"\n");

	if(!arg)
	{
		str = ZJOBLONG"��ѡ����ļ������ڵķ���"ZJBR+ZJBR;
		str += "����������������"ZJURL("cmds:closeroom north")+ZJSIZE(15)"����"NOR+ZJBR+ZJBR;
		str += "��"ZJURL("cmds:closeroom west")+ZJSIZE(15)"����"NOR"��������������������";
		str += ZJURL("cmds:closeroom east")+ZJSIZE(15)"����"NOR+ZJBR+ZJBR;
		str += "����������������"ZJURL("cmds:closeroom south")+ZJSIZE(15)"����"NOR+ZJBR;
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
		return notify_fail(obs[arg]->query("short")+"������ļҡ�\n");

	dirs = keys(obs);
	
	list = BUILD_D->get_file_code(find_object(obs[arg]));

	if(strsrch(list,"	set(\"door_room\", 1);\n")!=-1)
	{
		list = replace_string(list,"	set(\"door_room\", 1);\n","");
		find_object(obs[arg])->delete("door_room");
		write("��԰���趨Ϊ���ţ�\n");
	}
	else
	{
		list = replace_string(list,"	setup();\n","	set(\"door_room\", 1);\n	setup();\n");
		find_object(obs[arg])->set("door_room",1);
		write("��԰���趨Ϊ�رգ�\n");
	}
	BUILD_D->build_file(me,obs[arg]+".c",list);
	return 1;
}
