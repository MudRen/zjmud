// updateall.c
#include <ansi.h>

inherit F_CLEAN_UP;

mapping attrib =([
	"��Ϣ��":(["type":"sleep_room","need":"Ԫ��","need_num":50,]),
	"�չ���":(["type":"close_room","need":"Ԫ��","need_num":500,]),
	"������":(["type":"practice_room","need":"Ԫ��","need_num":500,]),
	"������":(["type":"door_room","need":"���","need_num":1,]),
]);

mapping lattrib =([
	"����"	:(["type":"short","need":"���","need_num":10,]),
	"����"	:(["type":"long","need":"���","need_num":10,]),
]);

// �ж��Ƿ��ǺϷ��ĺ���
int legal_chinese(string str)
{
	int i;

	if (strlen(str) < 2) return 0;

	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] < 161 || str[i] == 255) return 0;
		if ((! (i % 2)) && str[i] >= 248) return 0;
	}

	return 1;
}

int main(object me, string arg)
{
	string *att,str,dir,list,*files,file,attr,atts;
	string nid,msg,txt1,txt2,txt3,room_type;
	int i,num;
	object env,npc;
	mapping guard;

	env = environment(me);

	if(env->query("price_build"))
		room_type = "price";
	else if(env->query("owner_build"))
		room_type = "owner";
	else
		room_type = "system";

	if(room_type!="owner"&&!SECURITY_D->valid_grant(me, "(admin)"))
		return notify_fail(HIY"ϵͳ����ֻ������ʦ�Ľ�����"NOR"\n");
	else if(env->query("owner_build")!=me->query("id"))
		return notify_fail(HIY"��ֻ�����Լ��ļ���Ľ�����"NOR"\n");

	seteuid(geteuid(me));

	if (!arg)
	{
		str = ZJOBLONG"��ѡ�������޸�"+env->query("short")+"��ѡ�\n";
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
		write(str+"\n");
		return 1;
	}
	else if (sscanf(arg,"%s %d",atts,num)==2)
	{
		if(num!=0 && num!=1)
			return notify_fail(HIG+"ֻ������ 0���رգ��� 1���򿪣���"NOR"\n");
		file = base_name(env);
		list = BUILD_D->get_file_code(env);

		if (attrib[atts])
		{
			if(attrib[atts]["need"]=="Ԫ��"&&me->query("yuanbao")<attrib[atts]["need_num"])
				return notify_fail(HIG+"���Ԫ��������֧���Ľ��ѣ�"NOR"\n");
			if(attrib[atts]["need"]=="���"&&!MONEY_D->player_pay(me,attrib[atts]["need_num"]*10000))
				return notify_fail(HIG+"��Ľ�Ҳ�����֧���Ľ��ѣ�"NOR"\n");

			if(sscanf(list,"%s	set(\""+attrib[atts]["type"]+"\"%*s);\n%s",txt1,txt2)==3)
			{
				if(num==0)
				{
					env->delete(attrib[atts]["type"]);
					env->delete("owner_special");
					str = txt1 + txt2;
					str = replace_string(str,"	set(\"owner_special\", 1);\n","");
				}
				else
				{
					if(env->query("owner_special"))
						return notify_fail(HIG+"ͬһ����ֻ������һ�ֹ��ܡ�"NOR"\n");
					else
						str = txt1 + "	set(\""+attrib[atts]["type"]+"\", " + num + ");\n"
							+ "	set(\"owner_special\", 1);\n" + txt2;
					env->set(attrib[atts]["type"],num);
					env->set("owner_special",1);
				}
				BUILD_D->build_file(me,file+".c",str);
				"/cmds/std/look"->main(me);
				write("�޸ĳɹ���\n");
			}
			else
			{
				if(env->query("owner_special"))
					return notify_fail(HIG+"ͬһ����ֻ������һ�ֹ��ܡ�"NOR"\n");
				else
					list = replace_string(list,"	setup();\n","	set(\""+attrib[atts]["type"]+"\", " + num + ");\n	set(\"owner_special\", 1);\n	setup();\n");
				BUILD_D->build_file(me,file+".c",list);
				env->set(attrib[atts]["type"],num);
				env->set("owner_special",1);
				"/cmds/std/look"->main(me);
				write("�޸ĳɹ���\n");
			}
			if(attrib[atts]["need"]=="Ԫ��"&&num!=0)
				me->add("yuanbao",-attrib[atts]["need_num"]);
		}
		return 1;
	}
	else if (sscanf(arg,"%s %s",atts,attr)==2)
	{
		file = base_name(env);
		list = BUILD_D->get_file_code(env);

		if (lattrib[atts])
		{
			if(atts=="����")
			{
				if(!is_chinese(attr))
					return notify_fail(HIY"�������ֱ����Ǵ����ģ���"NOR"\n");
				if(strlen(attr)>12)
					return notify_fail(HIY"�������ֲ��ܳ���6�������֣���"NOR"\n");
			}
			if(atts=="����"&&strlen(attr)>300)
				return notify_fail(HIY"�����������ֻ����150������(300�ַ�)����"NOR"\n");
			if(atts=="����"&&!legal_chinese(attr))
				return notify_fail(HIY"��������ֻ���ú��ֺ͹涨��Ӣ�ķ��ţ���"NOR"\n");

			if(lattrib[atts]["need"]=="Ԫ��"&&me->query("yuanbao")<lattrib[atts]["need_num"])
				return notify_fail(HIG+"���Ԫ��������֧���Ľ��ѣ�"NOR"\n");
			if(lattrib[atts]["need"]=="���"&&!MONEY_D->player_pay(me,lattrib[atts]["need_num"]*10000))
				return notify_fail(HIG+"��Ľ�Ҳ�����֧���Ľ��ѣ�"NOR"\n");

			if(sscanf(list,"%s	set(\""+lattrib[atts]["type"]+"\"%*s);\n%s",txt1,txt2)==3)
			{
				if(attr=="0")
				{
					env->delete(lattrib[atts]["type"]);
					str = txt1 + txt2;
				}
				else
				{
					env->set(lattrib[atts]["type"],attr);
					str = txt1 + "	set(\""+lattrib[atts]["type"]+"\", \"" + attr + "\");\n" + txt2;
				}
				BUILD_D->build_file(me,file+".c",str);
				"/cmds/std/look"->main(me);
				write("�޸ĳɹ���\n");
			}
			else
			{
				list = replace_string(list,"	setup();\n","	set(\""+lattrib[atts]["type"]+"\", \"" + attr + "\");\n	setup();\n");
				BUILD_D->build_file(me,file+".c",list);
				env->set(lattrib[atts]["type"],attr);
				"/cmds/std/look"->main(me);
				write("�޸ĳɹ���\n");
			}
			if(lattrib[atts]["need"]=="Ԫ��"&&attr!="0")
				me->add("yuanbao",-lattrib[atts]["need_num"]);
		}
	}
	else
	{
		if (attrib[arg])
		{
			write(INPUTTXT("����ѡ�"+env->query("short")+"������Ϊ��"+arg+"����"ZJBR"Ŀǰ�ó��������Ե�ֵΪ��"+env->query(attrib[arg]["type"])+"����"
				ZJBR"����0����رո����ԣ�����1����򿪸����ԡ�"ZJBR
				HIG"ע�⣺������Ҫ����"+attrib[arg]["need_num"]+attrib[arg]["need"]+NOR"����������������˷ѸĽ��ѣ�","edroom "+arg+" $txt#")+"\n");
		}
		else if (lattrib[arg])
		{
			write(INPUTTXT("�����趨��"+env->query("short")+"���ġ�"+arg+"��Ϊʲô��"ZJBR
				HIG"ע�⣺�޸ĸ�������Ҫ����"+lattrib[arg]["need_num"]+lattrib[arg]["need"]+NOR"��","edroom "+arg+" $txt#")+"\n");
		}
		return 1;
	}

	return 1;
}
