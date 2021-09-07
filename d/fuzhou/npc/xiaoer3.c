// xiaoer3.c �Ƶ�С��

inherit KNOWER;
inherit F_DEALER;

void create()
{
	set_name("��С��", ({ "xiao er", "xiao", "waiter" }) );
	set("gender", "����" );
	set("age", 22);
	set("long",
		"��λ��С����Ц�����æ��������ʱ������ڲ����ϵ�Ĩ��������\n");
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("rank_info/respect", "С����");
	set("no_get", "1");
	set("vendor_goods", ({
		__DIR__"obj/fotiaoqiang",
		__DIR__"obj/jiuping",
	}));
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{	
	::init();
	remove_call_out("greeting");
	call_out("greeting", 1, this_player());

	add_action("do_buy", "buy");
	add_action("do_list", "list");
}

void greeting(object ob)
{
	if (! ob || environment(ob) != environment())
		return;

	switch (random(2))
	{
		case 0:
			say("��С��Ц�����˵������λ" + RANK_D->query_respect(ob) +
			    "�������ȱ��裬ЪЪ�Ȱɡ�\n");
			break;
		case 1:
			say("��С���ò����ϵ�ë��Ĩ��Ĩ�֣�˵������λ" +
			    RANK_D->query_respect(ob) +
			    "����������\n");
			break;
	}
}
