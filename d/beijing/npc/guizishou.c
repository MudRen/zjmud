inherit NPC;

void create()
{
	set_name("������", ({ "guizi shou", "guizi", "shou" }));
	set("long", 
		"һ������⺷�����ӣ��������ű��ֵ���\n"
	      "���̳���ר�Ÿ������ˡ�\n");
	set("gender", "����");
	set("age", 30);
	set("attitude", "heroism");
	set("shen_type", 1);

	set("str", 30);
	set("int", 20);
	set("con", 25);
	set("dex", 20);
	
	set("max_qi", 150);
	set("max_jing", 150);
	set("neili", 100);
	set("max_neili", 100);

	set("combat_exp", 15000);

	set_skill("force", 20);
	set_skill("dodge", 20);
	set_skill("unarmed", 20);
	set_skill("parry", 20);
	set_skill("blade", 20);

	setup();
	carry_object("/clone/weapon/dadao")->wield();
       carry_object("/d/beijing/npc/obj/cloth")->wear();
}
