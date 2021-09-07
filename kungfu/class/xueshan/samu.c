// /kungfu/class/xueshan/samu.c  ��ľ���
// by secret

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "xueshan.h"

void create()
{
	set_name("��ľ���", ({ "samu huofo", "huofo", "samu" }));
	set("long",@LONG
��ľ�����ѩɽ���е��ĸ�ɮ���Է��о�����о���
����һ����ɫ���ģ�ͷ��ɮñ��һ��������˼�����ӡ�
LONG
	);
	set("title", HIY "���" NOR);
	set("gender", "����");
	set("age", 45);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 22);
	set("int", 25);
	set("con", 24);
	set("dex", 21);

	set("max_qi", 2000); 
	set("max_jing", 1000); 
	set("neili", 2500); 
	set("max_neili", 2500); 
	set("jiali", 30); 
	set("combat_exp", 220000);

	set_skill("lamaism", 120);
	set_skill("literate", 80);
	set_skill("force", 120);
	set_skill("mizong-neigong", 100);
	set_skill("dodge", 120);
	set_skill("shenkong-xing", 100);
	set_skill("hand", 120);
	set_skill("dashou-yin", 100);
	set_skill("parry", 120);
	set_skill("sword", 100);
	set_skill("mingwang-jian", 100);

	map_skill("force", "mizong-neigong");
	map_skill("dodge", "shenkong-xing");
	map_skill("hand",  "dashou-yin");
	map_skill("parry", "mingwang-jian");
	map_skill("sword", "mingwang-jian");

	prepare_skill("hand",  "dashou-yin");

	create_family("ѩɽ��", 3, "���");
	set("class", "bonze");

	setup();

	carry_object("/d/city/obj/changjian")->wield();
	carry_object("/d/xueshan/obj/y-jiasha")->wear();
	carry_object("/d/xueshan/obj/sengmao")->wear();
	add_money("silver", 80);
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((string)ob->query("gender") != "����")
	{
		command("say ��ϰ�����ڹ���Ҫ����֮�塣");
		command("say ��λ" + RANK_D->query_respect(ob) +
			"������ذɣ�");
		return;
	}

	if ((string)ob->query("class") != "bonze")
	{
		command("say �ҷ��ŵ����������ࡣ");
		command("say ��λ" + RANK_D->query_respect(ob) +
			"������ذɣ�");
		return;
	}

	if ((string)ob->query("family/family_name") != "ѩɽ��")
	{
		command("say ��λ" + RANK_D->query_respect(ob) +
			"�ȷǱ��µ��ӣ�������ذɣ�");
		return;
	}

	if ((int)ob->query_skill("lamaism", 1) < 60)
	{
		command("say ����ѩɽ�£���ϰ�����ķ�����Ҫ�ġ�");
		command("say ��λ" + RANK_D->query_respect(ob) +
			"�Ƿ�Ӧ�ö�����б��ŵ��ķ���");
		return;
	}

	command("smile");
	command("nod");
	command("say �������ѧϰ�𷨰ɣ�");
	command("recruit " + ob->query("id"));

	ob->set("title", HIY"������"NOR);
}
