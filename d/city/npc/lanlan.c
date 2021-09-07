// lanlan.c

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("����", ({ "lan lan", "lan" }));

	set("gender", "Ů��");
	set("age", 20);
	set("per", 30);
	set("con", 30);
	set("int", 30);
	set("level", 99);
	set("dex", 30);
	set("icon","02046");
	set("str", 30);
	set("long",
 "����angelus��δ���ޣ��������æ��������̣���Щ�Լ���Ƶ��·���
����˵�Ƕ���angelus��2010��Ū���Ľ�Ʒ������ô˵���������������ε���\n");
	set_skill("unarmed", 600);
	set_temp("apply/damage", 150);
	set("combat_exp", 500000);
	set("attitude", "friendly");
	set("vendor_goods", ({
		__DIR__"cloth/moon-dress",
		__DIR__"cloth/pink-dress",
		__DIR__"cloth/qi-dress",
		__DIR__"cloth/red-dress",
		__DIR__"cloth/scarf",
		__DIR__"cloth/sha-dress",
		__DIR__"cloth/shoes",
		__DIR__"cloth/xian-cloth",
		__DIR__"cloth/xiu-cloth",
		__DIR__"cloth/xiu-scarf",
		__DIR__"cloth/yan-dress",
		__DIR__"cloth/zi-dress",


	}));
	
	setup();
	carry_object(__DIR__"cloth/feature")->wear();
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}
