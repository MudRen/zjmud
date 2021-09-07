// li.c

inherit NPC;

void create()
{
	set_name("��������", ({ "haolian tieshu", "tieshu" }));
	set("gender", "����");
	set("age", random(10) + 20);
	set("str", 25);
	set("dex", 16);
	set("long", "�������ĵ������󽫾��������Ժա�\n");
	set("combat_exp", 300000);
	set("shen_type", 1);
	set("attitude", "aggressive");

	set_skill("unarmed", 120);
	set_skill("force", 120);
	set_skill("club", 120);
	set_skill("zhongping-qiang", 80);
	set_skill("dodge", 120);
	set_skill("parry", 120);
	map_skill("club", "zhongping-qiang");
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/armor", 50);
	set_temp("apply/damage", 50);

	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 50);

	setup();
	carry_object("/clone/cloth/tiejia")->wear();
	carry_object("/clone/weapon/changqiang")->wield();
}
