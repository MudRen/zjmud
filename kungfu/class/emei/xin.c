// xin.c ����ʦ̫
// Modified by That Oct.1997

#include <ansi.h>
#include "tobebonze.h"

inherit NPC;
inherit F_GUARDER;

void create()
{
	set_name("����ʦ̫", ({ "jingxin shitai","jingxin","shitai"}));
	set("long", "����һλ������ҵ��ã����ڸ�£����ü��Ŀ��\n");
	set("gender", "Ů��");
	set("age", 45);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("class", "bonze");

	set("str", 20);
	set("int", 21);
	set("con", 24);
	set("dex", 21);

	// guarder, so the qi & neili will be more longer than others
	set("max_qi", 4800);
	set("max_jing", 2400);
	set("neili", 4500);
	set("max_neili", 4500);

	set("combat_exp", 130000);
	set_skill("persuading", 80);
	set_skill("throwing", 80);
	set_skill("force", 100);
	set_skill("dodge", 90);
	set_skill("finger", 80);
	set_skill("parry", 90);
	set_skill("strike", 90);
	set_skill("blade", 80);
	set_skill("literate", 90);
	set_skill("mahayana", 100);
	set_skill("jinding-zhang", 100);
	set_skill("tiangang-zhi", 90);
	set_skill("yanxing-dao", 90);
	set_skill("zhutian-bu", 95);
	set_skill("emei-xinfa", 100);
	set_skill("linji-zhuang", 100);
	map_skill("force","linji-zhuang");
	map_skill("finger","tiangang-zhi");
	map_skill("dodge","zhutian-bu");
	map_skill("strike","jinding-zhang");
	map_skill("blade","yanxing-dao");
	map_skill("parry","yanxing-dao");

	set("inquiry",([
		"���"  : (: ask_for_join :),
		"����"  : (: ask_for_join :),
		"����"  : "���ҵ��ӣ����ܻ��ס���������ʦ̫�ɡ�",
	]));
	create_family("������", 4, "����");

	set("coagents", ({
		([ "id"	: "zhou zhiruo",
		   "startroom" : "/d/emei/qinggong", ]),
	}));
	setup();
	carry_object("/d/city/obj/gangdao")->wield();
	carry_object("/d/city/obj/cloth.c")->wear();
}

void attempt_apprentice(object ob)
{
	command ("say �����ӷ�ƶ�᲻�յ��ӡ�\n");
	return;
}
