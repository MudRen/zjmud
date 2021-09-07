// gaibang npc code

inherit NPC;
inherit F_MASTER;

#include "gaibang.h"

void create()
{
	set_name("ºÎ²»¾»", ({"he bujing", "he", "bujing"}));
	set("title", "Ø¤°ïÆß´üµÜ×Ó");
	set("gender", "ÄĞĞÔ");
	set("age", 30);
	set("long", 
		"ÕâÊÇÎ»ÒÂÖøååËú£¬ÅîÍ·¹¸ÃæµÄØ¤°ïÆß´üµÜ×Ó¡£\n");
	set("attitude", "heroism");
	set("class", "beggar");
	set("str", 28);
	set("int", 22);
	set("con", 24);
	set("dex", 23);

	set("qi", 850);
	set("max_qi", 850);
	set("max_jing", 420);
	set("neili", 1800);
	set("max_neili", 1800);
	set("jiali", 35);
	
	set("combat_exp", 270000);
	
	set_skill("force", 125);
	set_skill("jiaohua-neigong", 125);
	set_skill("unarmed", 120);
	set_skill("changquan", 120);
	set_skill("dodge", 110);
	set_skill("feiyan-zoubi", 110);
	set_skill("parry", 120);
	set_skill("begging", 60);
	set_skill("stealing", 50);
	
	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "changquan");
	map_skill("parry", "changquan");
	map_skill("dodge", "feiyan-zoubi");
	
	create_family("Ø¤°ï", 19, "µÜ×Ó");
	setup();
}

void attempt_apprentice(object ob)
{
	if( !permit_recruit(ob) ) return;
	if( ob->query("combat_exp") > 120000 ) return;

	command("say ÄãºÜ°®´ò¼Ü°É£¿ ¹ş¹ş¹ş£¬ºÃ°É£¬ÎÒ¾ÍÊÕÏÂÄãÁË£¡");
	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "beggar")
		ob->set("class", "beggar");
}
