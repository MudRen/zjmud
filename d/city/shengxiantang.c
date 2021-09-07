// by ranger_����
// JuYiTing.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "ʥ����");
	seteuid(ROOT_UID);
	set("channel_id", "ʥ����");
	set("long", "�������ֺ�����ͬʱ�ۼ��ڴˡ�����������������Ϊ���˵�ʦ����Ҳ����Ѱ��һλ�����ʦ�����㴳��������");
	set("exits", ([
		"south" : __DIR__"shuyuan",
	]));
	set("action_list", ([
		HIG"Ѱ��ʦ��"NOR:"xunshi",
		HIM"��ʦ��֤"NOR:"daoshizg",
		HIC"�г�ʦ��"NOR:"chushili",
		HIY"�������"NOR:"quzhu",
		HIR"�����ϵ"NOR:"tuoli",
	]));
	set("no_fight","1");
        set("no_sleep_room",1);
	setup();
}

void init()
{
	add_action("do_baishi","baishi");
	add_action("do_chushili","chushili");
	add_action("do_shoutu","shoutu");
	add_action("do_quzhu","quzhu");
	add_action("do_tuoli","tuoli");
	add_action("do_xunshi","xunshi");
	add_action("do_daoshizg","daoshizg");
}

int do_quzhu(string arg)
{
	int tm,i,last_on;
	string *dizi,str,err;
	object ob,obj,me=this_player();
	mapping user;

	if(!arg)
	{
		if(!mapp(user=me->query("p_dizi")))
			return notify_fail("�㻹û�е����أ�\n");
		dizi = sort_array(keys(user),1);
		if(!sizeof(dizi))
			return notify_fail("�㻹û�е����أ�\n");
		str = ZJOBLONG"��������������Щ���ӣ�����Ե��ѡ������ĳ�����ӣ�\n";
		str += ZJOBACTS2+ZJMENUF(2,2,6,30);
		for(i=0;i<sizeof(dizi);i++)
		{
			last_on = FINGER_D->get_last_on(dizi[i]);
			str += FINGER_D->get_name(dizi[i])+"��"HIG+dizi[i]+NOR"��"ZJBR"�ϴε�¼��"ZJBR+CHINESE_D->chinese_date(last_on,2)+":quzhu "+dizi[i]+ZJSEP;
		}
		tell_object(me,str+"\n");
		return 1;
	}

	if(sscanf(arg,"%s yes",arg)!=1)
	{
		if(!FINGER_D->get_name(arg))
			return notify_fail("��Ҫ����˭��\n");
		tell_object(me,ZJOBLONG"��ȷ��Ҫ����"+FINGER_D->get_name(arg)+"�������ô��\n"ZJOBACTS2"ȷ��:quzhu "+arg+" yes\n");
		return 1;
	}

	if(!objectp(obj=find_player(arg)))
	{
		ob = new(LOGIN_OB);
		ob->set("id",arg);
		ob->set("body", USER_OB);
		obj = LOGIN_D->make_body(ob);
		destruct(ob);
		if(obj->restore())
		{
			obj->setup();
			if(!me->query("p_dizi/"+obj->query("id")))
			{
				tell_object(me,"��û�����ͽ�ܣ�\n");
			}
			else
			{
				obj->delete("p_master");
				obj->delete("zjvip/master");
				obj->save();
				me->delete("p_dizi/"+obj->query("id"));
				me->save();
				tell_object(me,HIR"�������"+obj->query("name")+"("+obj->query("id")+")"+"�ɹ���"NOR"\n");
			}
		}else
			tell_object(me,"������ݴ���\n");

		destruct(obj);
	}
	else
	{
		if(!me->query("p_dizi/"+obj->query("id")))
		{
			tell_object(me,"��û�����ͽ�ܣ�\n");
		}
		else
		{
			obj->delete("p_master");
			obj->delete("zjvip/master");
			obj->save();
			me->delete("p_dizi/"+obj->query("id"));
			me->save();
			tell_object(me,HIR"�������"+obj->query("name")+"("+obj->query("id")+")"+"�ɹ���"NOR"\n");
			tell_object(obj,HIR+me->query("name")+"("+obj->query("id")+")"+"���������ʦ���ˣ�"NOR"\n");
		}
	}

	return 1;
}

