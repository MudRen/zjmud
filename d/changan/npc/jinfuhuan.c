//jinfuhuan.c

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("�𸴻�", ({ "jin fuhuan", "jin","fuhuan" }));
	set("title", "�鱦���ϰ�");
	set("shen_type", 1);
	set("str", 35);
	set("gender", "����");
	set("age", 45);
	set("combat_exp", 50000);
	set("attitude", "friendly");
	set_skill("unarmed", 60);
	set_skill("dodge", 60);
	set_temp("apply/attack", 30);
	set_temp("apply/defense", 30);
	set("vendor_goods", ({
		__DIR__"obj/ring",
		__DIR__"obj/wrists",
		__DIR__"obj/neck",
	}));

       setup();

       carry_object(__DIR__"obj/choupao")->wear();
       add_money("gold", 2);
}

void init()
{
       add_action("do_buy", "buy");
       add_action("do_list", "list"); 	
}
