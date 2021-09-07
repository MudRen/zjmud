// li.c

inherit NPC;
inherit F_GUARDER;
inherit F_UNIQUE;

void create()
{
	set_name("��ܼ�", ({ "li", "li guanjia" }) );
	set("gender", "����" );
	set("age", 25);
	set("long", "���Ǹ��Ͱ����׵Ĵ�ܼҡ�\n");
	set("attitude", "friendly");
	set("shen_type", -1);
	set("class", "fighter");

	set("str", 23);
	set("int", 23);
	set("con", 22);
	set("dex", 20);

	set("max_qi", 5000);
	set("qi", 5000);
	set("max_jing", 5000);
	set("jing",5000);
	set("neili", 4000);
	set("max_neili", 4000);
	set("jiali", 0);

	set("combat_exp", 250000);
	set("score", 20000);

	set_skill("force", 100);
	set_skill("dodge", 120);
	set_skill("unarmed", 110);
	set_skill("parry", 100);
	set_skill("chanchu-bufa", 100);
	set_skill("changquan", 100);

	map_skill("dodge", "chanchu-bufa");
	map_skill("parry", "changquan");
	map_skill("unarmed", "changquan");

	create_family("ŷ������", 0, "�ܼ�");

	set("coagents", ({
	    ([ "startroom" : "/d/baituo/dating",
	       "id"	: "ouyang feng" ]),
	}));

	set("chat_chance", 2);
	set("chat_msg", ({
		"��ܼ�˵��: ��ѧ�������ɳ���..\n",
	}) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object ob)
{
	if (ob->query("born_family") != "ŷ������")
	{
		command("shake");
		command("say �������ļһ��Ȼ��������ɽ���ң�");
		return;
	}

	command("say �Ǻǣ��Ҳ���ͽ��ȥ��ŷ��ׯ���ɡ�\n");
	return;
}
