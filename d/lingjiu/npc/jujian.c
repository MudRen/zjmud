// /NPC jujian.c

#include <ansi.h>

inherit NPC;
inherit F_GUARDER;

void create()
{
	set_name("�ս�", ({ "ju jian", "ju"}));
	set("long",
	    "���Ǹ���ò毺õ�Ů�ӣ�����������������ᣬ������ס�\n");
	set("gender", "Ů��");
	set("age", 18);
	set("shen_type",1);
	set("attitude", "peaceful");

	set("str", 21);
	set("int", 24);
	set("con", 23);
	set("dex", 26);

	set("qi", 2800);
	set("max_qi", 2800);
	set("jing", 1400);
	set("max_jing", 1400);
	set("neili", 3400);
	set("max_neili", 3400);
	set("jiali", 35);

	set("combat_exp", 460000);
	set("score", 3000);
	set_skill("force", 155);
	set_skill("dodge", 140);
	set_skill("parry", 140);
	set_skill("hand", 140);
	set_skill("strike", 140);
	set_skill("sword", 140);

	set_skill("zhemei-shou", 140);
	set_skill("liuyang-zhang", 140);
 	set_skill("tianyu-qijian", 140);
	set_skill("yueying-wubu", 140);
	set_skill("lingjiu-xinfa", 155);

	map_skill("force", "lingjiu-xinfa");
	map_skill("strike","liuyang-zhang");
	map_skill("dodge", "yueying-wubu");
	map_skill("hand", "zhemei-shou");
	map_skill("parry", "liuyang-zhang");
	map_skill("sword", "tianyu-qijian");

	prepare_skill("hand", "zhemei-shou");
	prepare_skill("strike","liuyang-zhang");

	set("coagents", ({
		([ "startroom" : "/d/lingjiu/dating",
		   "id"	: "xu zhu" ]),
	}));

	create_family("���չ�",3,"����");
	setup();
	carry_object("/d/lingjiu/obj/qingyi")->wear();
	carry_object("/d/lingjiu/obj/doupeng")->wear();
	carry_object("/clone/weapon/changjian")->wield();
	add_money("silver",15);
}
