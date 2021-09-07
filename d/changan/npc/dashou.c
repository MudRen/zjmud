//dashou.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("����", ({ "da shou" }) );
	set("title",MAG "����ʹ��" NOR);
	set("age", random(25)+15);
	set("long", "һ��ΪȺ��¥Ч�������ڿ��ŵĴ���\n");
	set("per",15);
	set("combat_exp", 100000);
	set("no_arrest",1);
	set("attitude", "heroism");
	set("gender", "����" );
	set_skill("unarmed", 200);
	set_skill("blade",200);
	set_skill("parry", 200);
	set_skill("dodge", 200);

	setup();
	add_money("silver", 6);
	carry_object(__DIR__"obj/cloth")->wear();
	carry_object(__DIR__"obj/blade")->wield();
	
}

void init()
{
	add_action("do_killing", "kill");
}

int do_killing(string arg)
{
	object player, victim, weapon;
	string name;

	player = this_player();
	if (! arg) return 0;
	if (objectp(victim = present(arg, environment(this_object())))
	    && living(victim))
	{
		name = (string)victim->name();
		if ((string)name == "����")
		{
			message_vision("$N�����ҵ���Ⱥ��¥���£���"
				       "�����ò��ͷ��ˡ�\n",
				       this_object());
			this_object()->kill_ob(player);
			player->kill_ob(this_object());
			return 1;
		}
	}
	return 0;
}
