inherit NPC;

void create()
{
	set_name("Ϸ��", ({ "xi zi", "xi", "zi" }) );
	set("gender", "����" );
	set("age", 32);
	set("long",
	      "һ����ϷԺ��Ϸ��Ϸ�ӡ�\n");
	set("shen_type", 1);
	set("combat_exp", 10000);
	set("str", 17);
	set("dex", 20);
	set("con", 17);
	set("int", 22);
	set("attitude", "peaceful");
	set_skill("dodge",20);
	set_skill("unarmed",20);
	
	setup();
	carry_object("/d/beijing/npc/obj/cloth")->wear();
	add_money("coin", 30);
}

