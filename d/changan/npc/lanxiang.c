//lanxiang.c

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("������", ({"zhang lanxiang", "zhang", "lanxiang"}));
	set("shop_id",({"laoban","zhanglanxiang","zhang","lanxiang"}));
	set("shop_title", "ˮ�����ϰ�");
	set("gender", "Ů��");
	set("combat_exp", 4000);
	set("age", 23);
	set("per", 40);
	set("attitude", "friendly");
	set("shen_type", 1);
	set_skill("unarmed", 30);
	set_skill("dodge", 30);
	set_skill("parry", 30);
	set("vendor_goods", ({
		__DIR__"obj/pingguo",
		__DIR__"obj/hamigua",
		__DIR__"obj/juzi",
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
	if (! ob || environment(ob) != environment()) return;

	say("������Ц�����˵������λ" + RANK_D->query_respect(ob) +
	    "���µ��ĸ���ˮ���������ؼҳ����ɡ�\n");
}
