// xian.c ����ʦ̫
// Modified By That Oct.1997

inherit NPC;
inherit F_MASTER;

#include <command.h>
#include <ansi.h>
#include "emei.h"
#include "tobebonze.h"

void create()
{
	set_name("����ʦ̫", ({ "jingxian shitai","jingxian","shitai"}));
	set("long", "����һλ������ҵ��ã������ۣ�������"
		    "�������ϣ�üĿ֮����һ�����֮����\n");
	set("gender", "Ů��");
	set("age", 45);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("class", "bonze");

	set("str", 19);
	set("int", 22);
	set("con", 20);
	set("dex", 24);

	set("max_qi", 1800);
	set("max_jing", 900);
	set("neili", 2100);
	set("max_neili", 2100);

	set("combat_exp", 120000);
	set_skill("persuading", 80);
	set_skill("throwing", 70);
	set_skill("force", 70);
	set_skill("dodge", 70);
	set_skill("finger", 60);
	set_skill("parry", 70);
	set_skill("strike", 65);
	set_skill("blade", 60);
	set_skill("mahayana", 60);
	set_skill("literate", 60);
	set_skill("jinding-zhang", 60);
	set_skill("tiangang-zhi", 60);
	set_skill("yanxing-dao", 60);
	set_skill("zhutian-bu", 70);
	set_skill("emei-xinfa", 70);
	set_skill("linji-zhuang", 100);
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

	command("say �����ӷ����գ����գ��ðɣ��Ҿ��������ˡ�");
	command("say ϣ�������Դȱ�֮�ģ����ǻ�֮����Ŭ�����ƣ��ö�������");
	command("recruit " + ob->query("id"));
}
