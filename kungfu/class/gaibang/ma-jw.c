// gaibang npc code

inherit NPC;
inherit F_MASTER;

#include "gaibang.h"

void create()
{
	set_name("���Ϊ", ({"ma juwei", "ma", "juwei"}));
	set("title", "ؤ���ߴ�����");
	set("gender", "����");
	set("age", 35);
	set("long", 
		"����λ���վ�ǿ��ȴ��Ĭ���Ե�ؤ���ߴ����ӡ�\n");
	set("attitude", "peaceful");
	set("str", 25);
	set("int", 22);
	set("con", 25);
	set("dex", 30);

	set("qi", 800);
	set("max_qi", 800);
	set("jing", 350);
	set("max_jing", 350);
	set("neili", 1400);
	set("max_neili", 1400);
	set("jiali", 32);
	
	set("combat_exp", 180000);
	
	set_skill("force", 120);
	set_skill("jiaohua-neigong", 120);
	set_skill("unarmed", 120);
	set_skill("changquan", 120);
	set_skill("dodge", 120);
	set_skill("feiyan-zoubi", 120);
	set_skill("parry", 120);
	set_skill("staff", 120);
	set_skill("begging", 60);

	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("parry", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	
	create_family("ؤ��", 19, "����");
	setup();
}

void attempt_apprentice(object ob)
{
	if( !permit_recruit(ob) ) return;
	if( ob->query_con() < 22 )
	{
		command("say ��ĸ��ǲ��ѣ��Բ��˿࣬�������˰ɣ�");
		return;
	}

	command("say �����Ϊʦ����Ҫ���óԿ��׼�����ú�����ؤ����ӣ�");
	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "beggar")
		ob->set("class", "beggar");
}
