// daotong.c ��ͯ
// By Lgg,1998.10

inherit NPC;

void create()
{
	set_name("��ͯ", ({"tong", "dao tong"}));
	set("gender", "����");
	set("class", "taoist");
	set("age", 14);
	set("long",
		"����һλС��ͯ��������Ͳ������������̴棬����Ц����\n"
		"���������ǡ�\n" );
	set("attitude", "friendly");

	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);

	set("qi", 300);
	set("max_qi", 300);
	set("jing", 200);
	set("max_jing", 200);
	set("neili", 300);
	set("max_neili", 300);
	set("jiali", 0);

	set("combat_exp", 2000);
	create_family("ȫ���", 5, "����");

	setup();

	carry_object(__DIR__"obj/grayrobe")->wear();

}

