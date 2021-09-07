// cong-buqi.c  �Բ���
inherit NPC;
inherit F_MASTER;
#include <ansi.h>

void create()
{
	set_name("�Բ���", ({ "cong buqi", "cong" }) );
	set("gender", "����");
	set("class", "swordsman");
	set("title", "��ɽ���ڵ�ʮ��������");
	set("age", 52);
	set("long", "�Բ����ǻ�ɽ���ڸ��֡�\n");
	set("attitude", "peaceful");
	set("str", 26);
	set("int", 28);
	set("con", 25);
	set("dex", 26);

	set("max_qi", 3200);
	set("max_jing", 3200);
	set("neili", 3800);
	set("max_neili", 3800);
	set("jiali", 35);

	set("combat_exp", 920000);
	set("shen_type", -1);

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "sword.feilong" :),
		(: exert_function, "recover" :),
	}) );

	set_skill("unarmed", 80);
	set_skill("sword", 160);
	set_skill("force", 120);
	set_skill("parry", 160);
	set_skill("dodge", 160);
	set_skill("literate", 50);
	set_skill("huashan-sword", 160);
	set_skill("huashan-xinfa", 120);
	set_skill("huashan-quanfa", 80);
	set_skill("huashan-zhangfa", 80);
	set_skill("huashan-shenfa", 160);

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
	command("say �Ϸ�����ͽ��");
}
