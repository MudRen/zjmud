//yahuan.c

inherit NPC;

void create()
{
	set_name("Ѿ��", ({"yahuan"}));
	set("long","һ��СѾ�������ڴ�ɨ���䣮\n");
	set("gender", "Ů��");
	set("age", 16);
	set("attitude", "friendly");
	set("shen_type", 1);
	set("combat_exp", 500);

	setup();
	carry_object(__DIR__"obj/skirt")->wear();
}
