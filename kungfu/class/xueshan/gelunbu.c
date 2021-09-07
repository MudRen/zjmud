// /kungfu/class/xueshan/gelunbu.c  ���ײ�
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>
#include "xueshan.h"

void create()
{
	set_name("���ײ�", ({ "ge lunbu", "ge" }));
	set("long",@LONG
���ײ���ѩɽ���л���ɮ����ͷ�졣ͬʱ���µ��Ӵ����书��
��һ����ɫ���ģ�ͷ��ɮñ��
LONG
	);
	set("title", HIY "����" NOR);
	set("nickname", HIG "ɮ��ͷ��" NOR);
	set("gender", "����");
	set("age", 30);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 30);
	set("int", 20);
	set("con", 28);
	set("dex", 25);

	set("max_qi", 1400);
	set("max_jing", 700);
	set("neili", 1900);
	set("max_neili", 1900);
	set("jiali", 20);
	set("combat_exp", 50000);
	set("score", 40000);

	set_skill("lamaism", 50);
	set_skill("literate", 30);
	set_skill("force", 80);
	set_skill("mizong-neigong", 80);
	set_skill("dodge", 75);
	set_skill("shenkong-xing", 70);
	set_skill("parry", 60);
	set_skill("staff", 80);
	set_skill("xiangmo-chu", 70 );
	set_skill("hand", 60);
	set_skill("dashou-yin", 60);
	set_skill("sword", 60);
	set_skill("mingwang-jian", 60);

	map_skill("force", "mizong-neigong");
	map_skill("dodge", "shenkong-xing");
	map_skill("parry", "xiangmo-chu");
	map_skill("staff", "xiangmo-chu");
	map_skill("sword", "mingwang-jian");
	map_skill("hand",  "dashou-yin");

	prepare_skill("hand",  "dashou-yin");

	create_family("ѩɽ��", 5, "����");
	set("class", "bonze");

	set("coagents", ({
		([ "startroom" : "/d/xueshan/dating",
		   "id"	: "jinlun fawang", ]),
	}));

	setup();

	carry_object("/d/xueshan/obj/b-jiasha")->wear();
	carry_object("/d/xueshan/obj/sengmao")->wear();
	carry_object("/d/xueshan/obj/senggun")->wield();

	add_money("silver", 10);
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

	command("say �Ҿʹ���һЩ�书�ɣ�");
	command("recruit " + ob->query("id"));

	if ((string)ob->query("class") != "bonze")
	{
		ob->set("title", "ѩɽ���׼ҵ���");
	} else
	{
		ob->set("title", YEL "С����" NOR);
	}
}

