inherit NPC;

void create()
{
	set_name("��������", ({ "shi wei", "shi", "wei" }));
	set("age", 22);
	set("gender", "����");
	set("long", "һ����ı뺵�Ĺٱ������ŵ������ſ���������\n");
	set("attitude", "peaceful");

	set("str", 25);
	set("dex", 20);
	set("combat_exp", 20000);
	set("shen_type", 1);

	set_skill("unarmed", 40);
	set_skill("dodge", 40);
	set_skill("parry", 40);
	set_skill("blade", 40);
	set_skill("force", 40);
	set_temp("apply/attack", 20);
	set_temp("apply/defense", 20);
	set_temp("apply/damage", 10);
	set_temp("apply/armor", 20);

	setup();
	carry_object("/clone/weapon/blade")->wield();
	carry_object("/d/beijing/npc/obj/guanfu6")->wear();
}
