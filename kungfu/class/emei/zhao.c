// zhao.c ����ʦ̫
// Modified by That Oct.1997

inherit NPC;
inherit F_MASTER;

#include <command.h>
#include <ansi.h>
#include "emei.h"
#include "tobebonze.h"

string ask_for_join();

void create()
{
	set_name("����ʦ̫", ({ "jingzhao shitai","jingzhao","shitai"}));
	set("long", "����һλ������ҵ��ã����ڸ�£����ü��Ŀ��\n");
	set("gender", "Ů��");
	set("age", 43);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("class", "bonze");

	set("str", 20);
	set("int", 21);
	set("con", 20);
	set("dex", 22);

	set("max_qi", 2100);
	set("max_jing", 1000);
	set("neili", 2500);
	set("max_neili", 2500);

	set("combat_exp", 110000);
	set_skill("persuading", 80);
	set_skill("throwing", 60);
	set_skill("force", 90);
	set_skill("dodge", 70);
	set_skill("finger", 60);
	set_skill("parry", 75);
	set_skill("strike", 70);
	set_skill("sword", 60);
	set_skill("mahayana", 60);
	set_skill("literate", 70);
	set_skill("jinding-zhang", 60);
	set_skill("tiangang-zhi", 70);
	set_skill("huifeng-jian", 60);
	set_skill("zhutian-bu", 60);
	set_skill("emei-xinfa", 90);
	set_skill("linji-zhuang", 90);
	map_skill("force","linji-zhuang");
	map_skill("finger","tiangang-zhi");
	map_skill("dodge","zhutian-bu");
	map_skill("strike","jinding-zhang");
	map_skill("sword","huifeng-jian");
	map_skill("parry","huifeng-jian");

	set("inquiry",([
		"���"  : (: ask_for_join :),
		"����"  : (: ask_for_join :),
		"����"  : "���ҵ��ӣ����ܻ��ס���������ʦ̫�ɡ�",
	]));

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

	command("say �����ӷ����գ����գ��ðɣ��Ҿ��������ˡ�");
	command("say ϣ�������Դȱ�֮�ģ����ǻ�֮����Ŭ�����ƣ��ö�������");
	command("recruit " + ob->query("id"));
}
