#include "roomnpc.h"

inherit NPC;

int  accept_object(object who, object ob);

void create()
{
	set_name("����", ({"pu ren"}) );
	set("gender", "����" );
	set("age", 20 + random(20));
	set("long", "����һ�����ˣ������Һ���ʵ��");
	set("attitude", "friendly");

	setup();
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

	destruct(ob);
	message_vision(name() + "��$N��ͷ������������л��λ" +
		       RANK_D->query_respect(who) + "������\n", who);
	return 1;
}
