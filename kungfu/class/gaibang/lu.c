// sample master.c code
inherit NPC;
inherit F_MASTER;

#include "gaibang.h"

void consider();

void create()
{
	set_name("³�н�", ({"lu youjiao", "lu", "youjiao"}));
	set("title", "ؤ��Ŵ�����");
	set("nickname", "�ư���ͷ");
	set("gender", "����");
	set("age", 45);
	set("long", 
		"³�н���Ȼ�书�㲻�ö�����֣������ڽ�����ȴ����������\n"
		"��Ϊ����ؤ�����������壬���¹������䣬��ú��߹������ء�\n");
	set("attitude", "peaceful");
	set("str", 35);
	set("int", 21);
	set("con", 32);
	set("dex", 25);

	set("qi", 2500);
	set("max_qi", 2500);
	set("jing", 1200);
	set("max_jing", 1200);
	set("neili", 4000);
	set("max_neili", 4000);
	set("jiali", 80);
	
	set("combat_exp", 1000000);
	set("shen_type", 1);
	set("score", 25000);
	
	set_skill("force", 180);
	set_skill("jiaohua-neigong", 180);
	set_skill("unarmed", 180);
	set_skill("changquan", 150);
	set_skill("dodge", 150);
	set_skill("feiyan-zoubi", 150);
	set_skill("parry", 170);
	set_skill("staff", 170);
	set_skill("begging", 120);
	set_skill("checking", 150);
	set_skill("jueming-tui", 180);

	map_skill("force", "jiaohua-neigong");
	map_skill("unarmed", "jueming-tui");
	map_skill("parry", "jueming-tui");
	map_skill("dodge", "feiyan-zoubi");
	
	create_family("ؤ��", 18, "�Ŵ�����");

	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: perform_action, "unarmed.xianglong" :),
		(: exert_function, "recover" :),
	}) );

	setup();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob)) return;

	if ((int)ob->query_str() < 26)
	{
		command("say ����ؤ�������һ���Ը���Ϊ����" + RANK_D->query_respect(ob) + "�������У��ƺ�����ѧؤ��Ĺ���");
		return;
	}

	if (ob->query_skill("force") < 150)
	{
		command("say ����ڹ���򻹲��У��Ⱥͱ��ʦ��ѧϰ�ɡ�");
		return;
	}

	command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
		"�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");

	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "beggar")
		ob->set("class", "beggar");
}

int recognize_apprentice(object me)
{
	if (me->query("family/family_name") != query("family/family_name"))
		return 0;

	if (me->query("beggarlvl") < 9)
		return 0;

	return 1;
}
