inherit NPC;

void create()
{
	set_name("�Ŀ�", ({ "du ke", "du", "ke" }) );
	set("gender", "����" );
	set("age", 40);
	set("long",
	      "һ�����ĵ��˸߲��ҵĶĿ͡�\n");
	set("shen_type", 1);
	set("combat_exp", 10000);
	set("str", 17);
	set("dex", 20);
	set("con", 17);
	set("int", 22);
	set("attitude", "peaceful");
	set_skill("dodge",20);
	set_skill("unarmed",20);
	set("chat_chance", 1);
	set("chat_msg", ({
		"�Ŀ����������ģ�����������ô��ô��˳��\n",
	}) );       

	setup();
	carry_object("/d/beijing/npc/obj/cloth")->wear();
	add_money("coin", 30);
}

