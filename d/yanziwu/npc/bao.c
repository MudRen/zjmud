// bao.c

#include <ansi.h>;

inherit NPC;
inherit F_GUARDER;
inherit F_COAGENT;

void create()
{
	set_name("����ͬ", ({"bao butong", "bao"}));
	set("gender", "����");
	set("age", 31);
	set("long", "����Ľ�ݼ��Ĵ�ҳ�֮��������ϲ�����ࡣ\n");
	set("attitude", "peaceful");
	set("str", 21);
	set("int", 26);
	set("con", 25);
	set("dex", 24);

	set("qi", 2900);
	set("max_qi", 2900);
	set("jing", 1500);
	set("max_jing", 1500);
	set("neili", 2900);
	set("max_neili", 2900);
	set("combat_exp", 550000);

	set_skill("force", 130);
	set_skill("shaolin-xinfa", 130);
	set_skill("dodge", 130);
	set_skill("shaolin-shenfa", 130);
	set_skill("parry", 140);
	set_skill("claw", 140);
	set_skill("longzhua-gong", 140);

	map_skill("force", "shaolin-xinfa");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "longzhua-gong");
	map_skill("claw", "longzhua-gong");

	prepare_skill("claw", "longzhua-gong");

	create_family("Ľ������", 0, "�ҳ�");

	set("inquiry", ([
		"Ľ�ݲ�":   "���������ˡ�\n",
		"Ľ�ݸ�":   "���������Ǹ���Ĺ��ӣ�\n",
	]));

	set("coagents", ({
		([ "startroom" : "/d/yanziwu/qinyun",
		   "id"	: "feng boe" ]),
		([ "startroom" : "/d/yanziwu/shangyu",
		   "id"	: "murong bo" ]),
	}));

	set("guarder", ([
		"refuse_home" : "$N��$n����������Ҳ��Ҳ����Ȼ������Ľ�ݴ��ˣ���ˡ�����������ˣ�",
		"refuse_other": "$N��$n��Ц��������Ľ�ݼҵ�ͨͨ�ĸ��ҹ���ȥ��",
	]));

	setup();

	carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
	command("say ���Ǹ���Ľ�ݹ��ӣ�����ͽ��");
	return;
}
