//biaotou.c

inherit NPC;

void create()
{
	string *surname=({"��","Ǯ","��","��","��","��","֣","��",});
	set_name(surname[random(sizeof(surname))]+"��ͷ", ({ "biaoshi", "biao"}) );
	set("gender", "����" );
	set("age", 25);
	set("str", 45);
	set("cor", 50);
	set("cps", 35);
	set("int", 20);
	set("per", 20);
	set("kar", 15);
	set("long", "һλѵ�����ص���ͷ��\n");
	set("combat_exp", 70000);
	set("attitude", "heroism");
	set_skill("parry", 90);
	set_skill("dodge", 100);
	
	setup();
	carry_object(__DIR__"obj/jinzhuang")->wear();
	add_money("silver",30);
}
