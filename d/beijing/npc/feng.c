//feng.c

inherit NPC;

#include <ansi.h>

void create()
{
	set_name("������", ({ "feng xifan", "feng" }) );
	set("title", "�����ɸ���");
	set("nickname", HIR"һ����Ѫ"NOR);
	set("gender", "����");
	set("age", 45);
	set("long",
		"����������ƽ�������ӳ��������ɸ��֣�һ�Ű�տտ����Ƥ��\n"
		"̨��ս�ܺ�齵��͢������Ϊһ���ҳ�����");
	set("attitude", "peaceful");
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 28);

	set("neili", 2400);
	set("max_neili", 2400);
	set("jiali", 30);
	set("max_qi",2000);
	set("max_jing",1200);

	set("shen_type", -1);
	set("combat_exp", 1000000);

	set_skill("unarmed", 180);
	set_skill("sword", 160);
	set_skill("force", 160);
	set_skill("parry", 160);
	set_skill("dodge", 160);
	set_skill("literate", 100);
	set_skill("huashan-sword", 180);
	set_skill("kuangfeng-jian", 180);
	set_skill("huashan-xinfa", 160);
	set_skill("huashan-quanfa", 170);
	set_skill("huashan-zhangfa", 170);
	set_skill("huashan-shenfa", 170);

	map_skill("sword", "kuangfeng-jian");
	map_skill("parry", "kuangfeng-jian");
	map_skill("force", "huashan-neigong");
	map_skill("unarmed", "huashan-zhangfa");
	map_skill("dodge", "huashan-shenfa");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/d/beijing/npc/obj/guanfu5")->wear();
}
