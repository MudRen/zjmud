// gaibang npc code

inherit NPC;
inherit F_MASTER;

#include "gaibang.h"

void create()
{
	set_name("��ȫ", ({"zuo quan", "zuo", "quan"}));
	set("title", "ؤ���ߴ�����");
	set("gender", "����");
	set("age", 35);
	set("long", 
		"����λ��ˬ�󷽵�ؤ���ߴ����ӣ������Ǹ����غ��ܡ�\n");
	set("attitude", "peaceful");
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 26);

	set("qi", 720);
	set("max_qi", 720);
	set("jing", 400);
	set("max_jing", 400);
	set("neili", 1210);
	set("max_neili", 1210);
	set("jiali", 32);
	
	set("combat_exp", 350000);
	
	set_skill("force", 130); 
	set_skill("jiaohua-neigong", 130); 
	set_skill("unarmed", 130); 
	set_skill("changquan", 130); 
	set_skill("dodge", 130); 
	set_skill("feiyan-zoubi", 130); 
	set_skill("parry", 120); 
	set_skill("begging", 80); 
	set_skill("checking", 60); 
	
	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	
	create_family("ؤ��", 19, "����");
	setup();
}

void attempt_apprentice(object ob)
{
	if( !permit_recruit(ob) ) return;

	command("say �ðɣ�ϣ�����ܺú�ѧϰ�����书������Ϊؤ����һ��������");
	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "beggar")
		ob->set("class", "beggar");
}
