#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("�쵤��", ({ "zhu danchen", "zhu", "danchen" }));
	set("title", "���������" );
	set("nickname", CYN "������" NOR);
	set("long", "���Ǵ�����Ĵ���֮һ��һ������������Ĵ����ͷ��\n");
	set("gender", "����");
	set("age", 40);
	set("class", "officer");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 30);
	set("int", 20);
	set("con", 25);
	set("dex", 25);
	
	set("max_qi", 1800);
	set("max_jing", 1000);
	set("neili", 2200);
	set("max_neili", 2200);
	set("jiali", 50);
	set("combat_exp", 500000);
	set("score", 5000);

	set_skill("force", 120);
	set_skill("duanshi-xinfa", 120);
	set_skill("dodge", 120);
	set_skill("tiannan-step", 120);
	set_skill("cuff", 120);
	set_skill("jinyu-quan", 120);
	set_skill("strike", 120);
	set_skill("wuluo-zhang", 120);
	set_skill("dagger", 140);
	set_skill("qingliang-daxuefa", 140);
	set_skill("parry", 120);
	set_skill("literate", 280);
	set_skill("martial-cognize", 140);

	map_skill("force", "duanshi-xinfa");
	map_skill("dodge", "tiannan-step");
	map_skill("cuff", "jinyu-quan");
	map_skill("strike", "wuluo-zhang");
	map_skill("dagger", "qingliang-daxuefa");
	map_skill("parry", "qingliang-daxuefa");

	prepare_skill("cuff", "jinyu-quan");
	prepare_skill("strike", "wuluo-zhang");

	create_family("���ϻ���", 15, "�ҳ�");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "dagger.ding" :),
		(: perform_action, "cuff.man" :),
		(: perform_action, "strike.bian" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/d/dali/npc/obj/junfu")->wear();
	carry_object("/d/meizhuang/obj/panguanbi")->wield();
	add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	command("smile");
	command("say ���ӵ��º�����ˣ�ֻҪ���·Ը�����һ�����ǡ�");
	command("say �����Ӳ������������ﵹ����һ�ױʷ����Դ������㡣");

	return;
}

int recognize_apprentice(object ob, string skill)
{
	if (ob->query("family/family_name") != "���ϻ���")
	{
		command("sneer");
		command("say ��������ز���ʶ����֪���´˻��Ӻ�˵��");
		return -1;
	}

	if (skill != "qingliang-daxuefa" && skill != "dagger")
	{
		command("say ��ĳ��ƽֻ�Աʷ�һ�������о�������������֪��ǳ��");
		return -1;
	}

	if (! ob->query_temp("can_learn/zhudanchen"))
	{
		command("hehe");
		command("say ��Ȼ��������ϰ�䣬�������߾����ܴ��ڡ�");
		ob->set_temp("can_learn/zhudanchen", 1);
	}
	return 1;
}

