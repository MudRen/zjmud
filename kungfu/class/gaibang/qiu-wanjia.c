// qiu-wanjia.c
// Modified by Venus Nov.1997

inherit NPC;
inherit F_MASTER;

#include "gaibang.h"

void create()								   
{
	set_name("�����", ({"qiu wanjia", "qiu", "wanjia"}));
	set("title", "ؤ���������");
	set("gender", "����");
	set("age", 16);
	set("long",
		"����λ��Ʀ�Ƶ�ؤ��������ӣ������Ǹ��Եÿ���С��Ʀ��\n");
	set("attitude", "peaceful");
	set("class", "beggar");
	set("str", 19);
	set("int", 20);
	set("con", 20);
	set("dex", 23);
	set("max_qi", 150);
	set("max_jing", 140);
	set("neili", 370);
	set("max_neili", 370);
	set("jiali", 10);
	set("combat_exp", 12000);
	set_skill("force", 35);
	set_skill("jiaohua-neigong", 35);
	set_skill("unarmed", 35);
	set_skill("changquan", 35);
	set_skill("dodge", 35);
	set_skill("feiyan-zoubi", 35);
	set_skill("parry", 35);
	set_skill("begging", 35);
	set_skill("checking", 35);
	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	create_family("ؤ��", 20, "����");
	setup();
}

void attempt_apprentice(object ob)
{
	if( !permit_recruit(ob) ) return;
	if( ob->query("gender") != "����") return;

	command("say �ðɣ�ϣ�����ܺú�ѧϰ�����书������Ϊؤ����һ��������");
	command("recruit " + ob->query("id"));
}
