// yue-lingshan.c

inherit NPC;

void create()
{
	set_name("����ɺ", ({ "yue lingshan", "yue", "lingshan" }) );
	set("nickname", "Сʦ��");
	set("gender", "Ů��" );
	set("age", 17);
	set("str", 16);
	set("con", 24);
	set("dex", 30);
	set("int", 27);

	set("attitude", "friendly");

	set("max_qi", 1200);
	set("max_jing", 600);
	set("neili", 1500);
	set("max_neili", 1500);
	set("jiali", 40);
	set("combat_exp", 100000);

	set("long",     "����ɺ�ǻ�ɽ����������Ⱥ�Ķ���Ů����\n");

	create_family("��ɽ��", 14, "����");

	set_skill("unarmed", 50);
	set_skill("sword", 50);
	set_skill("force", 60);
	set_skill("parry", 50);
	set_skill("dodge", 50);
	set_skill("literate", 70);

	set_skill("huashan-sword", 50);
	set_skill("yunu-sword", 80);
	set_skill("huashan-quanfa", 50);
	set_skill("huashan-xinfa", 50);
	set_skill("feiyan-huixiang", 50);

	map_skill("sword", "yunu-sword");
	map_skill("parry", "yunu-sword");
	map_skill("force", "huashan-xinfa");
	map_skill("unarmed", "huashan-quanfa");
	map_skill("dodge", "feiyan-huixiang");

	setup();

	carry_object(__DIR__"obj/green_water_sword")->wield();
	carry_object("/clone/cloth/cloth")->wear();

}

int accept_fight(object me)
{
	command("say СŮ����������Ķ���?");
	return 0;
}
