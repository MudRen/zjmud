// bei.c ������

#include "emei.h"

inherit NPC;
inherit F_MASTER;
int ask_for_ji();

void create()
{
	set_name("������", ({ "bei jinyi", "bei", "jinyi"}));
	set("long", "���Ƕ����ɵĵ��Ĵ��׼ҵ��ӡ�\n");
	set("gender", "Ů��");
	set("age", 21);
	set("attitude", "peaceful");
	set("class", "fighter");
	set("shen_type", 1);

	set("str", 21);
	set("int", 25);
	set("con", 24);
	set("dex", 20);

	set("max_qi", 2100);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);
	set("inquiry",([
		"����ܽ"  : (: ask_for_ji :),
	]));

	set("combat_exp", 250000);
	set_skill("throwing", 30);
	set_skill("persuading", 50);
	set_skill("force", 130);
	set_skill("dodge", 90);
	set_skill("finger", 85);
	set_skill("parry", 70);
	set_skill("strike", 60);
	set_skill("sword", 130);
	set_skill("jinding-zhang", 60);
	set_skill("tiangang-zhi", 85);
	set_skill("huifeng-jian", 130);
	set_skill("zhutian-bu", 90);
	set_skill("emei-xinfa", 130);
	map_skill("force","emei-xinfa");
	map_skill("finger","tiangang-zhi");
	map_skill("dodge","zhutian-bu");
	map_skill("strike","jinding-zhang");
	map_skill("sword","huifeng-jian");
	map_skill("parry","huifeng-jian");

	create_family("������", 4, "����");

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/city/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	command("say �ðɣ��Ҿ��������ˡ�");
	command("recruit " + ob->query("id"));
}

int ask_for_ji()
{
	object ob;
	ob = this_player();
	tell_object(ob,"������˵��������ܽ���������ء��������벻�����ˣ�\n"); 
	ob->set("marks/ji",1);
	return 1;
}

