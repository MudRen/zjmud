// helper for user

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

void create()
{
	::create();
	set("gender", "����" );
	set("age", 15 + random(20));
	set("long", "");
	set("attitude", "friendly");
	set("chat_chance_combat", 120);
	set_temp("apply/damage", 15);
}

void init_man(mapping p)
{
	mapping my;

	my = query_entire_dbase();
	my["qi"] = my["eff_qi"] = my["max_qi"] = p["life"];
	my["jing"] = my["eff_jing"] = my["max_jing"] = p["life"] / 2;
	my["neili"] = my["max_neili"] = p["neili"];
	my["jingli"] = my["max_jingli"] = p["neili"] / 4;
	my["jiali"] = query_skill("force") / 2;

	set_temp("apply/armor", 100);
}

void kill_ob(object ob)
{
	if (ob->query("family/family_name") == query("family/family_name"))
	{
		message_vision(HIC "$N" HIC "���˿��Է�����æ����һ����"
			       "���������������ס�֣��л���˵����"NOR"\n",
			       this_object());
		return;
	}

	::kill_ob(ob);
}

int accept_fight(object ob)
{
	message_vision("$N����ҡͷ�������������ˣ���û����Ȥ����\n",
		       this_object());
	return 0;
}

int accept_hit(object ob)
{
	message_vision("$N����һ�ˣ��������ҿ�û����Ȥ������С���\n",
		       this_object());
	return 0;
}

int accept_kill(object ob)
{
	if (ob == query_temp("owner"))
	{
		message_vision("$N���һ�ˣ���������������ν������������"
			       "��ȥ�����ǲ����̷����ˣ���\n˵�գ�Ҳ����"
			       "$n�ػ����Թ�ȥ�ˡ�\n", this_object(), ob);
		destruct(this_object());
		return -1;
	}

	message_vision("$Nһ����Ц�����������д������аɣ���\n",
		       this_object());
	return 1;
}

void destruct_by_owner()
{
	call_out("destruct_me", 1);
}

private void destruct_me()
{
	destruct(this_object());
}

void scan()
{
	object ob;
	object env;
	object *obs;
	object enemy;

	set_temp("nopoison", 1);

	if (objectp(query_temp("renter")))
		return;

	if (! objectp(ob = query_temp("owner")))
	{
		if (environment())
			message_vision("$N����ææ�����ˡ�\n", this_object());
		destruct(this_object());
		return;
	}

	if ((time() - query_temp("help_time")) >= 86400)
	{
		if (environment())
		{
			command("tell " + ob->query("id") + " ������һ�꣬��"
				"ʱ������͵����������ٻ�ɣ�\n");
			message_vision("$N����ææ�����ˡ�\n", this_object());
		}
		destruct(this_object());
		return;
	}

	::scan();

	env = environment(ob);
	if (environment() == env || ob->is_ghost())
		// �������ڵĵص���ͬ���������˴��ڹ��״̬
		return;

	if (is_busy() || is_fighting() || ! living(this_object()))
		// ����æ
		return;

	if (! sizeof(env->query("exits")) ||
	    ! sizeof(environment()->query("exits")))
		return;

	message_vision("$N����ææ���߿��ˡ�\n", this_object());
	if (! move(env)) return;
	obs = filter_array(all_inventory(env),
			   (: $1->is_character() &&
			      $1->is_killing($(ob)->query("id")) &&
			      $1->query_competitor() != $(ob) :));
	if (sizeof(obs))
	{
		message_vision("$N����ææ�ĸ��˹���������$n��"
			       "�ڿභ���������һ����������$n��ս�ţ�\n",
			       this_object(), ob);
		foreach (enemy in obs) kill_ob(enemy);
	} else
		message_vision("$N���˹�����վ��$n�����\n",
			       this_object(), ob);
}
