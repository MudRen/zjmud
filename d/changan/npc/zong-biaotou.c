//zong-biaotou.c

inherit NPC;
#include <ansi.h>

void create()
{
	set_name("����ɽ", ({ "wan", "qingshan" }) );
	set("title", HIR "��������" NOR);
	set("gender", "����" );
	set("age", 45);
	set("int", 30);
	set("skill_public",1);
	set("long",
		"�����ھ�����ͷ��Ϊ�˺�ˬ�������߽��������ﶼ��������̵��书��\n"
	);
	set("chat_chance", 10);
	set("chat_msg", ({
		"����ɽ˵�����ھֵ�����Խ��Խ���ˣ�\n",
		"����ɽ˵������������һ����Σ�յ��£�\n",
	}) );
	set("attitude", "peaceful");
	set_skill("unarmed", 40);
	set_skill("literate", 40);
	set_skill("force", 40);
	set_skill("dodge",40);
	set_skill("parry",40);
	set("combat_exp", 100000);
	setup();
	carry_object(__DIR__"obj/jinzhuang")->wear();
}

int recognize_apprentice(object ob)
{
	return 1;
}
