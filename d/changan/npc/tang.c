//tang.c

inherit NPC;

void create()
{
	set_name("������", ({ "tang" }));
	set("gender", "����" );
	set("age", 24);
	set("long", "һλѵ�����ص������֡�\n");
	set("combat_exp", 40000);
	set("attitude", "friendly");
	set_skill("unarmed", 80);
	set_skill("dodge", 100);

	setup();
	add_money("silver", 10);
	carry_object(__DIR__"obj/jinzhuang")->wear();
}
