//shuci.c

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("���", ({ "shu chi", "chi", }) );
	set("gender", "����" );
	set("age", 40);
	set("title", "���ĸ��ϰ�");
	set("combat_exp", 50000);
	set_skill("dodge", 50);
	set_skill("parry", 50);
	set_skill("unarmed", 50);
	set_skill("literate", 100);
	set("attitude", "friendly");
	set("per",25);
	set("vendor_goods", ({
		__DIR__"obj/book_blade",
       	 	__DIR__"obj/book_unarmed",
	}));

	setup();
	carry_object(__DIR__"obj/choupao")->wear();
}

void init()
{
	object ob;
	::init();
	if (interactive(ob = this_player()) && ! is_fighting()) 
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
	command("say ��λ" + RANK_D->query_respect(ob) + "��������������");
}
