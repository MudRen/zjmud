// chushi.c

inherit NPC;

void create()
{
	set_name("��ʦ", ({ "chu shi", "chu" }));
	set("title", "÷ׯ");
	set("long",
		"÷ׯ��һ����ʦ��Ц���еؿ����㣬�����ܺ��Ƶ����ӡ�\n");
	set("gender", "����");
	set("age", 34);
	set("attitude", "peaceful");
	set("shen_type", 1);

	set("max_qi", 200);
	set("max_jing", 50);
	set("combat_exp", 500);
	set_skill("force", 10);
	set_skill("dodge", 10);
	set_skill("cuff", 10);
	set_skill("parry", 10);

	setup();
}
