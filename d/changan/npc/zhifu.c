//zhifu.c

inherit NPC;

void create()
{
	set_name("����»", ({ "liang xinglu", "liang" }));
	set("title", "����֪��");
	set("gender", "����");
	set("age", 43);
	set("str", 20);
	set("dex", 20);
	set("long", "����������֪����\n");
	set("combat_exp", 50000);
	set("shen_type", 0);
	set("attitude", "heroism");
	set_skill("unarmed", 60);
	set_skill("force", 60);
	set_skill("sword", 60);
	set_skill("dodge", 60);
	set_skill("parry", 60);
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 15);
	set("neili", 500); 
	set("max_neili", 500);
	set("jiali", 20);

	setup();
	carry_object(__DIR__"obj/sword")->wield();
	carry_object(__DIR__"obj/choupao")->wear();
}
