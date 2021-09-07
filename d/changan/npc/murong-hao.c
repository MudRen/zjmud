//murong-hao.c

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("Ľ�ݺ�", ({"murong hao", "murong", "hao"}));
	set("title", "�ϰ�");
	set("gender", "����");
	set("age", 25);
	set("long", "Ľ�ݺ���Ľ�����ҵĵ��ӡ�\n");
	set("combat_exp", 90000);
	set("attitude", "heroic"); 
	set_skill("sword", 50);
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("parry", 50);
	set("force", 200);
	set("max_force", 200);
	set("force_factor", 5);
	set("vendor_goods", ({
		__DIR__"obj/changjian",
		__DIR__"obj/blade",
		__DIR__"obj/hammer",
		"/clone/weapon/arrow",
		"/clone/weapon/wolfarrow",
		"/clone/weapon/bow",
		"/clone/weapon/longbow",
	}));

	setup();
	carry_object(__DIR__"obj/jinzhuang")->wear();
	carry_object(__DIR__"obj/changjian")->wield();
}

void init()
{
	object ob;

	::init();
	if (interactive(ob = this_player()) && !is_fighting()) 
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}

void greeting(object ob)
{
	if (! ob || ! visible(ob) || environment(ob) != environment())
		return;
	say(name() + "�������ĵĿ�����һ�ۣ�˳������������"
	    "��һ�ѳ��������������á�\n");
}

int accept_fight(object me)
{
	command("say ����ģ���һ�������Ӿ�֪�����ǳ��������ģ�\n");   
	command("hate");
	command("grin");
	command("say �Ҳ��Ǻ��۸��ģ�"+RANK_D->query_rude(me)+"���������ɣ�");
	command("kill" + me->query("id"));

	return 1;
}
