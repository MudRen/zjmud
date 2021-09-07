// gaibang npc code

inherit NPC;
inherit F_MASTER;

#include "gaibang.h"

void create()
{
	set_name("����", ({"li sheng", "li", "sheng"}));
	set("title", "ؤ��˴�����");
	set("gender", "����");
	set("age", 38);
	set("long", 
		"����λ���Ը�ֱ����������ؤ��˴����ӡ�\n");
	set("attitude", "peaceful");
	set("str", 32);
	set("int", 18);
	set("con", 20);
	set("dex", 23);

	set("max_qi", 390);
	set("max_jing", 300);
	set("neili", 800);
	set("max_neili", 800);
	set("jiali", 40);

	set("combat_exp", 480000);

	set_skill("force", 140);
	set_skill("jiaohua-neigong", 140);
	set_skill("unarmed", 120);
	set_skill("changquan", 120);
	set_skill("dodge", 100);
	set_skill("feiyan-zoubi", 100);
	set_skill("parry", 140);
	set_skill("staff", 135);
	set_skill("strike", 130);
	set_skill("jiaohua-bangfa", 135);
	set_skill("shenlong-baiwei", 130);
	set_skill("begging", 60);
	set_skill("checking", 110);

	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("strike", "shenlong-baiwei");

	set("no_teach/shenlong-baiwei", "�⡢���Ǻ�������ҵģ��Ҳ����Ҵ���");

	create_family("ؤ��", 19, "����");
	setup();
}

void attempt_apprentice(object ob)
{
	if( !permit_recruit(ob) ) return;
	if( ob->query("shen") < 0 )
	{
		command("say ���д�����Ϊؤ����ӣ���Ȼ�������£�");
		return;
	}

	command("say �ã���������һ��һ���˲�����ͽ�ܣ��һ�ϲ���������أ�");
	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "beggar")
		ob->set("class", "beggar");
}
