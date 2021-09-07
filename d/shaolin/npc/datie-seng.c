// datie-seng.c

inherit NPC;

int   ask_qiao();
mixed ask_armor();

string* armors = ({
	"/clone/book/book-iron",
	"/d/shaolin/obj/tieshou",
	"/d/shaolin/obj/tieshou",
	"/d/shaolin/obj/tieshou",
	"/d/shaolin/obj/tieshou",
	"/d/shaolin/obj/tieshou",
	"/d/shaolin/obj/tieshou",
	"/d/shaolin/obj/tieshou",
	"/d/shaolin/obj/tieshou",
	"/d/shaolin/obj/tieshou",
});

void create()
{
	set_name("����ɮ", ({ "datie seng", "datie", "seng" }) );
	set("gender", "����" );
	set("age", 38);
	set("long", "���Ǹ���ǿ��׳��Ƥ���ֺڵĴ���ɮ�ˡ�\n");
	set("str", 25);
	set("dex", 20);
	set("con", 17);
	set("int", 15);
	set("shen_type", 1);

	set_skill("unarmed", 50);
	set_skill("dodge", 35);
	set_temp("apply/attack", 5);
	set_temp("apply/defense", 5);
	set("combat_exp", 7500);

	set("attitude", "peaceful");
	set("inquiry", ([
		"����" : (: ask_qiao :),
		"������" : (: ask_armor :),
	]));
	set("chat_chance", 3);
	set("chat_msg", ({
		"����ɮ�������ɽ���µ����Ǹ������������"
		"�͹����Ķ���Щ��÷��õľ�����\n",
		"����ɮ�����������ϵȾ������õò���ˣ���"
		"�ûۺ���������ȥ������Щ������ ......��\n"
	}));

	set("hand_count", 20);

	setup();
}


int ask_qiao()
{
	if (this_player()->query_temp("marks/�ʹ�����"))
	{
		command("say ��ѽ������ǲ������\n");
	}
   	else
   	{
		command("say ���Ǿ�ס������ɽɽ���£�������"
			"�ڶ�ͷ��������ͷ����������ԣ�\n");
		this_player()->set_temp("marks/�ʹ�����", 1);
	}
	return 1;
}


mixed ask_armor()
{
	object armor, me, ob;

	me = this_object();
	ob = this_player();

	if (present("iron hand", ob))
		return "�㲻�Ѿ���һ������ ���������ɶ�ã�";

	if (present("iron hand", environment(ob)))
		return "�����ⲻ��һ���� ��Ҫ�Ļ��ͼ��߰ɡ�";

	if (time() - ob->query_temp("last_ask/for_hand") < 240)
		return "�ţ��Ҳ��Ǹո���һ�����㻹Ҫ��ɶ��";

	if (query("hand_count") < 1)
		return "Ŷ����������һ��Ѹ��ң������Ҷ������ˡ�";

	say("�����ƣ� ���������ɶ�ã�\n"
	    "��������һ��Ѹ��ң���Ҫ�Ļ�������һ��ȥ�ա�\n");

	add("hand_count", -1);
	ob->set_temp("last_ask/for_hand", time());

	armor = new(armors[random(sizeof(armors))]);
	armor->move(ob, 1);

	message_vision("$N����$nһ�������ơ�\n", me, ob);
	return 1;
}

void reset()
{
	set("hand_count", 20);
}
