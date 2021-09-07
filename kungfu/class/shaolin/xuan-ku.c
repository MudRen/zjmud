// Npc: /kungfu/class/shaolin/xuan-ku.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_me();

#include "xuan-ku.h"

void create()
{
	set_name("�����ʦ", ({
		"xuanku dashi",
		"xuanku",
		"dashi",
	}));
	set("long",
		"����һλ�����ü����ɮ����һϮ��˿�ػ����ġ�������ݸߣ�\n"
		"�����������ƣ��ֱ۴������¶���ƺ��þ���˪��\n"
	);


	set("nickname", "�޺�������");
	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 70);
	set("shen_type", 1);
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("max_qi", 2400);
	set("max_jing", 1000);
	set("neili", 3200);
	set("max_neili", 3200);
	set("jiali", 50);
	set("combat_exp", 1050000);

	set_skill("force", 120);
	set_skill("hunyuan-yiqi", 120);
	set_skill("shaolin-xinfa", 120);
	set_skill("dodge", 120);
	set_skill("shaolin-shenfa", 120);
	set_skill("parry", 120);
	set_skill("cuff", 120);
	set_skill("staff", 120);
	set_skill("blade", 120);
	set_skill("sword", 120);
	set_skill("luohan-quan", 120);
	set_skill("weituo-gun", 120);
	set_skill("xiuluo-dao", 120);
	set_skill("fumo-jian", 120);
	set_skill("buddhism", 120);
	set_skill("literate", 120);
	set_skill("medical", 180);
	set_skill("shaolin-yishu", 180);

	map_skill("force", "hunyuan-yiqi");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("parry", "luohan-quan");
	map_skill("cuff", "luohan-quan");
	map_skill("staff", "weituo-gun");
	map_skill("blade", "xiuluo-dao");
	map_skill("sword", "fumo-jian");

	prepare_skill("cuff", "luohan-quan");

	create_family("������", 36, "����");

	set("inquiry", ([
		"ʮ���޺���"       : (: ask_me :),
		"�޺�����"	   : (: ask_me :)
	]));

	setup();

	carry_object("/d/shaolin/obj/jiedao")->wield();
	carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

