// updateall.c
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string room_type,str,list,*dirs,*attr;
	int i;
	object ling,env;
	mapping dir = ([
		"east":"����",
		"west":"����",
		"south":"����",
		"north":"����",
	]);
	mapping dir2 = ([
		"east":"west",
		"west":"east",
		"south":"north",
		"north":"south",
	]);
	seteuid(geteuid(me));

	env = environment(me);

	if(env->query("price_build"))
		room_type = "price";
	else if(env->query("owner_build"))
		room_type = "owner";
	else
		room_type = "system";

	if(room_type=="system"&&!SECURITY_D->valid_grant(me, "(admin)"))
		return notify_fail(HIY"ϵͳ����ֻ������ʦ���裡��"NOR"\n");
	else if(room_type=="owner"&&env->query("owner_build")!=me->query("id"))
		return notify_fail(HIY"�ⲻ�����Լ��ļҰɣ���"NOR"\n");
	else if(!objectp(ling=present("build ling",me)))
		return notify_fail(HIY"�����԰����Ҫ�н������ƣ���"NOR"\n");

	if(!arg)
	{
		str = ZJOBLONG"��ѡ��Ҫ����������λ�ã�"ZJBR+ZJBR;
		str += "����������������"ZJURL("cmds:crroom north")+ZJSIZE(15)"����"NOR+ZJBR+ZJBR;
		str += "��"ZJURL("cmds:crroom west")+ZJSIZE(15)"����"NOR"��������������������";
		str += ZJURL("cmds:crroom east")+ZJSIZE(15)"����"NOR+ZJBR+ZJBR;
		str += "����������������"ZJURL("cmds:crroom south")+ZJSIZE(15)"����"NOR+ZJBR;
		write(str+"\n");
		return 1;
	}

	attr = explode(arg," ");

	if(sizeof(attr)==1)
	{
		if(!dir[arg])
			return notify_fail(HIY"����ѡ�����󣡣�"NOR"\n");
		if(env->query("exits/"+arg))
			return notify_fail(HIY"�˷������г����˲����ظ���������"NOR"\n");

		if(room_type=="price")
			write(INPUTTXT("��ѡ����"HIY+dir[arg]+NOR"�����³���"ZJBR"�˵�������ҹ��������õأ���Ҫ֧��"+env->query("price_build")+"Ԫ���Ľ���ѡ�"ZJBR"��ȷ���������趨����������(2-5��������)��","crroom "+arg+" $txt#")+"\n");
		else
			write(INPUTTXT("��ѡ����"HIY+dir[arg]+NOR"�����³���"ZJBR"��ȷ���������趨����������(2-5��������)��","crroom "+arg+" $txt#")+"\n");
		return 1;
	}
	else if(sizeof(attr)==2)
	{
		if(!is_chinese(attr[1]))
			return notify_fail(HIY"�������ֱ����Ǵ����ģ���"NOR"\n");
		if(strlen(attr[1])>12)
			return notify_fail(HIY"�����������ֻ����6�����֣���"NOR"\n");

		if(room_type=="price")
			write(INPUTTXT("�����趨�ĳ���������"HIY+attr[1]+NOR+ZJBR"�˵�������ҹ��������õأ���Ҫ֧��"+env->query("price_build")+"Ԫ���Ľ���ѡ�"ZJBR"ȷ������Ļ������趨������"HIG"Ӣ�Ĵ���"NOR+ZJBR"(id����Сд��ĸ��������ϣ������������ƣ����磺guangchang)��","crroom "+arg+" $txt#")+"\n");
		else
			write(INPUTTXT("�����趨�ĳ���������"HIY+attr[1]+NOR+ZJBR"ȷ������Ļ������趨������"HIG"Ӣ�Ĵ���"NOR+ZJBR"(id����Сд��ĸ��������ϣ������������ƣ����磺guangchang)��","crroom "+arg+" $txt#")+"\n");
		return 1;
	}
	else if(sizeof(attr)==3)
	{
		if(!dir[attr[0]])
			return notify_fail(HIY"����ѡ�����󣡣�"NOR"\n");
		if(env->query("exits/"+attr[0]))
			return notify_fail(HIY"�˷������г����˲����ظ���������"NOR"\n");
		if(!is_chinese(attr[1]))
			return notify_fail(HIY"�������ֱ����Ǵ����ģ���"NOR"\n");
		if(strlen(attr[1])>12)
			return notify_fail(HIY"�����������ֻ����6�����֣���"NOR"\n");
		if(!is_legal_id(attr[2]))
			return notify_fail(HIY"����Ӣ�Ĵ��ű����Ǵ�СдӢ�Ļ����֣���"NOR"\n");
		if(strlen(attr[2])>12)
			return notify_fail(HIY"����Ӣ�Ĵ������ֻ����12���ַ�����"NOR"\n");

		dirs = explode(base_name(env),"/");

		list = "//by ���� ranger's ednpc tools.\n";
		list += "// "+ attr[2]+".c\n\n";
		list += "#include <ansi.h>\n";
		list += "inherit ROOM;\n\n";
		list += "void create()\n{\n";
		list += "	set(\"short\",\""+attr[1]+"\");\n";
		list += "	set(\"long\",\"������"+attr[1]+"����������δ�趨������ϸ������\");\n";
		list += "	set(\"owner_build\",\""+me->query("id")+"\");\n";
		list += "	set(\"exits\", ([\n";
		list += "		\""+dir2[attr[0]]+"\" : \""+base_name(env)+"\",\n";
		list += "	]));\n";
		list += "	set(\"objects\", ([\n";
		list += "	]));\n";
		list += "	setup();\n";
		list += "}\n\n";

		dirs = dirs[0..(sizeof(dirs)-2)];
		if(room_type=="owner")
			str = "/"+implode(dirs,"/")+"/"+attr[2];
		else
			str = sprintf("/data/home/%c/%s/%s/%s",me->query("id")[0],me->query("id"),dirs[1],attr[2]);

		if(file_size(str+".c")>0)
			return notify_fail(HIY"ͬ���ļ��Ѵ��ڣ������Ӣ�Ĵ����ٴγ��ԣ���"NOR"\n");

		if(room_type=="price"&&me->query("yuanbao")<env->query("price_build"))
			return notify_fail(HIY"�����￪��������Ҫ����֧��"+env->query("price_build")+"Ԫ���ĵ�Ƥ�ѣ����Ԫ�����㣡��"NOR"\n");

		ling->add_amount(-1);
		me->add("yuanbao",-env->query("price_build"));
		BUILD_D->build_file(me,str+".c",list);

		list = BUILD_D->get_file_code(env);
		list = replace_string(list,"set(\"exits\", ([","set(\"exits\", ([\n		\""+attr[0]+"\" : \""+str+"\",");

		BUILD_D->build_file(me,base_name(env)+".c",list);
		env->set("exits/"+attr[0],str);

		write(HIY"������ϣ�������³���ͨ������̨�޸��趨��������������..."NOR"\n");
	}
	else
		return notify_fail("��ʽ���󣡣���ο�---���ƣ�"HIY"���Ĺ㳡"NOR"��id��"HIG"guangchang"NOR"������Ҫ�ô����ģ�Ӣ��id��Сд��ĸ����������ɡ�\n");
	return 1;
}
