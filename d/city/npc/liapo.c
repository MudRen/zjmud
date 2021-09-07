// liapo.c ���

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("���", ({ "li apo", "li", "apo" }));
	set("str", 18);
	set("gender", "Ů��");
	set("age", 58);
	set("long", "��������ݻ��˼�ʮ�꣬�Ϳ��ִ߽��������˹����ӡ�\n");
	set("combat_exp", 250);
	set("attitude", "friendly");
	set("vendor_goods", ({
		"/clone/misc/cailiao",
	}));

	set("carried_goods", 1);

	setup();
	carry_object("/clone/misc/cloth")->wear();

	if (clonep())
	{
		set("chat_chance", 20);
		set("chat_msg", ({
			(: NPC_D->random_move(this_object()) :),
		}));
		keep_heart_beat();
	}
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}
