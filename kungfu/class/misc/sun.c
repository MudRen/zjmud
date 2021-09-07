// beihai.c

#include <ansi.h>

inherit NPC;

void random_move();
void random_attack();

void create()
{
	set_name("�����", ({ "sun wukong", "sun" }));
	set("title", HIY "��սʤ��" NOR);
	set("gender", "����");
	set("age", 3000);
	set("long", @LONG
һ�Ż�ɫ�Ĺ�â������Ȼ͸��һ�ˣ�ϸ��ȴ���ܲ�׽�������Ρ�
LONG );
	set("combat_exp", 100000000);
	set("score", 10000000);
	set("shen_type", 0);
	set("attitude", "friendly");
	set("max_neili", 60000);
	set("neili", 60000);
	set("max_jing", 60000);
	set("jing", 60000);
	set("max_qi", 60000);
	set("qi", 60000);
	set("jingli", 60000);
	set("max_jingli", 60000);

	set("str", 200);
	set("int", 200);
	set("con", 200);
	set("dex", 200);

	set_skill("unarmed", 1500);
	set_skill("parry", 1500);
	set_skill("dodge", 1500);
	set_skill("force", 2000);

	set("jiali", 0);

	set_temp("apply/unarmed_damage", 800);
	set_temp("apply/armor", 3000);

	if (clonep(this_object()))
	{
		set("chat_chance", 30);
		set("chat_msg", ({ (: random_move :) }));
		set("chat_chance_combat", 120);
		set("chat_msg_combat", ({ (: random_attack :) }));
		set("born_time", time());
		keep_heart_beat();
	}

	setup();
}

mapping *actions = ({
([      "action": "$N΢һ����$w���Ŵ̶���֨֨��������ɨ��$n�Ľ���",
	"damage_type":"����"
]),
([      "action": "$N������ס$w������һ����ֻ��$w����$n�ļ�ͷ",
	"damage_type":"����"
]),
([      "action": "$N����$wƹƹ���ҵ��������ã���$n�����ұܣ��Ǳ�����",
	"damage_type":"����"
]),
([      "action": "$N����$w��ͻȻ�͵�һ������$n��$l",
	"damage_type":"����"
]),
([      "action": "$N��$wһ��ָ��$n�����ٴ���$n",
	"damage_type":"����"
]),
([      "action": "$Nȫ��ֱ�������ų���ǰ�У��䲻������$w������$n��ȥ",
	"damage_type":"����"
]),
([      "action": "$N���⽫$wˤ����ϣ���$n������һ�Ź��𣬻���$n��$l",
	"damage_type":"����"
]),
([      "action": "$Nһ������������$w��������������$n���ɲ�",
	"damage_type":"����"
]),
([      "action": "$N�������Ų��ƣ�$wȴֱ�ɰ�գ���ƫ���е�����$n��$l",
	"damage_type":"����"
]),
([      "action": "$N�߾�$w����������Ȱ�Ʈ������׼$n�������һ������",
	"damage_type":"����"
]),
([      "action": "$N��$w���ǧ�ٸ����ƣ���������$nȫ�����Ҫ��",
	"damage_type":"����"
]),
});

mapping query_action()
{
	mapping action;

	action = actions[random(sizeof(actions))];
	action["action"] = replace_string(action["action"], "$w",
					  HIY "�𹿰�" NOR);
	return action;
}

void fight_ob(object ob)
{
	if (is_fighting(ob))
		return;


	message_vision(HIY "$N" HIY "����һЦ������$n����һ����"NOR"\n",
		       this_object(), ob);

	::fight_ob(ob);
	if (! is_killing(ob->query("id")))
		kill_ob(ob);
}

int attack()
{
	object ob, *obs;
	string msg;

	obs = ({ });
	clean_up_enemy();

	foreach (ob in query_enemy())
	{
		if (ob->query("combat_exp") > 1000000)
			continue;

		obs += ({ ob });
	}

	if (sizeof(obs))
	{
		msg = HIY "$N" HIY "����һ�Ž�" +
		      implode(obs->name(), HIY "��") +
		      HIY "�ߵ�һ�ߣ��ȵ�������������"NOR"\n";
		message_sort(msg, this_object(), ob);
		obs->unconcious();
		obs -= ({ 0 });
		foreach (ob in obs)
		{
			remove_enemy(ob);
			remove_killer(ob);
			ob->remove_enemy(this_object());
			ob->remove_killer(this_object());
		}
	}

	return ::attack();
}

