// lao-denuo.c

inherit NPC;
inherit F_GUARDER;

int permit_pass(object me, string dir);

void create()
{
	set_name("�͵�ŵ", ({ "lao denuo","lao","denuo" }) );
	set("nickname", "�Ϻ���");
	set("gender", "����");
	set("age", 61);
	set("long", "�͵�ŵ������Ⱥ�Ķ����ӡ�\n");
	set("attitude", "peaceful");

	set("str", 26);
	set("con", 30);
	set("int", 24);
	set("dex", 30);

	set("max_qi", 3400);
	set("max_jing", 1700);
	set("neili", 2800);
	set("max_neili", 2800);

	set("combat_exp", 150000);
	set("shen_type", -1);
	set("score", 5000);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :)
	}) );

	set_skill("unarmed", 95);
	set_skill("sword", 95);
	set_skill("force", 95);
	set_skill("parry", 95);
	set_skill("dodge", 95);
	set_skill("literate", 40);

	set_skill("huashan-sword", 95);
	set_skill("huashan-xinfa", 95);
	set_skill("huashan-quanfa", 95);
	set_skill("feiyan-huixiang", 95);

	map_skill("sword", "huashan-sword");
	map_skill("parry", "huashan-sword");
	map_skill("force", "huashan-xinfa");
	map_skill("unarmed", "huashan-quanfa");
	map_skill("dodge", "feiyan-huixiang");

	set_temp("apply/damage", 100);
	set_temp("apply/armor", 100);

	set("apply/dodge", 100);

	set("coagents", ({
		([ "startroom" : "/d/huashan/qunxianguan",
		   "id"	: "yue buqun" ]),
	}));

	create_family("��ɽ��", 14, "����");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

int permit_pass(object me, string dir)
{
	object *inv;
	int i;
      object tongxing1;

	if (! interactive(me))
		return 0;

	if (! living(this_object()))
		return 1;

	if(objectp(tongxing1=present("tongxing ling1",me)) && dir == "southup")
	{
	      message_vision("$N�ݸ��͵�ŵһöͨ�����ơ�\n", me);
		command("say ԭ���Ƕ���һ��Ĺ���ݵ�����λ" + RANK_D->query_respect(me) + "�����룡");
		destruct(tongxing1);
		return 1;
	}

	if (me->query("family/family_name") == "��ɽ����" && dir == "southup")
	{
		if (me->query_temp("beg_huashan"))
		{
			command("say ��ͷ�ǰ�����ͷ�ǰ�����");
			return 1;
		}

		message_vision("$N˵������ʦ�н�������ɽ�ɽ��������Ѿ�����ǰ�ӣ���λ" + RANK_D->query_respect(me) + "��ɡ�\n", this_object());
		return 1;
	}


	notify_fail("����" + name() + "�����������ȥ��\n");

	inv = deep_inventory(me);
	for (i = 0; i < sizeof(inv); i++)
	{
		if (! playerp(inv[i])) continue;
		if ((string) inv[i]->query("family/family_name") != "��ɽ��")
		{
			message_vision("$N��$n�ȵ����㱳����˭�����������£�\n",
				       this_object(), me);
			return 0;
		}
	}

	if (me->query("family/family_name") &&
	    me->query("family/family_name") != "��ɽ��" ||
	    ! me->query("family/family_name") &&
	    me->query("combat_exp") > 20000)
	{
		message_vision("$N��$n�����Բ��𣬲������ǻ�ɽ�ɵ���"
			       "�����뱾���صء�\n", this_object(), me);
		return 0;
	}

	return 1;
}

void relay_emote(object me, string verb)
{
	if (verb != "beg")
	{
		switch (random(5))
		{
		case 0:
			command("bored");
			break;

		case 1:
			command("shzi");
			break;

		case 2:
			command("@@");
			break;

		case 3:
			command("cold");
			break;

		default:
			command("heihei");
			break;
		}
		return;
	}

	if (me->query("family/family_name") != "��ɽ����")
	{
		command("poor " + me->query("id"));
		return;
	}

	command("sigh");
	command("say ��λ" + RANK_D->query_respect(me) +	"�����˽��ڣ�����˰ɣ���Ҫ������ͷ�ǰ��");
	me->set_temp("beg_huashan", 1);
}
