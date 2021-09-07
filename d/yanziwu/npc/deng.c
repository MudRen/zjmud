// deng.c

#include <ansi.h>;

inherit NPC;
inherit F_GUARDER;

void create()
{
	set_name("�˰ٴ�", ({"deng baichuan", "deng"}));
	set("gender", "����");
	set("age", 42);
	set("long", "����Ľ�ݼ��Ĵ�ҳ�֮�ף�������Ϊ���\n");
	set("attitude", "peaceful");
	set("str", 26);
	set("int", 22);
	set("con", 25);
	set("dex", 22);

	set("qi", 3600);
	set("max_qi", 3600);
	set("jing", 1800);
	set("max_jing", 1800);
	set("neili", 3800);
	set("max_neili", 3800);
	set("combat_exp", 750000);

	set_skill("force", 175);
	set_skill("hunyuan-yiqi", 175);
	set_skill("dodge", 130);
	set_skill("shaolin-shenfa", 130);
	set_skill("parry", 140);
	set_skill("cuff", 175);
	set_skill("jingang-quan", 175);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "jingang-quan");
	map_skill("cuff", "jingang-quan");

	prepare_skill("cuff", "jingang-quan");

	create_family("Ľ������", 0, "�ҳ�");

	set("inquiry", ([
		"Ľ�ݲ�":   "���������ˡ�\n",
		"Ľ�ݸ�":   "���������Ǹ���Ĺ��ӣ�\n",
	]));

	set("guarder", ([
		"refuse_other": "$N��$n�������Ľ�ݼ��ˣ����ܹ�ȥ��ʧ���ˣ�",
	]));

	set("coagents", ({
		([ "startroom" : "/d/yanziwu/shangyu",
		   "id"	: "murong bo" ]),
	}));

	setup();

	carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
	command("say ���Ǹ���Ľ�ݹ��ӣ�����ͽ��");
	return;
}
