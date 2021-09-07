//tiegongji.c

inherit NPC;
inherit F_BANKER;

void create()
{
	set_name("������", ({"tie gongji", "tie", "gongji"}));
	set("title", "Ǯׯ�ϰ�");
	set("gender", "����");
	set("age", 46);
	set("dealer", "bank");
	set("kee", 800); 
	set("max_kee", 800);
	set("sen", 200);
	set("max_sen", 200);
	set("combat_exp", 50000);
	set("attitude", "friendly");
	set("env/wimpy", 50);
	set("chat_chance", 10);
	set("chat_msg", ({
		"�������ٺٺٵ�Ц�˼�������������̼�ʮ�����ɴ���û������\n",
		"������������˵�����������Ѿ����ϰ������ʷ���ڳ����ǿ���˵�ǵ�һ�ҡ�\n"
	}));
	set_skill("unarmed", 60);
	set_skill("parry", 60);
	set_skill("dodge", 60);

	setup();
	carry_object(__DIR__"obj/choupao")->wear();
	add_money("silver", 1);
}

void init()
{
	add_action("do_check", "check");
	add_action("do_convert", "duihuan");
	add_action("do_deposit", "cun");
	add_action("do_withdraw", "qu");
}

void enough_rest()
{
	delete_temp("busy");
}

int do_audit()
{
	int total = (int)this_player()->query("balance");
	if (! total || total < 0)
	{
		this_player()->set("balance", 0);
		return notify_fail("���ڱ�Ǯׯû�д�Ǯ��\n");
	}
	write("���������ĸ����㣺���ڱ�Ǯׯ������" + 
		MONEY_D->money_str(total) + "\n");
	return 1;							       
}
