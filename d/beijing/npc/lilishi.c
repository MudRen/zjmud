// lilishi.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;

void create()
{
	set_name("������", ({ "li lishi", "li" }));
	set("title", HIG "��ػ���ľ��"NOR"����");
	set("gender", "����");
	set("age", 45);
	set("str", 25);
	set("dex", 20);
	set("long", "����һ����İ�С����������������ˣ����ϵ�\n"
		    "�·��������ƣ������������ƣ�����ȥ������˪��\n");
	set("combat_exp", 35000);
	set("score", 5000);
	set("shen_type", 1);
	set("attitude", "peaceful");
	set_skill("unarmed", 50);
	set_skill("force", 60);
	set_skill("blade", 90);
	set_skill("dodge", 70);
	set_skill("parry", 50);
	set_skill("wuhu-duanmendao", 90);
	set_skill("yunlong-shenfa", 60);
	map_skill("blade", "wuhu-duanmendao");
	map_skill("dodge", "yunlong-shenfa");

	set("neili", 150); 
	set("max_neili", 150);
	set("jiali", 10);

	set("inquiry", ([
		"�½���" : "����ܶ����ɲ����װ���",
		"��ػ�" : "ֻҪ��Ӣ�ۺú���������������ػᡣ",
		"���帴��" : "ȥ�ײĵ�ͻش�����ϸ���ưɣ�",
		"����" : "�����£�",
		"�п�" : "�����£�",
	]));
	setup();
	carry_object("/clone/weapon/blade")->wield();
	carry_object("/d/beijing/npc/obj/cloth")->wear();
	add_money("silver", 20);
}
