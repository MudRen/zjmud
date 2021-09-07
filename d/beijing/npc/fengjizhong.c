// fengjizhong.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;

void create()
{
	set_name("�����", ({ "feng jizhong", "feng" }));
	set("title", HIR "��ػ�"HIG"��ľ��"NOR"����"); 
	set("shen_type", -1);
	set("gender", "����");
	set("age", 35);
	set("long",
		"\nһ����ʵ�ͽ�������ũ������ȴ���һ������ա�\n");

	set_skill("unarmed", 100);
	set_skill("dodge", 100);
	set_skill("parry", 120);
	set_skill("sword", 100);
	set_skill("force", 120);
	set_skill("huashan-xinfa", 120);
	set_skill("huashan-sword", 100);
	set_skill("huashan-shenfa", 100);
	map_skill("dodge", "huashan-shenfa");
	map_skill("parry", "huashan-sword");
	map_skill("sword", "huashan-sword");
	map_skill("force", "huashan-xinfa");

	set_temp("apply/attack", 35);
	set_temp("apply/attack", 35);
	set_temp("apply/damage", 25);

	set("combat_exp", 50000);
	set("attitude", "friendly");

	set("inquiry", ([
		"�½���" : "����ܶ����ɲ����װ���",
		"��ػ�" : "ֻҪ��Ӣ�ۺú���������������ػᡣ",
		"���帴��" : "ȥ�ײĵ�ͻش�����ϸ���ưɣ�",
		"����" : "�����£�",
		"�п�" : "�����£�",
	]));

	setup();
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}
