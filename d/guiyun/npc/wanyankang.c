// wanyankang.c

inherit NPC;

void create()
{
	set_name("���տ�", ({"wanyan kang", "kang", "wanyan"}));
	set("gender", "����");
	set("title", "����С��ү");
	set("age", 24);
	set("class", "fighter");
	set("long",
		"�����������ĸ��ϧ�������պ��Һ󣬳���С���ӣ�
̰ͼ�����������ġ�\n");
	set("attitude", "friendly");
	set("shen_type",1);
	set("str", 26);
	set("int", 25);
	set("con", 25);
	set("dex", 26);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
		(: perform_action, "sword.ding" :),
	}));

	set("qi", 500);
	set("max_qi", 500);
	set("jing", 400);
	set("max_jing", 400);
	set("neili", 1000);
	set("max_neili", 1000);
	set("jiali", 10);

	set("combat_exp", 160000);

	set_skill("force", 80);
	set_skill("quanzhen-xinfa", 80);
	set_skill("sword", 80);
	set_skill("quanzhen-jian", 80);
	set_skill("dodge", 80);
	set_skill("jinyan-gong", 80);
	set_skill("parry", 80);
	set_skill("strike", 80);
	set_skill("haotian-zhang", 80);
	set_skill("claw",80);
	set_skill("jiuyin-baiguzhao", 80);
	set_skill("literate", 100);
	set_skill("taoism", 20);

	map_skill("force", "quanzhen-xinfa");
	map_skill("sword", "quanzhen-jian");
	map_skill("dodge", "jinyan-gong");
	map_skill("parry", "quanzhen-jian");
	map_skill("strike", "haotian-zhang");
	map_skill("claw", "jiuyin-baiguzhao");
	prepare_skill("claw", "jiuyin-baiguzhao");

	create_family("ȫ���", 3, "����");

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/male1-cloth")->wear();
}

