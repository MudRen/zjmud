// guard.c

inherit F_CLEAN_UP;

mapping default_dirs = ([
	"north":	"��",
	"south":	"��",
	"east":	 "��",
	"west":	 "��",
	"northup":      "����",
	"southup":      "�ϱ�",
	"eastup":       "����",
	"westup":       "����",
	"northdown":    "����",
	"southdown":    "�ϱ�",
	"eastdown":     "����",
	"westdown":     "����",
	"northeast":    "����",
	"northwest":    "����",
	"southeast":    "����",
	"southwest":    "����",
	"up":	   "��",
	"down":	 "��",
	"out":	  "��",
	"in" :	  "��",
	"enter" :       "����",
]);

int main(object me, string arg)
{
	string dir;
	string id;
	object ob, *guards;
	object env;
	mixed old_target;
	 write( L_ICON("05027"));  
	if (me->is_busy() || me->is_fighting())
		return notify_fail("������û�а취����ȥ�������£�\n");

	old_target = me->query_temp("guardfor");

	if (! arg || arg == "")
	{
		if (objectp(old_target))
			if (living(old_target))
				write("�������ػ���" + old_target->name() +
				      "��\n");
			else
				write("��������" + old_target->name() +
				      "һ�ԣ���ֹ�������ߡ�\n");
		else
		if (stringp(old_target))
			write("������ס��" + default_dirs[old_target] +
			      "�ķ��򣬲�׼ " + me->query_temp("guardfor_id") +
			      " ���뿪��\n");
		else
			return notify_fail("ָ���ʽ��guard <����> | "
					   "<��Ʒ> | <����>\n");

		return 1;
	}

	env = environment(me);
	ob = present(arg, env);

	if (ob)
	{
		if (ob == me)
			return notify_fail("�����Լ�������˵��Ҳ��"
					   "�����԰ɡ�\n");
		if (me->query("jing") * 100 / me->query("max_jing") < 60)
			return notify_fail("�������޷����о�������" + ob->name() + "��\n");
		me->set_temp("guardfor", ob);
	} else
	if (sscanf(arg, "%s for %s", arg, id) == 2 && 
	    env->query("exits/" + arg))
	{
		if (id == me->query("id"))
			return notify_fail("�����ӽ�ˮ�ˣ�\n");

		if (env->query("no_fight"))
			return notify_fail("���ﲻ׼ս������Ҳ��׼��ס����ȥ·��\n");

		if (me->query("jing") * 100 / me->query("max_jing") < 75)
			return notify_fail("�������޷����о��������������\n");

		me->set_temp("guardfor", arg);
		me->set_temp("guardfor_id", id);
	} else
	if (arg != "cancel")
		return notify_fail("��Ҫ����˭��ʲô�������ĸ�����\n");

	if (objectp(old_target))
	{
		if (arrayp(guards = old_target->query_temp("guarded")))
		{
			guards -= ({ me, 0 });
			if (! sizeof(guards))
			{
				old_target->delete_temp("guarded");
			} else
				old_target->set_temp("guarded", guards);
		}
		if (interactive(old_target))
			tell_object(old_target, me->name() +
				    "���ٱ������ˡ�\n");
	} else
	if (stringp(old_target))
	{
		guards = env->query_temp("guarded/" + old_target);
		if (arrayp(guards))
		{
			guards -= ({ me, 0 });
			if (! sizeof(guards))
			{
				env->delete_temp("guarded/" + old_target);
			} else
				env->set_temp("guarded/" + old_target, guards);
		}
	}
	me->delete_temp("guardfor");

	if (arg=="cancel")
	{
		write("ʲôҲ�������ˣ����Ǻ����ɡ�\n");
		return 1;
	}

	if (objectp(ob))
	{
		guards = ob->query_temp("guarded");
		if (! arrayp(guards))
			guards = ({ me });
		else
		{
			guards -= ({ 0 });
			guards += ({ me });
		}
		ob->set_temp("guarded", guards);
		if (ob->query("no_guard"))
			message_vision("$n��������Ը�����$N�ı���"
				       "��\n", me, ob);
		else
		if (living(ob))
			message_vision("$N��ʼ����$n��\n", me, ob);
		else
			message_vision("$Nվ�����ϵ�$nһ����������"
				       "�����ȡ�ߡ�\n", me, ob);
		me->set_temp("guardfor", ob);
	} else
	{
		guards = env->query_temp("guarded/" + arg);
		if (! arrayp(guards))
			guards = ({ me });
		else
		{
			guards -= ({ 0 });
			guards += ({ me });
		}
		env->set_temp("guarded/" + arg, guards);
		message("vision", me->name() + "�����������������ܣ�"
				  "��֪��Ҫ��ʲô��\n", env, ({ me }));
		tell_object(me, "�㿪ʼ��ס��" + default_dirs[arg] +
				"�ķ����� " + me->query_temp("guardfor_id") +
				" ͨ�С�\n", me);
		me->set_temp("guardfor", arg);
	}

	return 1;
}

int help(object me)
{
	write(@TEXT
ָ���ʽ��guard [<ĳ��>|<����ĳ��>|<ĳ������> for <ĳ��>|cancel]

���ָ�����������÷�ʽ���ֱ����

guard <ĳ��>      ����<ĳ��>�����������ܵ�����ʱ�������߻���
		  ������ս����

guard <����ĳ��>  ��ס���ڵ��ϵ�ĳ����������ֹ�������ã�ֻҪ
		  �㻹��������䣬����û��æ�������£����˾�
		  �޷��������������

guard <ĳ������>..��סĳ�����ڷ�ָֹ�����˴���������뿪����
		  �����������������ܵĵ��˻���·��������£�
		  ����㵱ʱ��æ�������赲���ˡ�

guard cancel      ȡ����ǰ�� guard ����

ע�⣬ֻҪ��һ�ƶ�������Ʒ�ͳ��ڵ�����״̬�ͻ��������Ƕ���
��ı���״̬��Ȼ��Ч��ֻҪ�㵽�˱�������������Ȼ�������á�
���⣬����������״̬��ʱ�򣬻����ľ�������������ˣ�����Զ�
�������״̬��
TEXT );
	return 1;
}
