//huoji.c

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("С���", ({"huo ji"}));
	set("age", 18);
	set("gender", "����");
	set("long","�����̵Ļ�ƣ�������Ŀ����㡣\n");
	set("shop_title", "�����̻��");
	set("attitude", "friendly");
	set("combat_exp", 10000);
	set("shen_type", 1);
	set("neili", 200);
	set("jiali", 5);
	set_skill("unarmed", 20);
	set_skill("dodge", 60);
	set_skill("parry", 20);
	set("vendor_goods", ({
		__DIR__"obj/bao1",
		__DIR__"obj/bao2",		
		__DIR__"obj/bao3",		
	}));

	setup();
	add_money("silver", 3);
	carry_object(__DIR__"obj/linen")->wear();
}

int accept_fight(object me)
{
	command("say ��λ������С���ǸҸ������ְ���\n");
	return 0;
}

void init()
{
	object ob;

	::init();
	if (interactive(ob = this_player()) && !is_fighting() ) 
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
	add_action("do_buy", "buy");
	add_action("do_list", "list"); 	
}

void greeting(object ob)
{
	if (! ob || ! visible(ob) || environment(ob) != environment())
		return;

	say(name()+"�������˵������λ" +RANK_D->query_respect(ob) +
	    "�������Լ������Ӱɡ�\n");
}
