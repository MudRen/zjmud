// shihou.c ʨ����

inherit NPC;
inherit F_MASTER;

#include "xingxiu.h"

string ask_me();

void create()
{
	set_name("ʨ����", ({ "shihou zi", "shihou" }));
	set("nickname", "�����ɶ�ʦ��");
	set("long", 
		"�����Ƕ�����Ķ�����ʨ���ӡ�\n"
		"����ʮ���꣬ʨ�����ڣ�һ����֪����������ʿ��\n");
	set("gender", "����");
	set("age", 32);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("class", "fighter");
	set("str", 28);
	set("int", 20);
	set("con", 26);
	set("dex", 22);
	
	set("max_qi", 2500);
	set("max_jing", 1200);
	set("neili", 2800);
	set("max_neili", 2800);
	set("jiali", 25);
	set("combat_exp", 220000);

	set_skill("force", 120);
	set_skill("huagong-dafa", 120);
	set_skill("guixi-gong", 140);
	set_skill("dodge", 90);
	set_skill("zhaixinggong", 90);
	set_skill("strike", 120);
	set_skill("chousui-zhang", 120);
	set_skill("claw", 100);
	set_skill("sanyin-wugongzhao", 100);
	set_skill("parry", 100);
	set_skill("poison", 80);
	set_skill("staff", 50);
	set_skill("tianshan-zhang", 50);

	set("no_teach", ([
		"huagong-dafa" : "������Ҫ�������Դ��ڡ�",
	]));

	map_skill("force", "huagong-dafa");
	map_skill("dodge", "zhaixinggong");
	map_skill("claw", "sanyin-wugongzhao");
	map_skill("strike", "chousui-zhang");
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


