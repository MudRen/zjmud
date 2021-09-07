// gaibang npc code

inherit NPC;
inherit F_MASTER;

#include "gaibang.h"

void create()
{
	set_name("�����", ({"yu hongxing", "yu", "hongxing"}));
	set("title", "ؤ��˴�����");
	set("gender", "����");
	set("age", 30);
	set("long", 
		"����λЦ���е�ؤ��˴����ӣ����Զ��ǣ����С���á�\n");
	set("attitude", "peaceful");
	set("str", 22);
	set("int", 30);
	set("con", 24);
	set("dex", 22);

	set("qi", 1000);
	set("max_qi", 1000);
	set("jing", 530);
	set("max_jing", 530);
	set("neili", 1800);
	set("max_neili", 1800);
	set("jiali", 45);
	
	set("combat_exp", 550000);
	
	set_skill("force", 150); 
	set_skill("jiaohua-neigong", 150); 
	set_skill("unarmed", 140); 
	set_skill("changquan", 140); 
	set_skill("dodge", 140); 
	set_skill("feiyan-zoubi", 140); 
	set_skill("parry", 140); 
	set_skill("begging", 100); 
	set_skill("stealing", 30); 
	set_skill("checking", 80); 
	
	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	
	create_family("ؤ��", 19, "����");
	setup();
}

void attempt_apprentice(object ob)
{
	if( !permit_recruit(ob) ) return;

	if( ob->query("int") < 25 )
	{
		command("say ���... �Ǹ��е㲻�����ɣ�");
	}

	command("say �����������Ϊ����ֻ���߹������˼Һ��Ҳ��ر���Щ����ͽ����");
	command("say ��Ҷ�ҪΪ��Զ���밡��");
	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "beggar")
		ob->set("class", "beggar");
}
