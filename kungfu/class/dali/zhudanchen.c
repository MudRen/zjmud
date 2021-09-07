// zhudanchen.c �쵤��

#include <ansi.h>
inherit NPC;

void create()
{
	set_name("�쵤��", ({ "zhu danchen", "zhu" }));
	set("title",  "������" );
	set("long", "���Ǵ�����Ĵ���֮һ��һ������������Ĵ����ͷ��\n");
	set("gender", "����");
	set("age", 40);
	set("class", "officer");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 25);
	set("int", 30);
	set("con", 25);
	set("dex", 25);
	
	set("max_qi", 1600);
	set("max_jing", 800);
	set("neili", 1900);
	set("max_neili", 1900);
	set("jiali", 35);
	set("combat_exp", 290000);
	set("score", 11000);

	set_skill("force", 75);
	set_skill("dodge", 70);
	set_skill("parry", 75);
	set_skill("cuff", 70);
	set_skill("sword", 75);
	set_skill("staff", 75);
	set_skill("wudang-xinfa", 75);
	set_skill("tiannan-step", 70);
	set_skill("jinyu-quan", 70);
	set_skill("duanjia-sword", 75);
	set_skill("literate", 95);

	map_skill("force", "wudang-xinfa");
	map_skill("dodge", "tiannan-step");
	map_skill("cuff", "jinyu-quan");
	map_skill("sword", "duanjia-sword");
	map_skill("staff", "duanjia-sword");
	map_skill("parry", "duanjia-sword");
	prepare_skill("cuff", "jinyu-quan");

	setup();
	carry_object("/d/dali/npc/obj/junfu")->wear();
	carry_object("/clone/weapon/changjian")->wield();
	add_money("silver", 10);

	create_family("����μ�", 0, "����");
}