int do_tuoli(string arg)
{
	int tm,i;
	string *dizi,str,err;
	object ob,obj,me=this_player();
	mapping user;

	if(!stringp(str=me->query("p_master/id")))
	{
		if(!stringp(str=me->query("zjvip/master")))
		{
			tell_object(me,"�㻹û�и��κ���ұ���ʦͽ��ϵ���������룡\n");
			return 1;
		}
	}

	if(arg!="yes")
	{
		tell_object(me,ZJOBLONG"��ȷ��Ҫ��"+FINGER_D->get_name(str)+"����ʦ����ϵô��\n"ZJOBACTS2"ȷ��:tuoli yes\n");
		return 1;
	}

	if(!stringp(me->query("p_master/id")))
	{
		me->delete("zjvip/master");
		tell_object(me,"����"+FINGER_D->get_name(str)+"�Ӵ�֮�����޹ϸ�\n");
		return 1;
	}

	if(!objectp(obj=find_player(str)))
	{
		ob = new(LOGIN_OB);
		ob->set("id",str);
		ob->set("body", USER_OB);
		obj = LOGIN_D->make_body(ob);
		destruct(ob);
		if(obj->restore())
		{
			obj->setup();
			if(me->query("p_master/id")!=obj->query("id"))
			{
				tell_object(me,"��û�����ʦ����\n");
			}
			else
			{
				obj->delete("p_dizi/"+me->query("id"));
				obj->save();
				me->delete("p_master");
				me->delete("zjvip/master");
				me->save();
				tell_object(me,HIR"����"+obj->query("name")+"("+obj->query("id")+")"+"����ʦͽ��ϵ�ˣ�"NOR"\n");
			}
		}else
			tell_object(me,"������ݴ���\n");

		destruct(obj);
	}
	else
	{
		if(me->query("p_master/id")!=obj->query("id"))
		{
			tell_object(me,"��û�����ʦ����\n");
		}
		else
		{
			me->delete("p_master");
			me->delete("zjvip/master");
			me->save();
			obj->delete("p_dizi/"+me->query("id"));
			obj->save();
			tell_object(me,HIR"����"+obj->query("name")+"("+obj->query("id")+")"+"����ʦͽ��ϵ�ˣ�"NOR"\n");
			tell_object(obj,HIR+me->query("name")+"("+obj->query("id")+")"+"����������ʦͽ��ϵ��"NOR"\n");
		}
	}

	return 1;
}

int do_xunshi(string arg)
{
	string *str,strs,zige;
	int i,j,ye,yeall;
	object ob,*ob_list;

	if(!arg) arg = "1";
	str = ({});
	if( sscanf(arg, "%d", ye)==1)
	{
		ob_list = users();
		ob_list = sort_array(users(), "sort_user", this_object());
		for(i=0; i<sizeof(ob_list); i++)
		{
			ob = ob_list[i];
			if(ob->is_character()&&ob->query("zjvip/daoshizg"))
			{
				if(ob->query("zjvip/daoshizg")>5)
					zige = "һ��ʥ��";
				else if(ob->query("zjvip/daoshizg")==5)
					zige = "��������";
				else if(ob->query("zjvip/daoshizg")==4)
					zige = "��������";
				else if(ob->query("zjvip/daoshizg")==3)
					zige = "��ʦ����";
				else if(ob->query("zjvip/daoshizg")==2)
					zige = "�߼�ʦ��";
				else if(ob->query("zjvip/daoshizg")==1)
					zige = "����ʦ��";
				str += ({sprintf("%s��%s:baishi %s",zige,ob->query("name"),ob->query("id"))});
			}
		}

		if(!sizeof(str))
			write("Ŀǰ����"HIY"��ҵ�ʦ"NOR"���ߣ�\n");
		else
		{
			strs = ZJOBLONG"Ŀǰ�����µ�ʦ������ͽ��\n";

			strs += ZJOBACTS2+ZJMENUF(2,2,9,30);

			yeall = sizeof(str)/10;
			if(sizeof(str)%10) yeall += 1;
			if(ye<1) ye = 1;
			if(ye>yeall) ye = yeall;
			j = (ye-1)*10;
			i = ye*10;
			if (i >= sizeof(str)) i = sizeof(str);
			i--;
			if(yeall>1)
				strs += "��һҳ:xunshi "+(ye-1)+ZJSEP"��һҳ:xunshi "+(ye+1)+ZJSEP;
			strs += implode(str[j..i], ZJSEP);
			write(strs+"\n");
		}
	}
}

int sort_user(object ob1, object ob2)
{
	if(ob2->query("zjvip/daoshizg")==ob1->query("zjvip/daoshizg"))
		return ob2->query("combat_exp") - ob1->query("combat_exp");
	else 
		return ob2->query("zjvip/daoshizg") - ob1->query("zjvip/daoshizg");
}

