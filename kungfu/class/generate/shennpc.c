// person used in quest shen

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

void random_move();

void create()
{
	mapping my;

	::create();
	set("gender", "����" );
	set("age", 30 + random(30));
	set("long", "");
	set("attitude", "friendly");
	set("chat_chance", 30);
	set("chat_msg", ({ (: random_move :) }));
	set("scale", 150);
	set_temp("apply/armor", 30);
	set_temp("apply/damage", 20);
	set_temp("born_time", time());

	NPC_D->init_npc_skill(this_object(), 1);

	// ��ʼ��NPC������
	my = query_entire_dbase();
	my["max_qi"] = 500;
	my["max_jing"] = 250;
	my["max_neili"] = 800;
	my["eff_jing"] = my["max_jing"];
	my["jing"] = my["max_jing"];
	my["eff_qi"] = my["max_qi"];
	my["qi"] = my["max_qi"];
	my["neili"] = my["max_neili"] * 2;
}

int accept_fight(object ob)
{
	command("say ��û����Ȥ�����������������");
	return 0;
}

int accept_hit(object ob)
{
	message_vision("$N��ɫһ�䣬����һ��ɱ�����ȵ�������һ��" +
		       RANK_D->query_rude(ob) + "�����ɣ���\n", this_object());
	kill_ob(ob);
	return 1;
}

int accept_kill(object ob)
{
	if (! living(this_object()))
		return 1;

	return accept_hit(ob);
}

int accept_ansuan(object ob)
{
	return notify_fail("���˾����Ժøߣ����������֡�\n");
}

int accept_touxi(object ob)
{
	return notify_fail("���˾����Ժøߣ����������֡�\n");
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
	object ob;

	if (objectp(ob = killer) ||
	    objectp(ob = query_last_damage_from()))
	{
		if (query("shen_type") == 1)
		{
			QUEST_D->delay_bonus(ob, ([ "prompt" : "��������һ������֮��",
						    "shen"   : -random(100) - 100,
						    "score"  : random(5) + 5,
						    "weiwang": random(3) + 2, ]));
			CHANNEL_D->do_channel(this_object(), "rumor",
				"��˵" + ob->name(1) + "(" + ob->query("id") + ")��" +
				environment()->short() + "ɱ����" +
				name() + "��Ϊ��͢��ȥһ�ĸ�֮����");
		} else
		{
			QUEST_D->delay_bonus(ob, ([ "prompt" : "��������һ������֮��",
						    "shen"   : random(100) + 100,
						    "score"  : random(5) + 5,
						    "weiwang": random(3) + 2, ]));
//			CHANNEL_D->do_channel(this_object(), "rumor",
//				"��˵" + ob->name(1) + "(" + ob->query("id") + ")��" +
 //			       environment()->short() + "������" +
//				name() + "��Ϊ���ճ�ȥһ����");
		}
	}

	set_temp("die", 1);
	::die(killer);
}
