// guducheng.c ���Ƴ�

#include <ansi.h>
inherit NPC;

void create()
{
	set_name("���Ƴ�", ({ "gu ducheng", "gu" }));
	set("title",  "������" );
	set("long", "���Ǵ�����Ĵ���֮һ��\n");
	set("gender", "����");
	set("age", 40);
	set("class", "officer");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 30);
	set("int", 20);
	set("con", 25);
	set("dex", 25);
	
	set("max_qi", 1400);
	set("max_jing", 700);
	set("neili", 2000);
	set("max_neili", 2000);
	set("jiali", 45);
	set("combat_exp", 340000);
	set("score", 12000);

	set_skill("force", 70);
	set_skill("dodge", 75);
	set_skill("parry", 75);
	set_skill("unarmed", 70);
	set_skill("sword", 70);
	set_skill("staff", 70);
	set_skill("kurong-changong", 70);
	set_skill("tiannan-step", 75);
	set_skill("jinyu-quan", 70);
	set_skill("duanjia-sword", 70);
	set_skill("literate", 25);

	map_skill("force", "kurong-changong");
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
