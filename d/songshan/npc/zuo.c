// zuo.c
inherit NPC;

#include <ansi.h>

void create()
{
	set_name("������", ({ "zuo lengchan", "zuo" }) );
	set("title", HIR"������������"HIY"��ɽ�ɵ�ʮ������"NOR);
	set("gender", "����");
	set("class", "swordsman");
	set("age", 55);
	set("attitude", "peaceful");
	set("str", 26);
	set("con", 30);
	set("dex", 30);
	set("int", 28);

	set("max_qi",4500);
	set("max_jing",2200);
	set("neili", 4800);
	set("max_neili", 4800);
	set("jiali", 80);
	set("combat_exp", 1850000);
	set("shen_type", -1);

	set_skill("sword", 210);
	set_skill("force", 220);
	set_skill("parry", 180);
	set_skill("dodge", 180);
	set_skill("strike", 200);
	set_skill("songshan-xinfa", 220);
	set_skill("songshan-sword", 210);
	set_skill("lingxu-bu", 180);
	set_skill("hanbing-mianzhang", 200);

	map_skill("force", "songshan-xinfa");
	map_skill("sword", "songshan-sword");
	map_skill("parry", "songshan-sword");
	map_skill("strike", "hanbing-mianzhang");
	map_skill("dodge", "lingxu-bu");

	prepare_skill("strike", "hanbing-mianzhang");

	create_family("��ɽ��", 13, "����");
	setup();

	carry_object("/clone/weapon/changjian")->wield();
	carry_object("/clone/cloth/cloth")->wear();
}
