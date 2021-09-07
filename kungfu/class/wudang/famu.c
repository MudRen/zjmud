// famu.c ��ľ
inherit NPC;

void create()
{
	set_name("��ľ����", ({ "famu daozhang", "famu" }));
	set("long", 
		"�����䵱ɽ�ķ�ľ����, רΪ�����ṩľ�ġ�\n");
	set("gender", "����");
	set("age", 30);
	set("attitude", "peaceful");
	set("shen_type", 1);

	set("str", 20);
	set("int", 20);
	set("con", 25);
	set("dex", 20);
	
	set("max_qi", 300);
	set("max_jing", 200);
	set("neili", 300);
	set("max_neili", 300);

	set("combat_exp", 7500);
	set("score", 1000);

	set_skill("force", 40);
	set_skill("dodge", 40);
	set_skill("strike", 40);
	set_skill("wudang-zhang", 40);
	set_skill("parry", 40);
	set_skill("blade", 40);
	set_skill("taiji-dao", 40);
	set_skill("taoism", 20);

	map_skill("parry", "taiji-dao");
	map_skill("blade", "taiji-dao");
	map_skill("strike", "wudang-zhang");

	prepare_skill("strike", "wudang-zhang");

	create_family("�䵱��", 4, "����");

	setup();
	carry_object("/clone/weapon/gangdao")->wield();
}
