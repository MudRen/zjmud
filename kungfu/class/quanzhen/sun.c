// sun.c �ﲻ��
// By Lgg,1998.10

#include <ansi.h>
#include "quanzhen.h"

inherit NPC;
inherit F_MASTER;

string ask_me();

void create()
{
	set_name("�ﲻ��", ({"sun buer", "sun"}));
	set("gender", "Ů��");
	set("age", 33);
	set("class", "taoist");
	set("nickname",CYN"�徻ɢ��"NOR);
	set("long",
		"������ȫ��̶���������Ψһ��Ů�����ﲻ�������ˡ�������\n"
		"�������ǰ�����ӣ�����������һ������ͷ��\n");
	set("attitude", "peaceful");
	set("shen_type",1);
	set("str", 30);
	set("int", 29);
	set("con", 29);
	set("dex", 29);

	set("title","ȫ������֮ĩ");
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

	set("qi", 3700);
	set("max_qi", 3700);
	set("jing", 1800);
	set("max_jing", 1800);
	set("neili", 4100);
	set("max_neili", 4100);
	set("jiali", 100);

	set("combat_exp", 660000);

	set_skill("force", 140);
	set_skill("quanzhen-xinfa", 140);
	set_skill("sword", 150);
	set_skill("quanzhen-jian",150);
	set_skill("dodge", 150);
	set_skill("jinyan-gong", 150);
	set_skill("parry", 140);
	set_skill("strike", 140);
	set_skill("chongyang-shenzhang", 140);
	set_skill("haotian-zhang", 140);
	set_skill("literate",100);
	set_skill("finger",120);
	set_skill("zhongnan-zhi", 120);
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
		"�����" :  (: ask_me :),
		"����Ʒ�" :  (: ask_me :),
	]) );

	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/quanzhen/npc/obj/grayrobe")->wear();

}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if (ob->query("gender") == "����")
	{
		command("say �Ҳ�����ͽ���㻹��ȥ���Ҽ�λʦ��Ϊʦ�ɡ�\n");
		return;
	}

	if ((int)ob->query_skill("quanzhen-xinfa", 1) < 50)
	{
		command("say ��ı����ڹ��ķ�����㣬�������Ը�������书��");
		return;
	}

	if ((int)ob->query("shen") < 6000)
	{
		command("say �ҿ��㻹�Ƕ���һЩ����֮�°ɡ�\n");
		return;
	}
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
		return "�������ˣ���������Ѿ�����ȡ���ˡ�";
	add("book_count", -1);
	ob = new("/clone/book/zhangfapu");
	ob->move(this_player());
	return "�ðɣ��Ȿ��������ס����û�ȥ�ú��ж���";

}