int accept_fight(object ob)
{
	if (ob->query("combat_exp") < 3000000)
	{
		message_vision("$N������$n��\n",
			       this_object(), ob);
		return 0;
	}

	message_vision("$Nϲ�������úã����������û������ˣ�"
		       "���վͺ������桱\n", this_object(), ob);
	return 1;
}

int accept_kill(object ob)
{
	return 1;
}

int accept_hit(object ob)
{
	return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
	me->set("neili", me->query("max_neili"));
	if (playerp(ob) && ! ob->query("breakup"))
	{
		ob->set("qi", -1);
		ob->set("eff_qi", -1);
		return HIR "$N" HIR "һ��������$n" HIR
		       "���ϣ�ֻ��$n" HIR "���̱�ѹ���ڵأ�"NOR"\n";
	}

	ob->receive_wound("qi", 400 + random(400), me);
	switch (random(3))
	{
	case 0:
		return HIY "$N" HIY "һ������$n" HIY "���ϣ�"
		       HIY "$n" HIY "��ʱ���û����䡱��һ�£�"
		       "����ʧȥ֪����"NOR"\n";
	case 1:
		return HIY "$N" HIY "һ�����£�$n" HIY "ֻ����"
		       "����ǡ��ˡ���һ�£�������ʡ���£�"NOR"\n";

	default:
		return HIY "$N" HIY "һ����$n" HIY "���˸��������ᣬ"
		       "���㲻�ȣ�"NOR"\n";
	}
}

void unconcious()
{
	die();
}

void die()
{
	string *ob_list = ({
		"/clone/gift/diamond",
		"/clone/gift/agate",
		"/clone/gift/crystal",
		"/clone/gift/jade",
	});
	object ob;

	ob = new(ob_list[random(sizeof(ob_list))]);

	command("chat ������������ò������˼䣬�����뻹��������"
		"���յ��ˣ��������棡");
	message_sort(HIY "$N" HIY "����һ���ھ�����Ȼ���ƶ�ȥ��ֻ������"
		     "Ŀ�ɿڴ���������ֻ����������Ʈ��һ���Ʋʡ�"NOR"\n",
		     this_object());
	ob->move(environment());
	destruct(this_object());
}

void random_move()
{
	if (time() - query("born_time") > 7200)
	{
		message_vision("$N����ææ�����ˡ�\n", this_object());
		CHANNEL_D->do_channel(this_object(), "rumor",
			"��˵" + name() + HIM "����һ�ȥ�ˡ�" NOR);
		destruct(this_object());
		return;
	}
	NPC_D->random_move(this_object());
}

void random_attack()
{
	object ob;

	set("qi", query("eff_qi"));
	set("jing", query("eff_jing"));
	if (query("qi") < query("max_qi") * 3 / 5 ||
	    query("jing") < query("max_jing") * 3 / 5)
	{
		if (query_temp("recover_times") >= 3)
		{
			die();
			return;
		}

		message_combatd(HIM "$N" HIM "ʩչ�����������������õ�����ȫ�ָ���"NOR"\n",
				this_object());
		add_temp("recover_times", 1);
		set("eff_qi", query("max_qi"));
		set("qi", query("max_qi"));
		set("eff_jing", query("max_jing"));
		set("jing", query("max_jing"));
		return;
	}

	clean_up_enemy();
	ob = select_opponent();
	if (! objectp(ob))
		return;

	switch (random(10))
	{
	case 0:
		message_combatd(HIY "$Nץ��һ�Ѻ�ë���ã����ۡ��Ĵ���һ������"
				"��ʱ����ǧ�ٸ�С���ӣ��ֳֽ𹿰�\n"
				"����Χ����������һ���Ҵ�"NOR"\n",
				this_object());
		set_temp("apply/name", ({ "С����" }));
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		attack();
		delete_temp("apply/name");
		break;

	case 1:
		message_combatd(HIY "$N" HIY "����һЦ�����еĽ𹿰���Ȼ���"
				"�޴��ޱȣ�����$n" HIY "ֱѹ��ȥ��\nֻ��$n"
				"��ʱ�����˸����������ʮ����"NOR"\n",
				this_object(), ob);
		ob->receive_damage("qi", 1000 + random(1000), this_object());
		ob->receive_wound("qi", 700 + random(700), this_object());
		ob->interrupt_busy(ob, 10 + random(10));
		break;

	case 2:
		if (ob->is_busy())
			break;
		message_combatd(HIY "$N" HIY "��$n" HIY "�ȵ�����������ֻ��"
				"$n" HIY "�۾�һ�ɣ���ô���ľ����"NOR"\n",
				this_object(), ob);
		ob->start_busy(50 + random(50));
		break;
	}
}

