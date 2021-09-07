// hadani.c

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("������", ({ "ha dani", "dani", "ha" }));
	set("gender", "����" );
	set("age", 28);
	set("long",
		"����һλ�����С���ӣ��������������Ϊ����\n");
   set("icon","05011");      set("title", "����");
	set("combat_exp", 30000);
	set("attitude", "friendly");
	set_temp("apply/attack", 30);
	set_temp("apply/defense", 30);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 30);

	set("vendor_goods", ({
		"/d/guanwai/obj/saw",
		"/d/guanwai/obj/axe",
	}));

	set("inquiry", ([
		"�־�" : "���������Ϻõĸ־⣬��Ҫ��Ҫ��һ����",
		"��"   : "���������Ϻõĸ־⣬��Ҫ��Ҫ��һ����",
		"��ͷ" : "������У���һ�Ѱɡ�",
		"����" : "������У���һ�Ѱɡ�",
	]));

	setup();
	carry_object("/clone/cloth/cuttonp")->wear();
}

void init()
{	
	add_action("do_buy", "buy");
	add_action("do_list", "list");
}
