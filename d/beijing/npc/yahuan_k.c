inherit NPC;

void create()
{
	set_name("����Ѿ��", ({ "ya huan", "ya", "huan"}));
	set("gender", "Ů��" );
	set("age", 12);
	set("long", "һ��ʮ�����С������ǿ���������Ѿ��\n");
	set("shen_type", 1);
	set("combat_exp", 2000);
	set("str", 17);
	set("dex", 20);
	set("con", 17);
	set("int", 22);
	set("attitude", "peaceful");
	set_skill("dodge",10);
	set_skill("unarmed",10);

	setup();
	carry_object("/d/beijing/npc/obj/nvcloth")->wear();
	add_money("silver", 3);
}

