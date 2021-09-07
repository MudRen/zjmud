// gongye.c

#include <ansi.h>;

inherit NPC;
inherit F_GUARDER;

void create()
{
	set_name("��ұǬ", ({"gongye qian", "gongye"}));
	set("gender", "����");
	set("age", 35);
	set("long", "����Ľ�ݼ��Ĵ�ҳ�֮����Ϊ�����ء�\n");
	set("attitude", "peaceful");
	set("str", 27);
	set("int", 24);
	set("con", 26);
	set("dex", 24);

	set("qi", 3200);
	set("max_qi", 3200);
	set("jing", 1600);
	set("max_jing", 1600);
	set("neili", 3400);
	set("max_neili", 3400);
	set("combat_exp", 620000);

	set_skill("force", 150);
	set_skill("hunyuan-yiqi", 150);
	set_skill("sword", 155);
	set_skill("fumo-jian", 155);
	set_skill("dodge", 140);
	set_skill("shaolin-shenfa", 140);
	set_skill("parry", 150);
	set_skill("hand", 140);
	set_skill("fengyun-shou", 140);

	map_skill("force", "hunyuan-yiqi");
	map_skill("sword", "fumo-jian");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "fumo-jian");
	map_skill("hand", "fengyun-shou");

	prepare_skill("hand", "fengyun-shou");

	create_family("Ľ������", 0, "�ҳ�");

	set("coagents", ({
		([ "startroom" : "/d/yanziwu/qinyun",
		   "id"	: "bao butong" ]),
		([ "startroom" : "/d/yanziwu/canheju",
		   "id"	: "murong fu" ]),
	}));

	set("inquiry", ([
		"Ľ�ݲ�":   "���������ˡ�\n",
		"Ľ�ݸ�":   "���������Ǹ���Ĺ��ӣ�\n",
	]));

	set("guarder", ([
		"refuse_home" : "$N��$n��Ȼ��������Ľ�ݣ����������ٻ����ˣ�",
		"refuse_other": "$N��$n����Ľ�ݼҲ�����ͣ�����ذɣ�",
	]));

	set("coagents", ({
		([ "startroom" : "/d/yanziwu/shangyu",
		   "id"	: "murong bo" ]),
	}));

	setup();

	carry_object("/clone/cloth/cloth")->wear();
	carry_object("/clone/weapon/gangjian")->wield();
}

void attempt_apprentice(object ob)
{
	command("say ���Ǹ���Ľ�ݹ��ӣ�����ͽ��");
	return;
}
