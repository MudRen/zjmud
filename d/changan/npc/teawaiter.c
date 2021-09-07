//teawaiter.c

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("���С��",({"waiter","xiaoer","xiao","xiaoer","er"}));
	set("shop_id",({"waiter","xiaoer","xiao","er"}));
	set("shop_title","���С��");
	set("gender", "����");
	set("combat_exp", 1000);
	set("age", 26);
	set("per", 24);
	set("attitude", "friendly");
	set("shen_type", 1);
	set_skill("unarmed", 34);
	set("vendor_goods", ({
		__DIR__"obj/teapot",
	}));

	setup();
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
	if (! ob || environment(ob) != environment())
		return;
	switch(random(3))
	{
	case 0:
		say("С����Ц�����˵������λ" +
		    RANK_D->query_respect(ob) +
		    "�������ȱ��裬ЪЪ�Ȱɡ�\n");
		break;
	case 1:
		say("С������ë��Ĩ��Ĩ��ߵ�һ�����ӣ�˵"
		    "������λ" + RANK_D->query_respect(ob) +
		    "���������\n");
		break;
	case 2:
		say("С����˵������λ" + RANK_D->query_respect(ob) +
		    "���������������²ɵĲ�Ҷ�ɡ�׼�������⡣\n");
		break;
	}
}