int do_daoshizg()
{
	int i;
	string *dizi;
	string *dszg = ({HIW"����ʦ��"NOR,HIG"�߼�ʦ��"NOR,HIB"��ʦ����"NOR,HIM"��������"NOR,HIY"��������"NOR,HIR"һ��ʥ��"NOR});
	object me=this_player();

	if(me->query("combat_exp")<500000)
		return notify_fail("�����ڻ�û������ҵ�ʦ���ʸ�\n����Ҫ"HIB"100w����"NOR"������ͽ��\n");
	if(!me->query("zjvip/daoshizg"))
	{
		me->set("zjvip/daoshizg",1);
		return notify_fail("��ϲ������ĵ�ʦ�ʸ���֤�ɹ�������\n�����ڵĵ�ʦ�ʸ���"HIW"������ʦ����"NOR"��\n");
	}
	else if(me->query("zjvip/daoshi_exp")>49&&me->query("zjvip/daoshizg")<6&&!me->query("p_master/id"))
	{
		me->set("zjvip/daoshizg",6);
		return notify_fail("��ϲ����ĵ�ʦ�ʸ����Ϊ"HIM"��һ��ʥ�͡�"NOR"��\n");
	}
	else if(me->query("zjvip/daoshi_exp")>19&&me->query("zjvip/daoshizg")<5&&!me->query("p_master/id"))
	{
		me->set("zjvip/daoshizg",5);
		return notify_fail("��ϲ����ĵ�ʦ�ʸ����Ϊ"HIM"���������¡�"NOR"��\n");
	}
	else if(me->query("zjvip/daoshi_exp")>9&&me->query("zjvip/daoshizg")<4&&!me->query("p_master/id"))
	{
		me->set("zjvip/daoshizg",4);
		return notify_fail("��ϲ����ĵ�ʦ�ʸ����Ϊ"HIM"������������"NOR"��\n");
	}
	else if(me->query("zjvip/daoshi_exp")>4&&me->query("zjvip/daoshizg")<3&&!me->query("p_master/id"))
	{
		me->set("zjvip/daoshizg",3);
		return notify_fail("��ϲ����ĵ�ʦ�ʸ����Ϊ"HIB"����ʦ���ѡ�"NOR"��\n");
	}
	else if(me->query("zjvip/daoshi_exp")>2&&me->query("zjvip/daoshizg")<2 && !me->query("p_master/id"))
	{
		me->set("zjvip/daoshizg",2);
		return notify_fail("��ϲ����ĵ�ʦ�ʸ����Ϊ"HIG"���߼�ʦ����"NOR"��\n");
	}
	else
	{
		if(!me->query("p_dizi"))
		{
			return notify_fail("�����ڵĵ�ʦ�ʸ���"+dszg[me->query("zjvip/daoshizg")-1]+"���������"+(me->query("zjvip/daoshizg")*3+3)+"�����ӣ��㻹û��ͽ�ܣ�\n");
		}
		dizi = keys(me->query("p_dizi"));
		return notify_fail("�����ڵĵ�ʦ�ʸ���"+dszg[me->query("zjvip/daoshizg")-1]+"���������"+(me->query("zjvip/daoshizg")*3+3)+"�����ӣ�������"+sizeof(dizi)+"�����ӡ�\n");
	}
}

int do_baishi(string arg)
{
	int i;
	string *dizi;
	object ob,me=this_player();
	mapping user;

	if(!arg)
		return notify_fail("����Ҫ��˭Ϊ��ʦ��\n");
	else if(!(ob = find_player(arg)))
		return notify_fail("�������ʦô��\n");
	else if(ob==me)
		return notify_fail("�Լ����Լ��������뷨����\n");
	else if(me->query("p_master/id"))
		return notify_fail("���Ѿ��е�ʦ�ˣ��������ðɣ�\n");
	else if(me->query("zjvip/out_master"))
		return notify_fail("�㶼�Ѿ���ʦ������ʲôʦ��\n");

	if(!ob->query("zjvip/daoshizg"))
	{
		return notify_fail("�Է�û�е�ʦ�ʸ�\n");
	}
	else if(me->query("zjvip/daoshizg"))
	{
		return notify_fail("��Ҳ���е�ʦ�ʸ�����ˣ��Ͳ���Ҫ��ʦ�˰ɣ�\n");
	}
	else if(me->query("combat_exp")>500000)
	{
		return notify_fail("�����ڵĽ��������㹻�����˵ĵ�ʦ�˻���ȥ��֤һ�µ�ʦ�ʸ���Щͽ�ܰɣ�\n");
	}
	else
	{
		me->set_temp("baishi",ob);
		if(environment(ob)!=this_object())
		{
			tell_object(ob,ZJSIZE(25)+HIC+me->query("name")+NOR"��Ҫ"ZJSIZE(25)+HIM"����Ϊʦ"NOR"�����ͬ��Ļ��Ͻ�ȥ��Ե��ȷ�Ϲ�ϵ��\n");
			return notify_fail("��ʦ�����ѷ�������ȴ��𸴣�����յ���ʦ�𸴣��ȵ�ʦ���������ٴη��Ͱ�ʦָ�\n");
		}
		else
		{
			tell_object(ob,ZJSIZE(25)+HIC+me->query("name")+NOR"��Ҫ"ZJSIZE(25)+HIM"����Ϊʦ"NOR"�����"ZJURL("cmds:shoutu "+me->query("id"))+ZJSIZE(22)+HIY"ͬ��"NOR"�Ļ��Ͻ�����ȷ�ϡ�\n");
			return notify_fail("��ʦ�����ѷ�������ȴ���ʦ�𸴡�\n");
		}
	}
	return 1;
}

