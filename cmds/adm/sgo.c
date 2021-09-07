// goto.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int i;
	object obj;
	object env;
	string *dirs,msg,name;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	if(!sizeof(MAP_D->query_all_city()))
		return notify_fail(ZJOBLONG"����Ϸ��δ�п��õ�ͼ��\n");

	if (! arg)
	{
		msg = ZJOBLONG"��ѡ��Ŀ������\n"ZJOBACTS2+ZJMENUF(3,3,10,30);
		dirs = sort_array(MAP_D->query_all_city(),(: strcmp :));
		for(i=0;i<sizeof(dirs);i++)
		{
			msg += MAP_D->query(dirs[i]+"/short")+":goto /d/"+dirs[i];
			if(i<(sizeof(dirs)-1)) msg += ZJSEP;
		}
		write(msg+"\n");
		return 1;
	}

	if(file_size(arg)==-2)
	{
		msg = ZJOBLONG"��ѡ��Ŀ�곡����\n"ZJOBACTS2+ZJMENUF(3,3,10,33);
		dirs = sort_array(list_dirs(arg+"/"),(: strcmp :));
		for(i=0;i<sizeof(dirs);i++)
		{
			if(sscanf(dirs[i],"%s.c",dirs[i])==1)
			{
				name = arg+"/"+dirs[i];
				msg += name->short()+ZJBR+dirs[i]+":goto "+name;
			}
			else if(file_size(arg+"/"+dirs[i]) == -2)
			{
				name = arg+"/"+dirs[i];
				sscanf(name,"/d/%s",name);
				msg += MAP_D->query(replace_string(name,"/","/sub/")+"/short")+ZJBR+dirs[i]+":goto "+"/d/"+name;
			}
			if(i<(sizeof(dirs)-1)) msg += ZJSEP;
		}
		write(msg+"\n");
		return 1;
	}

	obj = find_player(arg);
	if (! obj) obj = find_living(arg);
	if (! obj || ! me->visible(obj))
	{
		arg = resolve_path(me->query("cwd"), arg);
		if (! sscanf(arg, "%*s.c") ) arg += ".c";
		if (! (obj = find_object(arg)))
		{
			if (file_size(arg)>=0)
				obj = load_object(arg);

			if (! obj)
				return notify_fail("û�������ҡ������ط���\n");
		}
	}

	if (environment(obj))
		obj = environment(obj);
	else
	{
		if (obj->is_character())
			obj = 0;
	}

	if (! obj) return notify_fail("������û�л������� goto��\n");

	if (wiz_level(obj) > wiz_level(me))
		return notify_fail("����������\n");

	if ((env = environment(me)) == obj)
		return notify_fail("����ԭ���ұ�ʲô��\n");

	if (obj == me)
		return notify_fail("�������������굽�Լ��������棿\n");

	if (obj->query("no_goto"))
		return notify_fail("���޷������Ǹ��ط���\n");

	if (me->query("gender") == "Ů��" )
		tell_object(me, HIG "�㻯������ȥ��"NOR"\n");
	else
		tell_object(me, HIY "�㻯�������ȥ��"NOR"\n");
		
	if (env && ! me->query("env/invisible"))
	{
		if (! stringp(msg = me->query("env/msg_out")))
			msg = "ֻ��һ��������ᣬ$N����Ӱ�Ѿ������ˡ�";

		msg = replace_string(msg, "$N", me->name() + HIM);
		message("vision", HIM + msg + ""NOR"\n", env, ({ me, env }));
	}

	if (! me->query("env/invisible"))
	{
		if (! stringp(msg = me->query("env/msg_in")))
			msg = "$N����ӰͻȻ������һ������֮�С�";
		msg = replace_string(msg, "$N", me->name());
		if (! obj->is_character())
			message("vision", HIM + msg + ""NOR"\n", obj, ({ me, obj }));
	}

	me->set_magic_move();
	if (! me->move(obj))
	{
		msg = HIM "��Ķ���ʧ���ˡ�"NOR"\n";
		tell_object(me, msg);
		message("vision", HIM "ͻȻ" + me->name() + "һ����ͷ"
				  "ˤ���ڵ��ϡ�"NOR"\n", obj, ({ me }));
		return 1;
	}
	else
		msg = HIM "�㵽�˵ط������¶ݹ⣬��ס���Ρ�"NOR"\n";

	if (environment(me) != obj)
		return 1;

	tell_object(me, msg);

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : goto [-i] <Ŀ��>
 
���ָ��Ὣ�㴫�͵�ָ����Ŀ��. Ŀ�������һ��living �򷿼�
�ĵ���. ���Ŀ����living , ��ᱻ�Ƶ����Ǹ���ͬ���Ļ���.
����м��� -i ������Ŀ���� living, ����ᱻ�Ƶ��� living ��
�� inventory ��.
 
HELP );
	return 1;
}
