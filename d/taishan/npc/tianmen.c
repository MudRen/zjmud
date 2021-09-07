// tianmen.c
inherit NPC;

#include <ansi.h>

void create()
{
	set_name("���ŵ���", ({ "tianmen daoren", "daoren", "tianmen" }) );
	set("gender", "����");
	set("title", HIG"̩ɽ�ɵ�ʮ��������"NOR);
	set("class", "taoist");
	set("age", 45);
	set("attitude", "peaceful");
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 28);

	set("max_qi", 3200);
	set("max_jing", 1600);
	set("neili", 4200);
	set("max_neili", 4200);
	set("jiali", 60);
	set("combat_exp", 800000);
	set("shen_type", 1);

	set_skill("sword", 170);
	set_skill("force", 170);
	set_skill("parry", 170);
	set_skill("dodge", 170);
	set_skill("taishan-sword", 170);
	set_skill("lingxu-bu", 170);
	set_skill("taishan-xinfa", 170);

	map_skill("force", "taishan-xinfa");
	map_skill("sword", "taishan-sword");
	map_skill("parry", "taishan-sword");
	map_skill("dodge", "lingxu-bu");

	create_family("̩ɽ��", 13, "����");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/greyrobe")->wear();
}

