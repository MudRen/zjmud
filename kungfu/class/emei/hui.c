// hui.c ����ʦ̫
// Modified by That Oct.1997

inherit NPC;
inherit F_MASTER;

#include <command.h>
#include <ansi.h>
#include "emei.h"
#include "tobebonze.h"

void create()
{
	set_name("����ʦ̫", ({ "jinghui shitai","jinghui","shitai"}));
	set("long", "���Ƕ�������ʦ�㣬ֻ��������˸˸����"
		    "��ͣ��ɨ�������ܡ���\n");
	set("gender", "Ů��");
	set("age", 45);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("class", "bonze");

	set("inquiry",([
		"���"  : (: ask_for_join :),
		"����"  : (: ask_for_join :),
		"����"  : "���ҵ��ӣ����ܻ��ס���������ʦ̫�ɡ�",
	]));

	set("str", 22);
	set("int", 20);
	set("con", 24);
	set("dex", 23);

	set("max_qi", 3100);
	set("max_jing", 1600);
	set("neili", 3300);
	set("max_neili", 3300);

	set("combat_exp", 380000);
	set_skill("persuading", 80);
	set_skill("throwing", 60);
	set_skill("force", 145);
	set_skill("dodge", 110);
	set_skill("finger", 100);
	set_skill("parry", 145);
	set_skill("strike", 145);
	set_skill("sword", 95);
	set_skill("literate", 100);
	set_skill("mahayana", 110);
	set_skill("jinding-zhang", 145);
	set_skill("tiangang-zhi", 90);
	set_skill("huifeng-jian", 90);
	set_skill("zhutian-bu", 110);
	set_skill("emei-xinfa", 145);
	set_skill("linji-zhuang", 145);
	map_skill("force","linji-zhuang");
	map_skill("finger","tiangang-zhi");
	map_skill("dodge","zhutian-bu");
	map_skill("strike","jinding-zhang");
	map_skill("sword","huifeng-jian");
	map_skill("parry","huifeng-jian");

	create_family("������", 4, "����");

	set("no_teach", ([
		"linji-zhuang" : "��ѧ�ټ�ʮ��ׯ�������ʦ̫ȥ��",
	]));

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/city/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query("shen") < 1000)
	{
		command("say " + RANK_D->query_respect(ob) +
			"����������֮�»����Ĳ�����");
		return;
	}

	if ((int)ob->query_skill("mahayana",1) < 50)
	{
		command("say ���˷𷨵���Ϊ��Ҫ���Щ��");
		return;
	}

	command("say �����ӷ����գ����գ��ðɣ��Ҿ��������ˡ�");
	command("say ϣ�������Դȱ�֮�ģ����ǻ�֮����Ŭ�����ƣ��ö�������");
	command("recruit " + ob->query("id"));
}
