// xu.c ����ʦ̫
// Modified by That Oct.1997

inherit NPC;
inherit F_MASTER;

#include <command.h>
#include <ansi.h>
#include "emei.h"
#include "tobebonze.h"

void create()
{
       set_name("����ʦ̫", ({ "jingxu shitai","jingxu","shitai"}));
	set("long", "���Ƕ����ɶ�ʦ�㣬�������¶��꣬"
		    "һ�׶����Ʒ�������������\n");
	set("gender", "Ů��");
	set("age", 43);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("class", "bonze");

	set("str", 21);
	set("int", 23);
	set("con", 22);
	set("dex", 21);

	set("max_qi", 2400);
	set("max_jing", 1200);
	set("neili", 3100);
	set("max_neili", 3100);

	set("combat_exp", 570000);
	set_skill("persuading", 90);
	set_skill("throwing", 120);
	set_skill("force", 155);
	set_skill("dodge", 140);
	set_skill("finger", 100);
	set_skill("parry", 155);
	set_skill("strike", 155);
	set_skill("blade", 100);
	set_skill("literate", 90);
	set_skill("mahayana", 120);
	set_skill("jinding-zhang", 155);
	set_skill("tiangang-zhi", 90);
	set_skill("yanxing-dao", 100);
	set_skill("zhutian-bu", 140);
	set_skill("emei-xinfa", 155);
	set_skill("linji-zhuang", 155);
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

	set("inquiry",([
		"���"  : (: ask_for_join :),
		"����"  : (: ask_for_join :),
		"����"  : "���ҵ��ӣ����ܻ��ס���������ʦ̫�ɡ�",
	]));

	setup();
	carry_object("/d/city/obj/gangdao")->wield();
	carry_object("/d/city/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query("shen") < 2000)
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
