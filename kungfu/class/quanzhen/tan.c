// tan.c ̷����
// By Lgg,1998.10

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("̷����", ({"tan chuduan", "tan"}));
	set("gender", "����");
	set("age", 40);
	set("class", "taoist");
	set("nickname",HIY"������"NOR);
	set("long",
		"������ȫ���ͽ̷����̷���ˣ�����Ŀ��࣬Ũü���ۣ�ɤ��\n"
		"����������������Ϊʦǰ������������\n");
	set("attitude", "peaceful");
	set("shen_type",1);
	set("str", 34);
	set("int", 28);
	set("con", 28);
	set("dex", 28);

	set("title","ȫ������֮��");
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: exert_function, "recover" :),
		(: exert_function, "recover" :),
		(: perform_action, "strike.ju" :),
		(: perform_action, "strike.ju" :),
		(: perform_action, "strike.ju" :),
		(: perform_action, "sword.ding" :),
		(: perform_action, "sword.ding" :),
		(: perform_action, "sword.ding" :),
	}));

	set("qi", 4000);
	set("max_qi", 4000);
	set("jing", 2000);
	set("max_jing", 2000);
	set("neili", 4200);
	set("max_neili", 4200);
	set("jiali", 100);

	set("combat_exp", 1200000);

	set_skill("force", 150);
	set_skill("quanzhen-xinfa", 160);
	set_skill("sword", 150);
	set_skill("quanzhen-jian",160);
	set_skill("dodge", 140);
	set_skill("jinyan-gong", 140);
	set_skill("parry", 150);
	set_skill("strike", 150);
	set_skill("chongyang-shenzhang", 150);
	set_skill("haotian-zhang", 150);
	set_skill("literate",80);
	set_skill("finger",140);
	set_skill("zhongnan-zhi", 140);
	set_skill("taoism",100);

	map_skill("force", "quanzhen-xinfa");
	map_skill("sword", "quanzhen-jian");
	map_skill("dodge", "jinyan-gong");
	map_skill("parry", "quanzhen-jian");
	map_skill("finger", "zhongnan-zhi");
	map_skill("strike", "haotian-zhang");
	prepare_skill("finger", "zhongnan-zhi");
	prepare_skill("strike","haotian-zhang");

	create_family("ȫ���", 2, "����");

	set("book_count",1);
	set("inquiry", ([
		"ȫ���" :  "��ȫ��������µ����������ڡ�\n",
	]) );

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query_skill("quanzhen-xinfa", 1) < 80)
	{
		command("say ��ı����ڹ��ķ�����㣬�������Ը�������书��");
		return;
	}
	if ((int)ob->query("shen") < 8000)
	{
		command("say �ҿ��㻹�Ƕ���һЩ����֮�°ɡ�\n");
		return;
	}
	command("say �ðɣ��Ҿ����������ͽ���ˡ�");
	command("recruit " + ob->query("id"));
}

