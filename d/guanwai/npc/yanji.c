// yanji.c

inherit NPC;

void create()
{
	set_name("�ֻ�", ({ "yan ji", "yan" }));
	set("title", "����ҽ��");
	set("gender", "����");
	set("long", "����һ��û�佭��ҽ����\n");
	set("age", 45);

	set("str", 21);
	set("int", 22);
	set("con", 24);
	set("dex", 20);
	
	set("qi", 1000);
	set("max_qi", 1000);
	set("jing", 500);
	set("max_jing", 500);
	set("shen_type", -1);

	set("combat_exp", 30000);
	set("attitude", "heroism");

	set_skill("unarmed", 30);
	set_skill("dodge", 60);
	set_skill("parry", 60);
	set_skill("blade", 60);
	set_skill("hujia-daofa", 60);
	map_skill("blade", "hujia-daofa");

	setup();
	add_money("silver", 20);
	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/gangdao")->wield();
}
