// gaibang.h for fight and get ������

int accept_object(object ob, object obj)
{
	object me = this_object();

	mapping my_fam  = me->query("family");
	mapping ob_fam  = ob->query("family");

	if (obj->query("id") != "qingzhu ling")
	{
		command("say ɶ���գ��Ը����Űɣ�");
		return 0;
	}

	if (! ob_fam || ob_fam["family_name"] != "ؤ��")
	{
		command("say ���������������");
		return 0;
	}

	if (ob->query("combat_exp") < 1000)
	{
		command("say ���˹��ˣ�������ˮƽ��������ô������������");
		return 0;
	}

	if (ob->query_temp("have_cloth") && present("po bu", ob))
	{
		command("say �㲻���Ѿ����Ʋ�ô?");
		return 0;
	}

	if (((ob->query("beggarlvl") == 0) &&
	     (ob->query("combat_exp") <= 1000)) ||
	    ((ob->query("beggarlvl") == 1) &&
	     (ob->query("combat_exp") <= 2000)) ||
	    ((ob->query("beggarlvl") == 2) &&
	     (ob->query("combat_exp") <= 5000)) ||
	    ((ob->query("beggarlvl") == 3) &&
	     (ob->query("combat_exp") <= 8000)) ||
	    ((ob->query("beggarlvl") == 4) &&
	     (ob->query("combat_exp") <= 10000)) ||
	    ((ob->query("beggarlvl") == 5) &&
	     (ob->query("combat_exp") <= 30000)) ||
	    ((ob->query("beggarlvl") == 6) &&
	     (ob->query("combat_exp") <= 100000)) ||
	    ((ob->query("beggarlvl") >= 7) &&
	     (ob->query("combat_exp") <= 300000)))
	{
	     command("say �����ǵ�ŧˮ���ҿ������˰ɡ�\n");
	     return 0;
	}

	if (((ob->query("beggarlvl") == 0) &&
	     (me->query("title") == "ؤ��һ������")) ||
	    ((ob->query("beggarlvl") == 1) &&
	     (me->query("title") == "ؤ���������")) ||
	    ((ob->query("beggarlvl") == 2) &&
	     (me->query("title") == "ؤ����������")) ||
	    ((ob->query("beggarlvl") == 3) &&
	     (me->query("title") == "ؤ���Ĵ�����")) ||
	    ((ob->query("beggarlvl") == 4) &&
	     (me->query("title") == "ؤ���������")) ||
	    ((ob->query("beggarlvl") == 5) &&
	     (me->query("title") == "ؤ����������")) ||
	    ((ob->query("beggarlvl") == 6) &&
	     (me->query("title") == "ؤ���ߴ�����")) ||
	    ((ob->query("beggarlvl") == 7) &&
	     (me->query("title") == "ؤ��˴�����")) ||
	    ((ob->query("beggarlvl") == 8) &&
	     (me->query("title") == "ؤ��Ŵ�����")))
	{
		if (! ob->query_temp("have_cloth"))
		{
			ob->set_temp("fight_ok", me->query("id"));
			command("say �ã���Ȼ����������ǾͿ���������ˡ�\n");
			destruct(obj);
			return 1;
		}
	}

	command("smile");
	command("say ������Ȼֻ������������Ҳ�ǲ��еġ�\n");
	command("say �ⶫ�����㻹���Լ����Űɡ�\n");
	return 0;
}

int accept_fight(object ob)
{
	if (query_competitor() == ob)
		return 1;

	if (ob->is_fightint())
		return notify_fail("�˼����ڱ����أ�����ô���ֲ�̫�׵��ɣ�\n");

	if (ob->query("family/family_name") != query("family/family_name"))
	{
		command("say ��...�ҿ�û��Ȥ���㶯�֡�");
		return 0;
	}

	if (ob->query_temp("fight_ok") != query("id"))
	{
		command("say ����������Ҫ���������������ҡ�");
		return 0;
	}

	ob->delete_temp("fight_ok");
	command("say �ã���������һ��������֣������㾿����ɶˮƽ��");
	competition_with(ob);
	return 1;
}

void lost()
{
	object ob;
	object obj;

	ob = query_competitor();
	command("say ��ү��������ã�����������������Ʋ��Ҽ���ȥ��");
	message_vision("$N����$nһ���Ʋ���\n", this_object(), ob);
	ob->set_temp("newtitle", query("title"));
	ob->set_temp("have_cloth",1);
	obj = new(__DIR__"obj/po-bu");
	obj->move(ob, 1);
	::lost();
}

void win()
{
	object ob;

	ob = query_competitor();
	if (! objectp(ob))
	{
		command("heihei");
		return;
	}
	command("say �������" + RANK_D->query_rude(ob) +
		"Ҳ��������Ҳ�������Լҳ��˼���ë��");
	::win();
}

int permit_recruit(object ob)
{
	if (ob->query("detach/ؤ��") || ob->query("betrayer/ؤ��"))
	{
		command("say ��������Ի�ͷ�ݣ�û�ţ�");
		return 0;
	}

	if (ob->query("betrayer/times"))
	{
		command("say ����ؤ����Ȼ�ǽл��ӣ���������������·����"
			"������ʦ֮ͽ�ģ�");
		return 0;
	}

	if (ob->query("family/family_name") &&
	    ob->query("family/family_name") != "ؤ��")
	{
		command("say �٣����Ȼ�Ѿ�������ʦָ�㣬��������ؤ���ʲô��");
		return 0;
	}

	return 1;
}
