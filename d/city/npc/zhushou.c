// yang.c �ӻ��̻�� 

inherit NPC;
//inherit F_VENDOR;
inherit F_DEALER;

void create()
{
	set_name("����", ({ "zhushou", "shou" }));
	set("title", "�ӻ��̻��");
	set("shen_type", 1);

	set("gender", "����");
	set("age", 29);
	set("long",
		"��������������������ˣ����ӻ��̸��˺ü����ˡ�\n");
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/damage", 15);

	set("combat_exp", 4000);
	set("attitude", "friendly");
	set("vendor_goods", ({
	      __DIR__"obj/pixue",
		__DIR__"obj/shoutao",
		__DIR__"obj/tieshou",
		__DIR__"obj/jinsijia",
		"/d/xingxiu/obj/fire",
	     "/clone/pants/piku",
		"/d/item/obj/chanhs",
		"/d/city/obj/rrose",
		"/d/city/obj/yrose",
		"/clone/misc/wood",
		"/clone/misc/shoeshine",
		"/clone/misc/brush",
	}));
	
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}

