// kong.c ����ʦ̫
// Modified By That Oct.1997

inherit NPC;
inherit F_MASTER;

#include <command.h>
#include <ansi.h>
#include "emei.h"
#include "tobebonze.h"

void create()
{
	set_name("����ʦ̫", ({ "jingkong shitai","jingkong","shitai"}));
	set("long", "���Ƕ�������ʦ�㣬һλ������ҵ��ã����ڸ�£����ü��Ŀ��\n");
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
	set("int", 21);
	set("con", 23);
	set("dex", 21);

	set("max_qi", 2800);
	set("max_jing", 500);
	set("neili", 2900);
	set("max_neili", 2900);

	set("combat_exp", 240000);
	set_skill("persuading", 80);
	set_skill("force", 125);
	set_skill("throwing", 80);
	set_skill("dodge", 90);
	set_skill("finger", 120);
	set_skill("parry", 80);
	set_skill("strike", 100);
	set_skill("blade", 90);
	set_skill("literate", 90);
	set_skill("mahayana", 100);
	set_skill("jinding-zhang", 90);
	set_skill("tiangang-zhi", 120);
	set_skill("yanxing-dao", 80);
	set_skill("zhutian-bu", 100);
	set_skill("emei-xinfa", 125);
	set_skill("linji-zhuang", 125);
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
