// mafu.c ���
#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
	set_name("���", ({ "ma fu", "mafu", "ma"}));
	set("age", 32);
	set("gender", "����");
	set("long", "�������ѱ���С��ƣ�ƽʱ����������ƥ��\n");
	set("attitude", "friendly");
	set("str", 24);
	set("dex", 16);
	set("combat_exp", 400000);
	set("shen_type", 1);
	set("icon", "05009");
	set("chat_chance",1);
	
	setup();
}

void init()
{
	object ob;

	::init();
	if (interactive(ob = this_player()) && ! is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if (! ob || environment(ob) != environment())
		return;

	say("����ͷ������˵������λ�͹٣����ã�����ȥ�Ķ�����\n");
}

int accept_object(object who, object ob)
{
	if (ob->query("money_id"))
	{
		message_vision("$N��$n������ȥ(goto)�Ķ����ȸ���С���ٸ�Ǯ��\n",
			       this_object(), who);
		return 0;
	}

	return 0;
}
