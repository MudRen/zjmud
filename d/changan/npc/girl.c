//girl.c

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("��������", ({"maihua guniang", "girl", "guniang"}));
	set("shop_title", "�����ϰ�");
	set("gender", "Ů��");
	set("combat_exp", 4000);
	set("age", 17);
	set("per", 40);
	set("attitude", "friendly");
	set("shen_type", 1);
	set_skill("unarmed", 30);
	set_skill("dodge", 30);
	set_skill("parry", 30);
	set("vendor_goods", ({
		__DIR__"obj/zi-luolan",
		__DIR__"obj/hong-meigui",
		__DIR__"obj/huang-meigui",
		__DIR__"obj/lan-tiane",
		__DIR__"obj/bai-chahua",
		__DIR__"obj/hei-mudan",
	}));

	setup();
  	carry_object(__DIR__"obj/skirt")->wear();
  	add_money("silver", 30);
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
	add_action("do_buy", "buy");
	add_action("do_list", "list"); 	
}

void greeting(object ob)
{
	if (!ob || environment(ob) != environment()) return;
	switch( random(2) ) 
	{
	case 0:
		message_vision("$NЦ��˵����������"
			       "�ʻ��䣬��Щ��ȥ����������˰ɡ�\n",
			       this_object(), ob);
		break;
	case 1:
		message_vision("$NЦ�����˵������λ" +
			       RANK_D->query_respect(ob) +
			       "Ҫ��ʲô������\n",
			       this_object(), ob);

		break;
	}
}
