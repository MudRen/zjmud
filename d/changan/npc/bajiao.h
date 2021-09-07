// bajiao.h Ⱥ��˽�

int accept_fight(object me)
{
	command("say СŮ�����������Ķ��֣�");
	return 0;
}

void init()
{
	remove_call_out ("says");
	call_out("says", random(3), this_player());
	add_action("do_makelove", "makelove");
}

void says(object me)
{
  	string *msgs = ({
    		"$N�Գ�һЦ�����쿴���㡣\n",
    		"$N���������ض���˵�������㡭���㻹����������������\n",
    		"����$N���������(makelove)һ��\n",
    		"$N������㡭��\n",
    		"$N�������һЦ��\n",
	});

	string msg;

	if (! me || environment(me) != environment() ||
	    ! living(this_object()))
		return;

	if (me->query("gender") != "����")
		msg = "$N���˺͹�Ƿ������ȥ�����ˡ�\n";
	else
		msg = msgs[random(sizeof(msgs))];

  	message_vision(msg, this_object());
}

int do_makelove()
{
  	object me = this_object();
  	object who = this_player();

	switch (who->query("gender"))
	{
	case "����":
		break;
	case "Ů��":
		return notify_fail("�㻹���Ⱞ�ã�û��������\n");
	default:
		return notify_fail("���ƺ�û���������ɣ�\n");
	}

	if (is_busy() || is_fighting())
		return notify_fail("��û�����˼���æ������\n");

	if (query_temp("makelove_with") == who)
	{
		write("��ú�����ģ������Ķ���ġ�\n");
		return 1;
	}

	if (query_temp("makelove_with"))
		return notify_fail("����һ���ϣ��㻹�������˼Ұɣ�\n");

  	message_vision(HIM "$N" HIM "����§��$n" HIM "�����"
		       "���壬���ɵ�һ������Ŀ�д���ȫ��"
		       "��֪�����Ŀ�ʼŤ���š���\n"NOR"\n", who, me);
  	who->command_function("remove all");
  	who->start_busy(300);

	// record sex
	who->add("sex/" + name(), 1);
	who->add("sex/times", 1);
	if (who->query("sex/times") == 1)
		who->set("sex/first", name());

	set_temp("makelove_with", who);

  	remove_call_out ("get_fainted");
  	call_out ("get_fainted", 1, who, me);
	remove_call_out("says");
	call_out("says", 40, me);
	return 1;
}

void get_fainted(object who, object me)
{
	object *objs = all_inventory(who);
	int i = sizeof(objs);

	delete_temp("makelove_with");

	if (! who || environment(who) != environment())
		return;

	message_vision("$N��$n���ص�һЦ��\n", me, who);
	who->unconcious();
	while (i--)
	{
	    	object obj = objs[i];
		if (obj->is_character())
			continue;
		if (! obj->query("money_id"))
			continue;
	    	message_vision("$N��$n�����ó�" +
			       obj->query("name") +
			       "��\n", me, who);
	    	destruct(obj);
		break;
	}

	if (i < 0)
		// Get nothing
		command("chat ���������ˣ�ԭ����һ�����");
}

int accept_kill(object me)
{       
	object ob;
	if (is_fighting()) return 1;
	if (query("called")) return 1;
	command("say Ҫɱ���ˣ������˾�������");
	ob = present("bao biao");
	if (! ob)
	{
		seteuid(getuid());
		ob=new(__DIR__"baobiao");
		ob->move(environment());
	}
	message_vision(HIC "\n��Ȼ�����������������ڣ���"
		       "$N" HIC "��һ������ʲô���������"
		       "�£���������\n"NOR"\n", me);
	ob->kill_ob(me);
	ob->set_leader(me);
	me->kill_ob(ob);
	set("called", 1);
	call_out("regenerate", 200);
	return notify_fail("�����ˣ�");
}

int regenerate()
{
	set("called", 0);
	return 1;
}
