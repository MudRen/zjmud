//jingming.c

inherit NPC;

void create()
{
	set_name("����", ({"jing ming", "monk" }));
	set("title","�����³���");
	set("gender", "����");
	set("age", 80);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("per", 30);
	set("int", 30);
	set("max_qi", 700);
	set("max_jing", 700);
	set("neili", 800);
	set("max_neili", 800);
	set("jiali", 30);
	set("max_jingli", 800);
	set("jingli", 800);
	set("combat_exp", 120000);
	set_skill("unarmed", 70);
	set_skill("dodge", 70);
	set_skill("parry", 70);
	set_skill("force", 70);

	setup();
	carry_object(__DIR__"obj/sengpao")->wear();
}

int accept_fight(object me)
{
	command("say ��λ"+ RANK_D->query_respect(me) +
		"������ԩ�޳��������Ǻα��أ�");
	
	return 0;
}
