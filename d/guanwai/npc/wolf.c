// wolf.c

inherit NPC;

#include <ansi.h>

void create()
{
	set_name(WHT "Ұ��" NOR, ({ "wolf", "lang", "ye lang" }) );
	set("race", "Ұ��");
	set("age", 10);
	set("long", "һֻ���͵�Ұ�ǣ����������һ���׺�ģ����\n");
	set("attitude", "aggressive");

	set("limbs", ({ "ͷ��", "����", "ǰצ", "��צ", "β��" }) );
	set("verbs", ({ "bite", "claw" }));
	set("unit", "ƥ");

	set("combat_exp", 30000);
	set_temp("apply/attack", 180);
	set_temp("apply/defense", 150);
	set_temp("apply/armor", 50);

	setup();
}

void init()
{
	if (query_temp("owner"))
		return;

	if (sscanf(base_name(environment()), "/d/guanwai/%*s") == 1 &&
	    environment()->query("outdoors"))
	{
		if (playerp(this_player()))
			kill_ob(this_player());
	} else
	{
		remove_call_out("greeting");
		call_out("greeting", 1, this_player());
	}
}

void greeting(object ob)
{
	if (! objectp(ob) || environment(ob) != environment())
		return;

	message_vision("$N����Ķ���$n��Ŀ����͸¶��һ�ɺݾ���\n",
		       this_object(), ob);
}

void unconcious()
{
	die();
}

void die()
{
	message_vision("\n$N����һ��������β�������ˣ�\n", this_object());
	destruct(this_object());
}
