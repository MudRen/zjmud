// yin.c ��־ƽ
// By Lgg,1998.10

#include <ansi.h>;
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("��־ƽ", ({"yin zhiping", "yin"}));
	set("gender", "����");
	set("class", "taoist");
	set("nickname", HIM"�������"NOR);
	set("age", 24);
	set("long",
		"�����𴦻��ĵ���������־ƽ������ü���ۣ�������ЩӢ����\n"
		"�ţ���ȫ��̵����������������������Ϊ����Ĳ��ߣ�ü���\n"
		"�ƺ���һ������֮ɫ�����ĵ��ǳ�ü��Ŀ����ò���ţ�������룬\n"
		"��ϧ��ȸ���������в��͡�\n");
	set("attitude", "friendly");
	set("shen_type",1);
	set("str", 28);
	set("int", 25);
	set("con", 25);
	set("dex", 25);

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

	set("qi", 1500);
	set("max_qi", 1500);
	set("jing", 800);
	set("max_jing", 800);
	set("neili", 3000);
	set("max_neili", 3000);
	set("jiali", 60);

	set("combat_exp", 220000);

	set_skill("force", 110);
	set_skill("quanzhen-xinfa", 110);
	set_skill("sword", 100);
	set_skill("quanzhen-jian", 100);
	set_skill("dodge", 90);
	set_skill("jinyan-gong", 90);
	set_skill("parry", 110);
	set_skill("finger",100);
	set_skill("zhongnan-zhi", 100);
	set_skill("strike", 100);
	set_skill("chongyang-shenzhang", 100);
	set_skill("literate",60);
	set_skill("taoism",60);

	map_skill("force", "quanzhen-xinfa");
	map_skill("sword", "quanzhen-jian");
	map_skill("dodge", "jinyan-gong");
	map_skill("parry", "quanzhen-jian");
	map_skill("finger", "zhongnan-zhi");
	map_skill("strike", "chongyang-shenzhang");
	prepare_skill("finger", "zhongnan-zhi");
	prepare_skill("strike", "chongyang-shenzhang");

	create_family("ȫ���", 3, "����");

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

	command("say �ðɣ��Ҿ����������ͽ���ˡ�");
	command("recruit " + ob->query("id"));
}
