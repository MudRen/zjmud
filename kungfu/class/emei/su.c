// su.c ������

#include "emei.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("������", ({ "su mengqing","su","mengqing"}));
	set("long", "���Ƕ����ɵĵ��Ĵ��׼ҵ��ӡ�\n");
	set("gender", "Ů��");
	set("age", 22);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("class", "fighter");

	set("str", 18);
	set("int", 21);
	set("con", 20);
	set("dex", 19);

	set("max_qi", 1400);
	set("max_jing", 700);
	set("neili", 1700);
	set("max_neili", 1700);

	set("combat_exp", 70000);
	set_skill("throwing", 40);
	set_skill("persuading", 40);
	set_skill("force", 50);
	set_skill("dodge", 60);
	set_skill("finger", 60);
	set_skill("parry", 60);
	set_skill("strike", 60);
	set_skill("sword", 50);
	set_skill("jinding-zhang", 60);
	set_skill("tiangang-zhi", 60);
	set_skill("huifeng-jian", 50);
	set_skill("zhutian-bu", 60);
	set_skill("emei-xinfa", 50);

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
