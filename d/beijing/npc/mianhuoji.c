inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("��ݻ��", ({ "mianguan huoji", "huoji" }));
	set("str", 20);
	set("gender", "����");
	set("age", 18+random(20));
	set("long", "����С��ݵĻ�ơ�\n");
	set("combat_exp", 2500);
	set("attitude", "friendly");

	setup();
	carry_object("/d/beijing/npc/obj/cloth")->wear();
}

