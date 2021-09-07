// suxingh.c
// shilling 97.2

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_GUARDER;
inherit F_QUESTER;

#include "xiaoyao.h"

string ask_me();
string ask_book();

void create()
{
	set_name("���Ǻ�",({"su xinghe","su"}));
	set("gender", "����" );
	set("nickname", "�ϱ�����");
	set("shen_type", 0);
	set("class", "scholar");
	set("age",60);

	set("str", 29);
	set("con", 30);
	set("int", 45);
	set("dex", 37);

	set("long", @LONG
���˾��Ǻųƴϱ����˵����Ǻӣ���˵�������Ʊ磬��һ�������е�
���ߣ��������书Ҳ��������֪��
LONG );

	set("combat_exp", 1100000);
	set("attitude", "peaceful");
	set("book_count", 1);
	set("chat_chance", 1);

	set("max_qi", 4400);
	set("max_jing", 2400);
	set("neili", 5500);
	set("max_neili", 5500);
	set("jiali", 60);
	set("env/wimpy", 60);

	set_skill("force", 150);
	set_skill("dodge", 150);
	set_skill("strike", 140);
	set_skill("hand", 140);
	set_skill("parry", 150);
	set_skill("blade", 130);
	set_skill("feiyan-zoubi", 150);
	set_skill("xiaoyao-xinfa", 150);
	set_skill("ruyi-dao", 140);
	set_skill("liuyang-zhang", 140);
	set_skill("zhemei-shou", 140);
	set_skill("literate", 160);
	set_skill("medical", 250);
	set_skill("xiaoyao-qixue", 250);

	map_skill("strike", "liuyang-zhang");
	map_skill("hand", "zhemei-shou");
	map_skill("blade", "ruyi-dao");
	map_skill("dodge", "feiyan-zoubi");
	map_skill("force", "xiaoyao-xinfa");

	prepare_skill("hand","zhemei-shou");
	prepare_skill("strike","liuyang-zhang");	

	create_family("��ң��", 2, "����");
	set("title", "��ң�ɵڶ������ŵ���");

	set("coagents", ({
	       ([ "startroom" : "/d/xiaoyao/shishi",
		  "id"	: "xiaoyao zi" ]),
	}));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "blade.ruyi" :),
		(: perform_action, "hand.jiubu" :),
		(: perform_action, "strike.jiutian" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}));

	set_temp("apply/force", 100);
	set_temp("apply/dodge", 100);
	set_temp("apply/parry", 100);
	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();
	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/blade")->wield();
}


void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if (ob->query_int() < 30)
	{
		command("shake"+ ob->query("id")); 
		command("say " + RANK_D->query_respect(ob) + 
			"�Ƿ�Ӧ����ѧ���϶��µ㹦�򣬱��˿���ң���ˣ�");
		return;
	}

	if (ob->query_skill("force", 1) < 50)
	{
		command("sigh");
		command("say ������ң�ɵ��书��Ҫ���ڹ�Ϊ���������Ȱ�"
			"�����ڹ�ѧ��ʵ�ɡ�");
		return;
	}

	if (ob->query_skill("xiaoyao-xinfa", 1) < 50)
	{
		command("sigh");
		command("say �������ŵ������ķ���û��ѧ�ã�����ѧ����"
			"���ϳ���ѧ��");
		return;
	}

	command("say �ðɣ��Ҿ��������ˣ����Ҫ���Ŭ������");
	command("recruit " + ob->query("id"));
}

int permit_pass(object me, string dir)
{
	if (! ::permit_pass(me, dir))
		return 0;

	if (me->query("family/master_id") == "xiaoyao zi")
		return 1;

	if (me->query("combat_exp") < 250000)
	{
		command("say ���������ֲ�Ҫȥ����ú�ѧ������ң���书��");
		return 0;
	}

	if (me->query_skill("xiaoyao-xinfa", 1) < 120)
	{
		command("say ��������ң�ķ���ѧ���ã�����ʲô��");
		return 0;
	}

	command("sigh");
	command("say ȥ�ɣ�ȥ�ɣ���Ե�߾��ɡ�");
	return 1;
}

int accept_hit(object who)
{
	command("heng");
	command("say " + who->name() + "���������̫����");
	return 0;
}

void unconcious()
{
	die();
}
