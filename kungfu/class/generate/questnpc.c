// person used in quest

inherit CLASS_D("generate") + "/chinese";

void random_move();

void create()
{
	mapping my;
	int lvl;

	::create();
	set("gender", "����" );
	set("age", 30 + random(30));
	set("long", "");
	set("attitude", "friendly");
	set("chat_chance", 30);
	set("chat_msg", ({ (: random_move :) }));
	set("scale", 150);
	set_temp("apply/armor", 100);
	set_temp("apply/damage", 50);
	set_temp("born_time", time());

	lvl = 3 + random(4);
	NPC_D->init_npc_skill(this_object(), lvl);

	// ��ʼ��NPC������
	my = query_entire_dbase();
	my["max_qi"] = 1000 + lvl * 300 + random(500);
	my["max_jing"] = my["max_qi"] / 2;
	my["max_neili"] = 1000 + lvl * 500 + random(500);
	my["eff_jing"] = my["max_jing"];
	my["jing"] = my["max_jing"];
	my["eff_qi"] = my["max_qi"];
	my["qi"] = my["max_qi"];
	my["neili"] = my["max_neili"] * 2;
}

int accept_fight(object ob)
{
	command("say �ţ�����ʲô�ˣ���û����Ȥ���������");
	return 0;
}

int accept_hit(object ob)
{
	message_vision("$N��ɫһ�䣬��û�����$n��ת����ææ"
		       "�������ˡ�\n", this_object(), ob);
	NPC_D->random_move(this_object());
	return -1;
}

int accept_kill(object ob)
{
	command("say ���д�����Ȼ�۸����ҵ�ͷ���ˣ�");
	command("yun powerup");
	return 1;
}

void random_move()
{
	NPC_D->random_move(this_object());
}

void remove()
{
	if (! environment() || query_temp("die"))
	{
		::remove();
		return;
	}

	if (! living(this_object()))
	{
		message_vision("·�������ˣ��������Բ��ѵ�$N"
			       "��̾��������$P�����ˡ�\n",
			       this_object());
		return;
	}

	message_vision("$N���˿����ܣ�����ææ�����ˡ�\n",
		       this_object());

	::remove();
}

void die(object killer)
{
	set_temp("die", 1);
	::die(killer);
}
