inherit NPC;

void create()
{
	set_name("����", ({ "tie jiang", "tie", "jiang" }) );
	set("gender", "����" );
	set("age", 37);
	set("long",
		"һ��Ƥ����ڵ������������\n");
	set("shen_type", 1);
	set("combat_exp", 20000);
       set("str", 20);
       set("dex", 20);
	set("icon","05011");
       set("con", 20);
       set("int", 20);
	set("attitude", "peaceful");
       set_skill("dodge",20);
       set_skill("unarmed",20);
       set("chat_chance", 1);
       set("chat_msg", ({
		"���������Ĵ�������\n",
       }) );       

	setup();
       carry_object("/d/beijing/npc/obj/cloth3")->wear();
       carry_object("/d/beijing/npc/obj/hammer")->wield();
	add_money("coin", 200);
}
