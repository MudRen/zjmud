// diyun ����

inherit NPC;

void create()
{
	set_name("����", ({ "di yun", "diyun"}));
	set("long", "��Ӣ���������һ�ɺ���֮����\n");
	set("gender", "����");
	set("age", 25);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("per", 20);

	setup();
	carry_object("/d/city/obj/cloth.c")->wear();
}
