//tongling2.c

inherit NPC;

void create()
{
	set_name("��Ⱥ", ({ "xiao qun"}) );
	set("gender", "����");
	set("age", 30);
	set("combat_exp", 200000);
	set("title", "���־�ͳ��");
	set("attitude", "friendly");
	set("per", 25);
	set("str", 35);
	set("max_qi", 900);
	set("max_jing", 900);
	set("max_jingli", 900);
	set("jingli", 900);
	set("neili", 900);
	set("max_neili", 900);
	set("jiali", 50);
	set_skill("hammer", 120);
	set_skill("unarmed", 120);
	set_skill("parry", 120);
	set_skill("dodge", 120);
	set_skill("force", 120);  
     
	setup();
	carry_object(__DIR__"obj/hammer")->wield();
	carry_object(__DIR__"obj/zhanjia")->wear();
}

int accept_fight(object me)
{
	command("say �ҹ�Ϊ���־�ͳ�죬��������һ���ʶ��");
	return 0;
}
