// qibiaoqing.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;

void create()
{
	set_name("�����", ({ "qi biaoqing", "qi" }));
	set("title", HIR "��ػ�"HIG"��ľ��"NOR"����"); 
	set("shen_type", 1);
	set("gender", "����");
	set("age", 35);
	set("long", "һ��Ƣ���𱩵�׳����\n");

	set_skill("unarmed", 60);
	set_skill("dodge", 70);
	set_skill("parry", 70);
	set_skill("sword", 80);
	set_skill("force", 70);
	set_skill("huashan-xinfa", 50);
	set_skill("huashan-sword", 70);
	set_skill("huashan-shenfa",60);
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