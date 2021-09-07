// ding.c

#include <ansi.h>;

inherit NPC;

void create()
{
	set_name("����", ({"ding jian","ding",}));
	set("long",
		"���������ӽ��������һ�ֵ罣���ᣬ������÷ׯ�����ˡ�\n"
	);
	set("gender", "����");
	set("nickname", HIC "һ�ֵ罣" NOR);
	set("title", "÷ׯ�ʹ�");
	set("attitude", "friendly");

	set("age", 30);
	set("shen_type", -1);
	set("str", 17);
	set("int", 24);
	set("con", 20);
	set("dex", 22);
	set("max_qi", 3350);
	set("max_jing", 2200);
	set("neili", 1350);
	set("max_neili", 1350);
	set("jiali", 5);
	set("combat_exp", 100000);

	set_skill("force", 80);
	set_skill("dodge", 80);
	set_skill("sword", 100);
	set_skill("parry", 100);

	setup();
	carry_object("/d/city/npc/obj/cloth")->wear();
	carry_object("/d/city/npc/obj/changjian")->wield();
	carry_object("/d/meizhuang/obj/yaoshi");
}
