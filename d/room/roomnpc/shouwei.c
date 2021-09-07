#include "roomnpc.h"

inherit CLASS_D("generate") + "/chinese";
inherit F_GUARDER;
inherit F_COAGENT;

int  accept_object(object who, object ob);

void create()
{
	::create();
	set_name(query("name"), ({ query("id"), "shou wei", "guarder" }));
	NPC_D->init_npc_skill(this_object(), 7 + random(2));
	set("gender", "����" );
	set("age", 30 + random(30));
	set("long", "���ǿ���ׯ԰������������ȥ�ƺ���������\n");
	set("attitude", "friendly");

	set("max_qi", 4800);
	set("eff_qi", 4800);
	set("qi", 4800);
	set("max_jing", 2400);
	set("eff_jing", 2400);
	set("jing", 2400);
	set("max_neili", 5200);
	set("neili", 5200);
	set("jiali", 100);
}

void init()
{
	::init();
	add_action("do_invite", "invite");
	add_action("do_show", "show");
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
	return 0;
}

int accept_hit(object ob)
{
	if (is_owner(ob))
	{
		message_vision("$N��æ�ڰ��֣���$n�������ɲ�Ҫ���ҿ���"
			       "����Ц����\n", this_object(), ob);
		return 0;
	}

	return ::accept_hit(ob);
}

int accept_fight(object ob)
{
	if (is_owner(ob))
	{
		message_vision("$N����һ������æ��$n������С�Ĳ��ң�С"
			       "�Ĳ��ң���\n", this_object(), ob);
		return 0;
	}

	return ::accept_fight(ob);
}

int accept_kill(object ob)
{
	if (is_owner(ob))
	{
		message_vision("$Nһ����̾����������Ȼ���˲������ˣ���"
			       "�հգ���������������ȥ�������ˡ���\n"
			       "˵�գ�$Nһ���֣�����һ���¾�ƮȻ��ȥ��\n",
			       this_object(), ob);
		destruct(this_object());
		return 0;
	}

	return ::accept_kill(ob);
}
