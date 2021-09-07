// li-futou.c
// Modified by Venus. Nov.1997

inherit NPC;
inherit F_MASTER;

#include "gaibang.h"

void create()
{
	set_name("�ͷ", ({"li futou", "li", "futou"}));
	set("title", "ؤ����������");
	set("gender", "����");
	set("class", "beggar");
	set("age", 20);
	set("long",
		"����λؤ���������ӣ������Ǹ���ز�¶�ĸ��֡�\n");
	set("attitude", "peaceful");
	set("str", 27);
	set("int", 25);
	set("con", 24);
	set("dex", 27);
	set("max_qi", 250);
	set("max_jing", 220);
	set("neili",300);
	set("max_neili", 300);
	set("jiali",30);
	set("combat_exp", 320000);

	set_skill("force", 120);
	set_skill("jiaohua-neigong", 120);
	set_skill("unarmed", 120);
	set_skill("changquan", 120);
	set_skill("dodge", 120);
	set_skill("feiyan-zoubi", 120);
	set_skill("parry", 120);
	set_skill("begging", 50);
	set_skill("checking", 50);
	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	create_family("ؤ��", 19, "����");
	setup();
}

void attempt_apprentice(object ob)					      
{
	if( !permit_recruit(ob) ) return;
	if( ob->query("gender") != "����") return;

	command("say �ðɣ�ϣ�����ܺú�ѧϰ�����书������Ϊؤ����һ��������");
	command("recruit " + ob->query("id"));
}
