#include "roomnpc.h"

inherit NPC;

void greeting(object ob);
void init();
int  accept_object(object who, object ob);

void create()
{
	set_name("Ѿ��", ({"girl", "ya huan"}) );
	set("gender", "Ů��" );
	set("age", 12 + random(6));
	set("long", "���Ǹ����䲻���С���һ���������ɡ�");
	set("attitude", "friendly");

	setup();
}

void init()
{
	object ob;

	::init();

	if (interactive(ob = this_player()) && !is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

void greeting(object ob)
{
	if (! ob || (environment(ob) != environment())) return;

	if (is_owner(ob))
	{
		message_vision(name() + "��$Nӯӯ����һ���򸣡�\n", ob);
		command("say ��ʲô�Ը���");
		return;
	}
	message_vision(name() + "��$N��������λ" + RANK_D->query_respect(ob) +
		"�á���\n", ob);
}

int accept_object(object who, object ob)
{
	object obn;

	if (! ob->query("money_id"))
		return 0;

	if (is_owner(who))
	{
		message_vision(name() + "��$Nʩ��һ��\n", who);
		destruct(ob);
		return 1;
	}

	if (ob->value() < 1000)
	{
		if (owner_is_present())
		{
			say(name() + "����Ը�Ľ�����" + ob->name() + "��\n");
			destruct(ob);
			return 1;
		}
		message_vision(name() + "��Ŀ԰�����ȵ���������Ϊ�Ǵ�"
			       "���л��Ӱ�����\n", who);
		return 0;
	}

	destruct(ob);
	message_vision(name() + "��$N΢΢һЦ����������л��λ" +
		       RANK_D->query_respect(who) + "������\n", who);
	return 1;
}
