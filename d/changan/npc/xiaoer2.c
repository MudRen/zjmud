//xiaoer.c

inherit KNOWER;
inherit F_DEALER;

void create()
{
	set_name("��С��", ({"xiaoer","xiaoer","xiao","waiter","er"}));
	set("shop_id",({"waiter","xiaoer","xiao","er"}));
	set("shop_title","��С��");
	set("gender", "����");
	set("combat_exp", 1000);
	set("age", 26);
	set("per", 14);
	set("attitude", "friendly");
	set("shen_type", 1);
	set_skill("unarmed", 10);
	set("vendor_goods", ({
		__DIR__"obj/jiudai",
	 	__DIR__"obj/gourou",
		__DIR__"obj/jitui",
	}));

	setup();
	carry_object(__DIR__"obj/linen")->wear();
	add_money("silver", 5);
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
	if (! ob || ! visible(ob) || environment(ob) != environment())
		return;
	switch(random(3))
	{  
	case 0:
		say("��С��Ц�����˵������λ" + RANK_D->query_respect(ob) +
		    "�����������ѣ�ЪЪ�Ȱɡ�\n");
		break;
	case 1:
		say("��С���ò����ϵ�ë��Ĩ��Ĩ�֣�˵������λ" +
		    RANK_D->query_respect(ob)+ "����������\n");
	break;
	}
}