int do_chushili()
{
	int i;
	string *dizi;
	object chushili,ob,ob1,me=this_player();
	mapping user;

	if(me->query("combat_exp")<500000)
		return notify_fail("���������㻹�����ʸ��ʦ��\n");
	else if(me->query("zjvip/out_master"))
		return notify_fail("�㶼�Ѿ���ʦ�ˣ�������ʲôʦ��\n");
	else if(!me->query("p_master/id"))
		return notify_fail("�㶼û�е�ʦ����ʲôʦ��\n");
	else if(!(ob=UPDATE_D->global_find_player(me->query("p_master/id"))))
	{
		return notify_fail("���е�ʦ��\n");
	}
	else
	{
		me->delete("p_master");
		ob->delete("p_dizi/"+me->query("id"));
		ob->add("zjvip/daoshi_exp",1);
		if(!me->query("zjvip/out_master"))
		{
			ob1 = new("/clone/shizhe/masterbox");
                        ob1->move(me);
			tell_object(me,"��ʦ��ʽ��ɣ�������һ��"HIM"��ʦ���"NOR"��\n");
			me->add("zjvip/out_master",1);
		}
		CHANNEL_D->do_channel(me,"chat","�����������ɵ�ʦ"+ob->query("name")+"Ϥ���չ�ָ���������ڴ���ͽ�����һ�ݣ�");
	}
	return 1;
}

int do_shoutu(string arg)
{
	int i;
	string *dizi;
	object obj,ob,me=this_player();
	mapping user;

	if(!arg)
		return notify_fail("����Ҫ��˭Ϊͽ��\n");
	else if(!(ob = find_player(arg)))
		return notify_fail("�������ô��\n");
	else if(ob==me)
		return notify_fail("������Ҫ���찡��\n");

	if(me->query("p_master/id"))
		return notify_fail("�㻹û��ʦ������ͽ����\n");

	if(me->query("p_dizi"))
	{
		dizi = keys(me->query("p_dizi"));
	}

	if(ob->query_temp("baishi")!=me)
	{
		return notify_fail("��������ͽ�ܣ��˼�û�����ɣ�\n");
	}
	else if((me->query("zjvip/daoshizg")*3+3)<=sizeof(dizi))
	{
		return notify_fail("�����ڵĵ����Ѿ������ˣ����Ƕ��չ��չ�δ��ʦ�ĵ��Ӱɣ�\n");
	}
	else if(sizeof(dizi)&&member_array(ob->query("id"),dizi)!=-1)
	{
		return notify_fail(ob->query("name")+"��������ĵ����˰ɣ�\n");
	}
	else
	{
		ob->delete_temp("baishi");
		if(environment(ob)==this_object())
		{
			ob->set("p_master/name",me->query("name"));
			ob->set("p_master/id",me->query("id"));
			ob->set("p_master/qinmi",1);
			me->set("p_dizi/"+ob->query("id")+"/name",ob->query("name"));
			me->set("p_dizi/"+ob->query("id")+"/qinmi",1);
			if(!ob->query("baishi_times"))
			{
				tell_object(ob,"��ʦ�ɹ����Ͻ���ʦ��ѧϰһЩ�������߾��飬��ʦ��ҪЩ���߽�������Ʒ���߽����ɣ�\n");
			}
			else
				tell_object(ob,"��ʦ�ɹ�����ոϽ�����ʦ�����̰ɣ�\n");
			ob->add("baishi_times",1);
			ob->set("zjvip/master",me->query("id"));
			CHANNEL_D->do_channel(me,"chat","pat "+ob->query("id"),1);
			CHANNEL_D->do_channel(this_object(),"chat","��ϲ"HIM+me->query("name")+"��"+ob->query("name")+"����ʦͽ֮Ե"NOR"��ף"+ob->query("name")+"���ճ�ʦ������������");
			return notify_fail("��ϲ�������յ�һ���ӵܣ����������ָ�����������ճ�ʦ�ɡ�\n");
		}
		else
		{
			tell_object(ob,"��ʦʧ�ܣ����Ѿ��뿪ʥ�����ˣ�\n");
			return notify_fail("��ͽʧ�ܣ��Է��Ѳ������\n");
		}
	}
	return 1;
}
