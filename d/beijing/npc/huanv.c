inherit NPC;
inherit F_VENDOR;

void create()
{
	set_name("������Ů", ({ "shao nv", "nv", "shao" }) );
	set("gender", "Ů��" );
	set("age", 15);
	set("long",
	      "һ���ʻ���������СŮ����\n");
	set("shen_type", 1);
	set("combat_exp", 10000);
       set("str", 17);
       set("per", 25);
       set("dex", 20);
       set("con", 17);
       set("int", 22);
	set("attitude", "peaceful");
       set_skill("dodge",20);
       set_skill("unarmed",20);
       set("chat_chance", 20);

	set("vendor_goods", ({
		"/d/beijing/obj/hua",
	}) );

	setup();
       carry_object("/d/beijing/npc/obj/nvcloth")->wear();
	add_money("coin", 100);
}

void init()
{
	::init();
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}
