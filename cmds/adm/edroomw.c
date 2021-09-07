// updateall.c
#include <ansi.h>

inherit F_CLEAN_UP;

mapping attrib =([
	"��ȫ��":"no_fight",
	"��Ϣ��":"sleep_room",
	"���ڷ�":"price_build",
]);

mapping lattrib =([
	"����"	:"long",
]);

int main(object me, string arg)
{
	string *att,str,dir,list,*files,file,attr,atts;
	string nid,msg,txt1,txt2,txt3;
	int i,num;
	object env,npc;
	mapping guard;

	env = environment(me);

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	seteuid(geteuid(me));

	if (!arg)
	{
		str = ZJOBLONG"��ѡ���������"+env->query("short")+"��ѡ�\n";
		str += ZJOBACTS2+ZJMENUF(4,4,9,30);
		att = sort_array(keys(lattrib),1);
		for(i=0;i<sizeof(att);i++)
		{
			str += att[i]+":edroom "+ att[i]+ZJSEP;
		}
		att = sort_array(keys(attrib),1);
		for(i=0;i<sizeof(att);i++)
		{
			str += att[i]+":edroom "+ att[i]+ZJSEP;
		}
		str += "��������:edroom guard"+ZJSEP;
		write(str+"\n");
		return 1;
	}
	else if (sscanf(arg,"%s %d",atts,num)==2)
	{
		if(num<0||num>999999)
			return notify_fail(HIG+"ֻ������0�رջ����1-999999֮���ֵ�򿪣�"NOR"\n");
		file = base_name(env);
		list = read_file(file+".c");

		if (attrib[atts])
		{
			if(sscanf(list,"%s	set(\""+attrib[atts]+"\"%*s);\n%s",txt1,txt2)==3)
			{
				if(num==0)
					str = txt1 + txt2;
				else
					str = txt1 + "	set(\""+attrib[atts]+"\", " + num + ");\n" + txt2;
				write_file(file+".c",str,1);
				me->force_me("update here");
				me->force_me("look");
				write("�޸ĳɹ���\n");
			}
			else
			{
				list = replace_string(list,"	setup();\n","	set(\""+attrib[atts]+"\", " + num + ");\n	setup();\n");
				write_file(file+".c",list,1);
				me->force_me("update here");
				me->force_me("look");
				write("�޸ĳɹ���\n");
			}
		}
		return 1;
	}
	else if(arg=="guard")
	{
		str = ZJOBLONG"��ѡ��Ҫ�����ķ���"ZJBR+ZJBR;
		str += "����������������"ZJURL("cmds:edroom guard north")+ZJSIZE(15)"����"NOR+ZJBR+ZJBR;
		str += "��"ZJURL("cmds:edroom guard west")+ZJSIZE(15)"����"NOR"��������������������";
		str += ZJURL("cmds:edroom guard east")+ZJSIZE(15)"����"NOR+ZJBR+ZJBR;
		str += "����������������"ZJURL("cmds:edroom guard south")+ZJSIZE(15)"����"NOR+ZJBR;
		write(str+"\n");
		return 1;
	}
	else if (sscanf(arg,"guard %s",attr)==1)
	{
		file = base_name(env);
		list = read_file(file+".c");
		if(!mapp(guard = env->query("guard")))
			guard = ([]);

		if(sscanf(attr,"%s %s",dir,atts)==2)
		{
			if(atts=="del")
			{
				map_delete(guard,dir);
				write("�˷������������������\n");
			}
			else if(sscanf(atts,"%s/%s",nid,msg)!=2)
			{
				write(INPUTTXT("������������·��Ϣ��","edroom "+arg+"/$txt#")+"\n");
				return 1;
			}
		}
		else
		{
			str = ZJOBLONG"��ѡ������NPC��\n"ZJOBACTS2+ZJMENUF(3,3,9,30);
			if(!env->query("objects"))
				return notify_fail("������û�е��ù̶�NPC�����ܷ���������\n");
			files = keys(env->query("objects"));
			if(!sizeof(files))
				return notify_fail("������û�е��ù̶�NPC�����ܷ���������\n");

			str += "ȡ������:edroom "+arg+" del"ZJSEP;
			for(i=0;i<sizeof(files);i++)
			{
				if(file_size(files[i]+".c")<0) continue;
				str += files[i]->query("name")+":edroom "+arg+" "+files[i]->query("id")+ZJSEP;
			}
			write(str+"\n");
			return 1;
		}

		if(dir!="east"&&dir!="south"&&dir!="west"&&dir!="north")
			return notify_fail(HIG+"����ѡ������"NOR"\n");
		if(atts!="del")
			guard[dir] = nid+"/"+msg;
		files = keys(guard);
		if(sscanf(list,"%s	set(\"guard\"%*s);\n%s",txt1,txt2)==3)
		{
			str = txt1+"	set(\"guard\", ([\n";
			for(i=0;i<sizeof(files);i++)
			{
				str += "		\""+files[i]+"\" : \""+guard[files[i]]+"\",\n";
			}
			str += "	]));\n";
			str += txt2;
			write_file(file+".c",str,1);
			me->force_me("update here");
			me->force_me("look");
			write("�޸ĳɹ���\n");
		}
		else if(atts!="del")
		{
			list = replace_string(list,"	setup();","	set(\"guard\", ([\n		\""+dir+"\" : \""+nid+"/"+msg+"\",\n	]));\n	setup();");
			write_file(file+".c",list,1);
			me->force_me("update here");
			me->force_me("look");
			write("�޸ĳɹ���\n");
		}

		return 1;
	}
	else if (sscanf(arg,"%s %s",atts,attr)==2)
	{
		file = base_name(env);
		list = read_file(file+".c");

		if (lattrib[atts])
		{
			if(sscanf(list,"%s	set(\""+lattrib[atts]+"\"%*s);\n%s",txt1,txt2)==3)
			{
				if(attr=="0")
					str = txt1 + txt2;
				else
					str = txt1 + "	set(\""+lattrib[atts]+"\", \"" + attr + "\");\n" + txt2;
				write_file(file+".c",str,1);
				me->force_me("update here");
				me->force_me("look");
				write("�޸ĳɹ���\n");
			}
			else
			{
				list = replace_string(list,"	setup();\n","	set(\""+lattrib[atts]+"\", \"" + attr + "\");\n	setup();\n");
				write_file(file+".c",list,1);
				me->force_me("update here");
				me->force_me("look");
				write("�޸ĳɹ���\n");
			}
		}
	}
	else
	{
		if (attrib[arg])
		{
			write(INPUTTXT("����ѡ�"+env->query("short")+"���ġ�"+arg+"����"+env->query(attrib[arg])+"����Ϊ���٣�"
				ZJBR"0����رո����ԣ�����0��ֵ�򿪸����Բ��趨ֵ��","edroom "+arg+" $txt#")+"\n");
		}
		else if (lattrib[arg])
		{
			write(INPUTTXT("�����趨��"+env->query("short")+"���ġ�"+arg+"��Ϊʲô��","edroom "+arg+" $txt#")+"\n");
		}
		return 1;
	}

	return 1;
}
