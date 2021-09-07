// guarder.c

#include <ansi.h>

int is_guarder() { return 1; }

int permit_pass(object ob, string dir)
{
	object *inv;
	string fam_name;
	string my_fam;
	string born_fam;
	string msg;
	int i;
        object tongxing1;

	 //walker����
	if (! living(this_object()) || ob->query("attitude") == "heroism" )
		return 1;

	if(this_object()->query("id")=="kong jian" && objectp(tongxing1=present("tongxing ling1",ob)) && dir == "north")
	{
	      message_vision("$N�ݸ��ռ�һöͨ�����ơ�\n", ob);
		command("say ԭ���Ƕ���һ��Ĺ�����ˣ���λ" + RANK_D->query_respect(ob) + "�����룡");
		destruct(tongxing1);
		return 1;
	}
//����  feature/guarder
	if(this_object()->query("id")=="ping si" && objectp(tongxing1=present("tongxing ling1",ob)) && dir == "north")
	{
	      message_vision("$N�ݸ�ƽ��һöͨ�����ơ�\n", ob);
		command("say ԭ���Ƕ���һ��Ĺ�����ˣ���λ" + RANK_D->query_respect(ob) + "�����룡");
		destruct(tongxing1);
		return 1;
	}

	notify_fail("����" + this_object()->name() + "�����������ȥ��\n");
	fam_name = ob->query("family/family_name");
	my_fam   = (string) this_object()->query("family/family_name");
	born_fam = (string) ob->query("born_family");
	if (born_fam == my_fam && fam_name && fam_name != my_fam)
	{
		if (stringp(msg = this_object()->query("guarder/refuse_home")))
			message_vision(msg + "\n", this_object(), ob);
		else
			message_vision("$N����Ŀ��˿�$n���������Ȼ�Ѿ�����" +
				       fam_name + "����������" + my_fam +
				       "��ʲô��\n", this_object(), ob);
		return 0;
	}

	if (my_fam != fam_name && my_fam != born_fam)
	{
		if (stringp(msg = this_object()->query("guarder/refuse_other")))
			message_vision(msg + "\n", this_object(), ob);
		else
			message_vision("$N������ס$n�������Բ��𣬲�������" + my_fam +
				       "�˲������ڣ�\n", this_object(), ob);
		return 0;
	}

	inv = deep_inventory(ob);
	for (i = 0; i < sizeof(inv); i++)
	{
		if (! playerp(inv[i])) continue;
		if ((string) inv[i]->query("family/family_name") != fam_name)
		{
			if (stringp(msg = this_object()->query("guarder/refuse_carry")))
				message_vision(msg + "\n", this_object(), ob);
			else
				message_vision("$N��$n�ȵ����㱳����˭�����������£�\n",
					       this_object(), ob);
			return 0;
		}
	}

	return 1;
}

void kill_enemy(object ob)
{
	mixed result;

	mapping *co;
	string startroom;
	object room;
	object coagent;
	object me;
	int i;
	int flag;

	me = this_object();
	if ((int)ob->query("combat_exp") < (int)me->query("combat_exp") / 2)
		return;

	if (!pointerp(co = me->query("coagents")))
		return;

	if (sizeof(co) < 1)
		return;

	if (base_name(environment(me)) != (string)me->query("startroom"))
		return;

	message_vision(random(2) ? HIW "\n$N������������ҿ�����æ����"NOR"\n" :
				   HIW "\n$N�ȵ������ã��������������ˣ�"NOR"\n", me);
	flag = 0;
	for (i = 0; i < sizeof(co); i++)
	{
		if (! mapp(co[i])) continue;

		startroom = co[i]["startroom"];
		if (! objectp(room = find_object(startroom)))
		{
			result = catch(room = load_object(startroom));
			if (! objectp(room))
			{
				if (wizardp(this_object()))
					write(sprintf("Error to load object:%s\nCatch message:%s\n\n",
					      startroom, result));
				continue;
			}
		}

		if (! objectp(coagent = present(co[i]["id"], room)) &&
		    ! objectp(coagent = present(co[i]["id"], environment())) ||
		    ! coagent->is_coagent() ||
		    coagent == this_object())
			continue;

		flag += (int)coagent->start_help(environment(), me, ob);
	}

	if (! flag)
		message_vision("���û��һ���˳��� :)\n", me);
}

int check_enemy(object ob, string type)
{
	mapping myfam;
	object me;

	me = this_object();
	myfam = ob->query("family");
	if (! mapp(myfam) || ! myfam ||
		myfam["family_name"] != me->query("family/family_name"))
	{
		if (type == "fight")
		{
			message_vision("$N��$nҡҡͷ����������û�ա�\n\n", me, ob);
			return 0;
		} else
		{
			message_vision("$N��ȵ��������" + RANK_D->query_rude(ob) +
				       "����ò��ͷ��ˣ���������Ұ��\n", me, ob);
			me->kill_ob(ob);
		}
	} else
	switch (type)
	{
	case "hit":
	case "kill":
		message_vision("$N����һ�ɣ��ȵ���" + ob->query("name") +
			       "������Ҫ�췴��\n", me, ob);
		me->kill_ob(ob);
		break;

	case "fight":
		if (ob->is_apprentice_of(me))
			message_vision("$Nһ��$n��ŭ��������Һú�����ȥ��\n", me, ob);
		else
			message_vision("$N��$nҡҡͷ���������ʦ���Ȼ�ȥ��\n\n", me, ob);
		return 0;
	}

	return 1;
}
