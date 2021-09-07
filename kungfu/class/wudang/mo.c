#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("Ī����", ({ "mo shenggu", "mo" }));
	set("nickname", "�䵱����");
	set("long", 
		"��������������ߵ���Ī���ȡ�\n"
		"����������ʮ���꣬�Ե�����δ�ѡ�\n"
		"��Ҳ�ǽ������������壬����Զ�������͡�\n");
	set("gender", "����");
	set("age", 40);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 24);
	set("int", 27);
	set("con", 25);
	set("dex", 22);
	
	set("max_qi", 3600);
	set("max_jing", 1800);
	set("neili", 4000);
	set("max_neili", 4000);
	set("jiali", 60);
	set("combat_exp", 850000);
	set("score", 300000);

	set_skill("force", 150);
	set_skill("wudang-xinfa", 150);
	set_skill("taiji-shengong", 150);
	set_skill("dodge", 150);
	set_skill("tiyunzong", 150);
	set_skill("unarmed", 135);
	set_skill("taiji-quan", 135);
	set_skill("strike", 150);
	set_skill("zhenshan-zhang", 150);
	set_skill("hand", 100);
	set_skill("paiyun-shou", 100);
	set_skill("wudang-zhang", 125);
	set_skill("parry", 140);
	set_skill("sword", 130);
	set_skill("wudang-jian", 130);
	set_skill("taiji-jian", 130);
	set_skill("taoism", 70);
	set_skill("literate", 80);

	map_skill("force", "taiji-shengong");
	map_skill("dodge", "tiyunzong");
	map_skill("unarmed", "taiji-quan");
	map_skill("parry", "taiji-jian");
	map_skill("sword", "taiji-jian");
	map_skill("strike", "zhenshan-zhang");
	map_skill("hand", "paiyun-shou");

	prepare_skill("unarmed", "taiji-quan");

	set("no_teach", ([
		"taiji-shengong" : "Ҫ��ѧϰ̫����������������̡�",
		"taiji-jian"     : "̫���������������״���",
		"taiji-quan"     : "̫��ȭ�����������״���",
	]));

	create_family("�䵱��", 2, "����");

	set("chat_chance_combat", 30);
	set("chat_msg_combat", ({
		(: perform_action, "sword.chan" :),
		(: perform_action, "sword.lian" :),
		(: perform_action, "sword.sui" :),
		(: exert_function, "recover" :),
	}) );

	setup();
	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/wudang/obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query("shen") < 2000 )
	{
		command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
		command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
			"�Ƿ����ò�����");
		return;
	}

	if ((int)ob->query_skill("wudang-xinfa", 1) < 50)
	{
		command("say ���䵱����ע���ڹ��ķ�" + RANK_D->query_respect(ob)+
			"�Ƿ�Ӧ�����䵱�ķ��϶��µ㹦��?");
		return;
	}

	if ((int)ob->query_skill("taoism", 1) < 50)
	{
		command("say ϰ����Ϊ��ǿ���壬һζ�������ǲ���ȡ������");
		command("say �ҿ��㻹��Ҫ���������Է��������������������"
			"�ĵ����ķ���");
		return;
	}

	command("say �ðɣ��Ҿ��������ˡ�");
	command("say ϣ�����ܺú��ù����������䵱����!");
	command("recruit " + ob->query("id"));
	if ((string)ob->query("class") != "taoist")
		ob->set("class", "taoist");
}
