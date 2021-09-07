// xuan.c ����ʦ̫
//Modified by That Oct.1997

#include <command.h>
#include <ansi.h>
#include "tobebonze.h"
#include "emei.h"

inherit NPC;
inherit F_MASTER;
string ask_for_join();

void create()
{
	set_name("����ʦ̫", ({ "jingxuan shitai","jingxuan","shitai"}));
	set("long", "���Ƕ����ɴ�ʦ�㣬�������ʦ̫��ʮ���أ�"
		    "�����ɵĹ����Ѿ���������\n");
	set("gender", "Ů��");
	set("age", 42);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("class", "bonze");
	set("inquiry",([
		"���"  : (: ask_for_join :),
		"����"  : (: ask_for_join :),
		"����"  : "���ҵ��ӣ����ܻ��ס���������ʦ̫�ɡ�",
	]));

	set("str", 24);
	set("int", 27);
	set("con", 25);
	set("dex", 22);

	set("max_qi", 3000);
	set("max_jing", 1500);
	set("neili", 4100);
	set("max_neili", 4100);

	set("combat_exp", 750000);
	set_skill("persuading", 100);
	set_skill("throwing", 120);
	set_skill("force", 165);
	set_skill("dodge", 140);
	set_skill("finger", 150);
	set_skill("parry", 160);
	set_skill("strike", 120);
	set_skill("sword", 160);
	set_skill("literate", 100);
	set_skill("mahayana", 140);
	set_skill("jinding-zhang", 150);
	set_skill("tiangang-zhi", 120);
	set_skill("huifeng-jian", 160);
	set_skill("zhutian-bu", 140);
	set_skill("emei-xinfa", 165);
	set_skill("linji-zhuang", 165);
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

	if ((int)ob->query("shen") < 5000)
	{
		command("say " + RANK_D->query_respect(ob) +
			"����������֮�»����Ĳ�����");
		return;
	}

	if ((int)ob->query_skill("mahayana",1) < 80)
	{
		command("say ���˷𷨵���Ϊ��Ҫ���Щ��");
		return;
	}

	command("say �����ӷ����գ����գ��ðɣ��Ҿ��������ˡ�");
	command("say ϣ�������Դȱ�֮�ģ����ǻ�֮����Ŭ�����ƣ��ö�������");
	command("recruit " + ob->query("id"));
}
