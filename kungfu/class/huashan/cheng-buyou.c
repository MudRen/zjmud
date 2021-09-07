// cheng-buyou.c  �ɲ���
inherit NPC;
inherit F_MASTER;
#include <ansi.h>

void create()
{
	set_name("�ɲ���", ({ "cheng buyou", "cheng" }) );
	set("gender", "����");
	set("class", "swordsman");
	set("title", "��ɽ���ڵ�ʮ��������");
	set("age", 41);
	set("long",
		"һ���׾���Ƥ�İ��ӣ���Ҳ����С������\n");
	set("attitude", "peaceful");
	set("str", 26);
	set("int", 24);
	set("con", 23);
	set("dex", 27);

	set("max_qi", 2800);
	set("max_jing",1400);
	set("neili", 3600);
	set("max_neili", 3600);
	set("jiali", 45);

	set("combat_exp", 850000);
	set("shen_type", -1);
	set("apprentice_available", 3);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "sword.feilong" :),
		(: exert_function, "recover" :),
	}) );

	set_skill("unarmed", 80);
	set_skill("sword", 150);
	set_skill("force", 100);
	set_skill("parry", 130);
	set_skill("dodge", 130);
	set_skill("literate", 50);
	set_skill("huashan-sword", 150);
	set_skill("huashan-xinfa", 100);
	set_skill("huashan-quanfa", 80);
	set_skill("huashan-shenfa", 130);

	map_skill("sword", "huashan-sword");
	map_skill("parry", "huashan-sword");
	map_skill("force", "huashan-neigong");
	map_skill("unarmed", "huashan-quanfa");
	map_skill("dodge", "huashan-shenfa");

	create_family("��ɽ����", 13, "����");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
	command("say �Ϸ�Ӳ���ͽ�������ҷ�ʦ�ֺ��ˡ�");
}
