// ma.c ����
// By Lgg,1998.10

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

string ask_me();

void create()
{
	set_name("����", ({"ma yu", "ma"}));
	set("gender", "����");
	set("age", 42);
	set("class", "taoist");
	set("nickname",MAG"������"NOR);
	set("long",
		"�������������Ĵ���ӣ�ȫ������֮�ף����������������ˡ�\n"
		"����ü��Ŀ���Ͱ����ף���Ц�ſ����㡣\n");
	set("attitude", "peaceful");
	set("shen_type",1);
	set("str", 28);
	set("int", 32);
	set("con", 31);
	set("dex", 30);

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

	set("qi", 4500);
	set("max_qi", 4500);
	set("jing", 2200);
	set("max_jing", 2200);
	set("neili", 4700);
	set("max_neili", 4700);
	set("jiali", 100);

	set("combat_exp", 1400000);

	set_skill("force", 180);
	set_skill("quanzhen-xinfa", 180);
	set_skill("sword", 170);
	set_skill("quanzhen-jian",170);
	set_skill("dodge", 180);
	set_skill("jinyan-gong", 180);
	set_skill("parry", 180);
	set_skill("literate",100);
	set_skill("strike", 180);
	set_skill("chongyang-shenzhang", 180);
	set_skill("haotian-zhang", 180);
	set_skill("finger",180);
	set_skill("zhongnan-zhi", 180);
	set_skill("taoism",150);
	set_skill("medical", 210);
	set_skill("liandan-shu", 210);

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
		"���㹦" : (: ask_me :),
		"����ͼ��" : (: ask_me :),
	]) );

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query_skill("quanzhen-xinfa", 1) < 100)
	{
		command("say ��ı����ڹ��ķ�����㣬�������Ը�������书��");
		return;
	}
	if ((int)ob->query("shen") < 10000)
	{
		command("say ���������ұ�ѧ�������������ģ���������Ŀɲ�������\n");
		return;
	}
	command("pat " + ob->query("id"));
	command("say �ðɣ��Ҿ����������ͽ���ˡ�");
	command("recruit " + ob->query("id"));
}

string ask_me()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "ȫ���")
		return RANK_D->query_respect(this_player()) +
		"�뱾�̺��޹ϸ��ҽ̵��书�伮�ɲ��ܽ����㡣";
	if (query("book_count") < 1)
		return "�������ˣ�����ͼ���Ѿ�����ȡ���ˡ�";
	add("book_count", -1);
	ob = new("/clone/book/jinyantu");
	ob->move(this_player());
	return "�ðɣ��Ȿ������ͼ�ס����û�ȥ�ú��ж���";

}

