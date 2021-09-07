// jia.c ����ʦ̫
// Modified by That Oct.1997

inherit NPC;
inherit F_MASTER;

#include <command.h>
#include <ansi.h>
#include "emei.h"
#include "tobebonze.h"

void create()
{
	set_name("����ʦ̫", ({ "jingjia shitai","jingjia","shitai"}));
	set("long", "����һλ������ҵ��ã����ڸ�£����ü��Ŀ��\n");
	set("gender", "Ů��");
	set("age", 44);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("class", "bonze");
	set("inquiry",([
		"���"  : (: ask_for_join :),
		"����"  : (: ask_for_join :),
		"����"  : "���ҵ��ӣ����ܻ��ס���������ʦ̫�ɡ�",
	]));

	set("str", 23);
	set("int", 25);
	set("con", 26);
	set("dex", 21);

	set("max_qi", 2900);
	set("max_jing", 1500);
	set("neili", 3100);
	set("max_neili", 3100);

	set("combat_exp", 375000);
	set_skill("persuading", 80);
	set_skill("throwing", 70);
	set_skill("force", 140);
	set_skill("dodge", 60);
	set_skill("finger", 60);
	set_skill("parry", 140);
	set_skill("strike", 130);
	set_skill("blade", 70);
	set_skill("literate", 60);
	set_skill("mahayana", 60);
	set_skill("jinding-zhang", 130);
	set_skill("tiangang-zhi", 60);
	set_skill("yanxing-dao", 70);
	set_skill("zhutian-bu", 70);
	set_skill("emei-xinfa", 140);
	set_skill("linji-zhuang", 140);
	map_skill("force","linji-zhuang");
	map_skill("finger","tiangang-zhi");
	map_skill("dodge","zhutian-bu");
	map_skill("strike","jinding-zhang");
	map_skill("blade","yanxing-dao");
	map_skill("parry","yanxing-dao");

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
