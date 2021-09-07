inherit NPC;
inherit F_MASTER;

#include "xingxiu.h"

string ask_me();

void create()
{
	set_name("������", ({ "tianlang zi", "tianlang" }));
	set("nickname", "��������ʦ��");
	set("long", 
		"�����Ƕ�����������������ӡ�\n");
	set("gender", "����");
	set("age", 30);
	set("attitude", "peaceful");
	set("class", "fighter");
	set("shen_type", -1);
	set("str", 27);
	set("int", 16);
	set("con", 25);
	set("dex", 27);
	
	set("max_qi", 1700);
	set("max_jing", 800);
	set("neili", 1900);
	set("max_neili", 1900);
	set("jiali", 15);
	set("combat_exp", 120000);

	set_skill("force", 100);
	set_skill("huagong-dafa", 100);
	set_skill("guixi-gong", 100);
	set_skill("dodge", 70);
	set_skill("zhaixinggong", 70);
	set_skill("strike", 70);
	set_skill("chousui-zhang", 70);
	set_skill("claw", 100);
	set_skill("sanyin-wugongzhao", 100);
	set_skill("whip", 60);
	set_skill("chanhun-suo", 60);
	set_skill("parry", 100);
	set_skill("poison", 70);
	set_skill("staff", 50);
	set_skill("tianshan-zhang", 50);

	set("no_teach", ([
		"huagong-dafa" : "������Ҫ�������Դ��ڡ�",
	]));

	map_skill("whip", "chanhun-suo");
	map_skill("force", "huagong-dafa");
	map_skill("dodge", "zhaixinggong");
	map_skill("strike", "chousui-zhang");
	map_skill("claw", "sanyin-wugongzhao");
	map_skill("parry", "tianshan-zhang");
	map_skill("staff", "tianshan-zhang");

	prepare_skill("strike", "chousui-zhang");
	prepare_skill("claw", "sanyin-wugongzhao");

	create_family("������", 2, "����");

	setup();
}

void attempt_apprentice(object ob)
{
	command("say �ðɣ��Ҿ��������ˡ�");
	welcome(ob);
	command("recruit " + ob->query("id"));
}

