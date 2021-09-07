// gao-genming.c

inherit NPC;
inherit F_GUARDER;

int permit_pass(object me, string dir);

void create()
{
	set_name("�߸���", ({ "gao genming","gao","genming" }) );
	set("nickname", "�о�����");
	set("gender", "����");
	set("age", 24);
	set("long",
		"�߸���������Ⱥ�ĵ���λ���ӡ�\n");
	set("attitude", "peaceful");

	set("str", 26);
	set("con", 30);
	set("int", 24);
	set("dex", 30);

	set("neili", 900);
	set("max_neili", 900);

	set("combat_exp", 30000);
	set("score", 20000);
	set("shen_type", 1);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :)
	}) );

	set_skill("unarmed", 50);
	set_skill("sword", 50);
	set_skill("force", 50);
	set_skill("parry", 50);
	set_skill("dodge", 50);
	set_skill("literate", 30);

	set_skill("huashan-sword", 50);
	set_skill("huashan-xinfa", 50);
	set_skill("huashan-quanfa", 50);
	set_skill("feiyan-huixiang", 50);

	map_skill("sword", "huashan-sword");
	map_skill("parry", "huashan-sword");
	map_skill("force", "huashan-xinfa");
	map_skill("unarmed", "huashan-quanfa");
	map_skill("dodge", "feiyan-huixiang");

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

	if (! living(this_object()))
		return 1;

	if (me->query("family/family_name") == "��ɽ����" && dir == "north")
	{
		message_vision("$N˵���������н�������ɽ�ɽ��������Ѿ�����ǰ�ӣ���λ" + RANK_D->query_respect(me) + "��ɡ�\n", this_object());
		return 1;
	}

	if (me->query_temp("beg_huashan") &&
	    me->query("family/family_name") != "��ɽ��")
	{
		message_vision("$N�۾�һ������$n�ȵ���������"
			       "�ܸ�ɶ���Ǽ�ϸô����\n", this_object(), me);
		return -1;
	}

	notify_fail("����" + name() + "�����������ȥ��\n");

	inv = all_inventory(me);
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
