// huitong.c

inherit NPC;

void create()
{
	set_name("��ͨ��ʦ", ({"huitong chanshi","monk", "huitong","chanshi"}));
	set("long",
	"��ͨ��ʦ�Ǳ����µ����֣���ɫׯ�أ���ֹ������һ�����ǡ�\n");
	set("title", "����������");
	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");
	set("age", 69);
	set("per", 25);
	set("max_qi", 900);
	set("max_jing", 900);
	set("neili", 900);
	set("max_neili", 900);
	set("jiali", 40);
	set("max_jingli", 900);
	set("jingli", 900);
	set("combat_exp", 200000);
	set("shen_type", 1);

	set_skill("force", 90);
	set_skill("unarmed", 90);
	set_skill("dodge", 90);
	set_skill("parry", 90);
	
	setup();
	carry_object(__DIR__"obj/sengpao")->wear();
}
