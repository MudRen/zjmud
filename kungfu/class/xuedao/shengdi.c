// /kungfu/class/xueshan/shengdi.c  ʤ��
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>
#include "xuedao.h"

void create()
{
	set_name("ʤ��", ({ "sheng di", "sheng", "di" }));
	set("long",@LONG
����һ�����ο��������ɮ�ˣ���ɫ��Į���书��ͬ������ߵ�һ�ˡ�
LONG
	);
	set("title",HIR"Ѫ���ŵ��������"NOR);
	set("gender", "����");
	set("age", 35);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 28);
	set("int", 25);
	set("con", 28);
	set("dex", 24);

	set("max_qi", 5000);
	set("max_jing", 2500);
	set("neili", 4500);
	set("max_neili", 4500);
	set("jiali", 55);
	set("combat_exp", 640000);

	set_skill("lamaism", 140);
	set_skill("literate", 100);
	set_skill("force", 160);
	set_skill("mizong-neigong", 160);
	set_skill("parry", 140);
	set_skill("blade", 145);
	set_skill("xue-dao", 125);
	set_skill("dodge", 130);
	set_skill("shenkong-xing", 130);
	set_skill("hand", 110);
	set_skill("dashou-yin", 110);
	set_skill("cuff", 140);
	set_skill("yujiamu-quan", 140);

	map_skill("force", "mizong-neigong");
	map_skill("dodge", "shenkong-xing");
	map_skill("hand", "dashou-yin");
	map_skill("cuff", "yujiamu-quan");
	map_skill("parry", "xue-dao");
	map_skill("blade", "xue-dao");

	prepare_skill("cuff", "yujiamu-quan");
	prepare_skill("hand", "dashou-yin");

	create_family("Ѫ����", 5, "����");
	set("class", "bonze");

	set("coagents", ({
		([ "id" : "xuedao laozu",
		   "startroom" : "/d/xuedao/shandong3" ]),
	}));

	setup();
	carry_object("/d/xueshan/obj/y-jiasha")->wear();
	carry_object("/clone/weapon/gangdao")->wield();

	add_money("silver", 5);
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if (ob->query("class") != "bonze")
	{
		ob->set_temp("pending/join_bonze", 1);
		command("say �㲻�ǳ����ˣ�����Ѫ�����ǲ��������ġ�"
			"�����Ҫ���ң���������ʦֶ��");
		return;
	}

	if ((string)ob->query("gender") != "����")
	{
		command("say �Ҳ���Ůͽ�ܡ�\n");
		return;
	}

	if (ob->query("shen") > -5000)
	{
		command("say �����һ�Ҫ�Ƚ�������ĺ�ɱ�ˡ�\n");
		return;
	}

	if ((int)ob->query_skill("lamaism", 1) < 50)
	{
		command("say ����Ѫ���ţ���ϰ���ڷ�����Ҫ�ġ�\n");
		return;
	}

	if ((int)ob->query_skill("force") < 90)
	{
		command("say �������������ô���Ȱ��ڹ����ã�\n");
		return;
	}

	command("recruit " + ob->query("id"));
}
