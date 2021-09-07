// wulaoda.c

inherit NPC;

string ask_me();
int ask_duihuan();

mapping list = ([
	"/clone/gift/xiaohuan" : 150,
	"/clone/gift/lingzhi" : 150,
	"/clone/gift/putao" : 100,
	"/clone/gift/tianxiang1" : 400,
]);

void create()
{
	set_name("���ϴ�", ({ "wu laoda", "wu" }));
	set("gender", "����");
	set("age", 47);

	set("inquiry", ([
		"���˴���" : (: ask_me :),
		"���ֵ���" : (: ask_duihuan :),
	]));

	setup();
	carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
	add_action("do_sign", "sign");
	add_action("do_join", "join");
	add_action("do_duihuan", "duihuan");
}

void unconcious()
{
	die();
}

void die()
{
	message_vision("$N���˸����磬�漴�ָ�������\n", this_object());
}

int ask_duihuan()
{
	int i;
	string str,*items;
	object me = this_player();

	str = ZJOBLONG"��Ŀǰ���õĶһ����ֻ���"+me->query("pkd_pot")+"�㣬��ѡ��һ���Ʒ��\n"ZJOBACTS2+ZJMENUF(3,3,9,30);
	items = keys(list);
	for(i=0;i<sizeof(items);i++)
	{
		str += items[i]->query("name")+ZJBR"�һ��㣺"+list[items[i]]+":duihuan "+items[i]+ZJSEP;
	}
	tell_object(me,str+"\n");
	return 1;
}

int do_duihuan(string arg)
{
	int i,num;
	string str,*items;
	object ob,me = this_player();

	if(!arg)
	{
		tell_object(me,"��Ҫ�һ�ʲô��Ʒ��\n");
		return 1;
	}

	if(sscanf(arg,"%d %s",num,arg)!=2)
	{
		if(arg->query_amount())
		{
			tell_object(me,INPUTTXT("����һ�����"+arg->query("name")+"��","duihuan $txt# "+arg+"\n"));
			return 1;
		}
		num = 1;
	}

	if(num<1||num>999)
	{
		tell_object(me,"һ�����һ�999.\n");
		return 1;
	}

	if(!list[arg])
	{
		tell_object(me,"��Ҫ�һ�ʲô��Ʒ��\n");
		return 1;
	}

	if(!me->query("pkd_pot")||me->query("pkd_pot")<list[arg]*num)
	{
		tell_object(me,"��Ķһ��㲻�㣡��\n");
		return 1;
	}

	me->add("pkd_pot",-list[arg]*num);
	ob = new(arg);
	if(ob->query_amount())
		ob->set_amount(num);
	ob->move(me);
	me->save();
	tell_object(me,"������ϴ�����һ���һ"+ob->query("unit")+ob->query("name")+"��\n");
	return 1;
}

string ask_me()
{
	object me;

	me = this_player();
	if (PK_D->is_pking())
		return "�������˴������ھ����أ������ʲô��";

	if (PK_D->is_ready())
		return "�ܺã��������˴�����Ҫ��ʼ����Ҫ����ô(sign)��";

	return "���˴��������������Űɣ���û����ʼʱ���ء�";
}

int do_join()
{
	if(!wizardp(this_player()))
	return notify_fail("���ڷǱ���ʱ�䳡����ʱ�����š���\n");

	if (PK_D->is_pking())
		return notify_fail("���ϴ��۾�һ�����ȵ��������������������أ�����Щ�˵ȵȰɡ���\n");

	if (PK_D->is_ready())
		return notify_fail("���ϴ�����������Ҫ����ʽ�����ͽ�ȥ���������ȵ��š���\n");

	message_vision("$N��Ц��$n�������ҽ�ȥ��������пɺã���\n",this_player(), this_object());

	if (PK_D->join_competition(this_player()))
	{
		message("vision", this_player()->name() + "һ��С�ܽ������˳���\n",
			environment());
		return 1;
	}

	return 0;
}

int do_sign()
{
	object me;
	string msg;
	object ob;

	me = this_player();
	message_vision("$N����Ц����$n���������ã����ã���Ҳ��ǩ��������\n",me, this_object());
	if (me->query("combat_exp") < 1000)
	{
		message_vision("$ņͷ���˿�$N����м������������㱾�£�ֻ�òμӱ�����������\n",me, this_object());
		return 1;
	}

	if (stringp(msg = PK_D->reject_join(me)))
	{
		command("say " + msg);
		return 1;
	}

	foreach (ob in deep_inventory(me))
		if (ob->is_character())
		{
			command("say �㱳��˭��ȥ�������ϼҴ��ڵģ�����ҹ���");
			message_vision("$N����һ�ţ���$n�ߵ��ڵأ�\n",this_object(), me);
			me->receive_damage("qi", 50);
			return 1;
		}

	message_vision("$n���ͷ����$N�������ðɣ����Ƚ�ȥ׼���ɡ���\n$N���ͷ�������׼������ȥ��\n", me, this_object());
	me->move("/d/pk/ready");
	message("vision", me->name() + "�����ӵ����˽�����\n",environment(me), ({ me }));
	return 1;
}

