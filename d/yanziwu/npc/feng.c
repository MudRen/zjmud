// feng.c

#include <ansi.h>;

inherit NPC;
inherit F_GUARDER;
inherit F_COAGENT;

void create()
{
	set_name("�粨��", ({"feng boe", "feng"}));
	set("gender", "����");
	set("age", 28);
	set("long", "����Ľ�ݼ��Ĵ�ҳ�֮�ģ���ϲ����ܣ�����ȴ�����䡣\n");
	set("attitude", "peaceful");
	set("str", 24);
	set("int", 21);
	set("con", 24);
	set("dex", 28);

	set("qi", 2700);
	set("max_qi", 2700);
	set("jing", 1400);
	set("max_jing", 1400);
	set("neili", 2800);
	set("max_neili", 2800);
	set("combat_exp", 480000);

	set_skill("force", 125);
	set_skill("shaolin-xinfa", 125);
	set_skill("blade", 145);
	set_skill("xiuluo-dao", 145);
	set_skill("dodge", 140);
	set_skill("shaolin-shenfa", 140);
	set_skill("parry", 130);
	set_skill("cuff", 100);
	set_skill("jingang-quan", 100);

	map_skill("force", "shaolin-xinfa");
	map_skill("blade", "xiuluo-dao");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "xiuluo-dao");
	map_skill("cuff", "jingang-quan");

	prepare_skill("cuff", "jingang-quan");

	create_family("Ľ������", 0, "�ҳ�");

	set("inquiry", ([
		"Ľ�ݲ�":   "���������ˡ�\n",
		"Ľ�ݸ�":   "���������Ǹ���Ĺ��ӣ�\n",
	]));

	set("guarder", ([
		"refuse_other": "$N��$n�µ������ȥ��Ҫ���������ҵĵ�����Ӧ���������Ⱥ��Ҵ������ٻغ���˵��",
	]));

	set("coagents", ({
		([ "startroom" : "/d/yanziwu/qinyun",
		   "id"	: "bao butong" ]),
		([ "startroom" : "/d/yanziwu/shangyu",
		   "id"	: "murong bo" ]),
	}));

	setup();

	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/gangdao")->wield();
}

void attempt_apprentice(object ob)
{
	command("say ���Ǹ���Ľ�ݹ��ӣ�����ͽ��");
	return;
}
