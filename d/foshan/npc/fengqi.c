// fengqi.c

inherit KNOWER;
inherit F_DEALER;

void create()
{
	set_name("����", ({ "feng qi", "feng", "qi" }) );
	set("gender", "����" );
	set("title", "��¥�ϰ�" );
	set("age", 42);
	set("long", @LONG
�����Ƿ����ϵ�Զ����ܣ�����Ӣ��¥���ƹ��书û��ʲô��Ϊ��
ȴ���ǻ��飬�����ϴ��СС�����鶼֪��һЩ
LONG );
	set("combat_exp", 10000);
	set("attitude", "friendly");
	set("rank_info/respect", "�߸�");
	set("vendor_goods", ({
		"/clone/food/jitui",
		"/clone/food/jiudai",
		"/clone/food/baozi",
	}));
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{	
	object ob; 
	mapping myfam; 

	ob = this_player();

	::init();
	if (interactive(ob) && ! is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}

	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

void greeting(object ob)
{
	if (! ob || environment(ob) != environment()) return;
	switch (random(2))
	{
		case 0:
			say( "����Ц�����˵������λ" + RANK_D->query_respect(ob)
				+ "�������ȱ��裬ЪЪ�Ȱɡ�\n");
			break;
		case 1:
			say( "����Ц�����˵������λ" + RANK_D->query_respect(ob)
				+ "���������\n");
			break;
	}
}

void unconcious()
{
	die();
}
