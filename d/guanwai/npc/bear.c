// bear.c

inherit NPC;
#include <ansi.h>;

void create()
{
	set_name(CYN "����" NOR, ({ "hei xiong", "bear", "xiong" }));
	set("race", "Ұ��");
	set("age", 20);
	set("long", "һֻ���͵ĺ��ܣ�����˶���������С�\n");
	set("attitude", "aggressive");

	set("limbs", ({ "��ͷ", "����", "ǰצ", "��צ" }) );
	set("verbs", ({ "bite", "claw" }) );
	set("unit", "ֻ");

	set("combat_exp", 50000);
	set_temp("apply/attack", 200);
	set_temp("apply/defense", 280);
	set_temp("apply/armor", 120);

	setup();

	set("chat_chance", 10);
	set("chat_msg", ({
		"���ܳ�����ҡͷ��β�أ���֪����ʲô��˼��\n",
		"���ܼ��˼����ӣ��������������Ц����ʱһ����š�\n",
	}));
}

void init()
{
	if (query_temp("owner"))
		return;

	if (sscanf(base_name(environment()), "/d/guanwai/%*s") == 1 &&
	    environment()->query("outdoors"))
		kill_ob(this_player());
	else
	{
		remove_call_out("greeting");
		call_out("greeting", 1, this_player());
	}
}

void greeting(object ob)
{
	if (! objectp(ob) || environment(ob) != environment())
		return;

	message_vision("$N�����Ŀ���$n��\n",
		       this_object(), ob);
}

void die()
{
	object ob, corpse;

	message_vision("$N���춯��һ���Һ�������ί���ڵأ����ˣ�\n", this_object());

	if (objectp(corpse = CHAR_D->make_corpse(this_object())))
	{
		ob = new(__DIR__"xiongdan");
		ob->move(corpse);
		corpse->move(environment(this_object()));
		destruct(this_object());
	}
}
