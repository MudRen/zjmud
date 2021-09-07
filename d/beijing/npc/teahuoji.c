inherit NPC;
inherit F_VENDOR;

void create()
{
	set_name("���̻��", ({ "chapu huoji", "chapu", "huoji" }) );
	set("gender", "����" );
	set("age", 18);
	set("long",
		"һ���ڲ�������õĻ�ơ�\n");
	set("shen_type", 1);
	set("combat_exp", 10000);
       set("str", 10);
       set("dex", 10);
       set("con", 10);
       set("int", 10);
	set("attitude", "peaceful");
       set_skill("dodge",20);
       set_skill("unarmed",20);
       set("chat_chance", 2);
       set("chat_msg", ({
		"���̻�ƶ�����˵������λ�͹٣��Ȳ���\n",
	}) );       

	set("vendor_goods", ({
		"/d/beijing/obj/tea1",
		"/d/beijing/obj/tea2",
		"/d/beijing/obj/tea3",
		"/d/beijing/obj/tea4",
	}) );
	setup();
       carry_object("/d/beijing/npc/obj/cloth")->wear();
	add_money("silver", 1);
}
void init()
{
	::init();
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}