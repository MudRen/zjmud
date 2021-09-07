#include <weapon.h>
#include <ansi.h>

inherit SWORD;

string do_wield();
string do_unwield();

void create()
{
	set_name(HIY "���佣" NOR,({ "zhenwu jian", "jian", "sword", "zhenwu" }) );
	set_weight(1500);
	if (clonep())
		destruct(this_object());
	else {
		set("long", @LONG
����һ�����������ı����������䵱�����˳ִ˽�������ħ��ɨ��Ⱥ��
������С�����˽��޲��ĵ���ҡ��
LONG );
		set("unit", "��");
		set("value", 800000);
		set("icon","05058");
		set("no_sell", 1);
		set("material", "steel");
		set("wield_msg", (: do_wield :));
		set("unwield_msg", (: do_unwield :));
		set("stable", 80);
	}
	init_sword(200);
	setup();
}

string do_wield()
{
	object me;

	me = this_player();
	remove_call_out("check_npc");
	call_out("check_npc", 0, me, environment(me));
	if (me->query("shen") > 10000)
		return HIC "$Nһ����Х����$n" HIC "�������ʣ���ʱ��ؼ������Ȼ��"NOR"\n";
	else
	if (me->query("shen") >= 0)
		return HIC "$Nһ���֣���Ȼ��$n" HIC "�������С�"NOR"\n";
	else
	if (me->query("shen") > -10000)
		return HIG "$Nսս����������һ��$n" HIG "��"NOR"\n";
	else
		return HIG "$Nһ����Ц����ৡ���һ��������$n" HIG "��"NOR"\n";
}

string do_unwield()
{
	object me;

	me = this_player();
	remove_call_out("check_npc");
	if (me->query("shen") >= 0)
		return HIC "$Nһ���֣��������ʡ�"NOR"\n";
	else
	if (me->query("shen") > -10000)
		return HIG "$N��$n" HIG "��ؽ��ʣ�Ĩ��Ĩͷ�ϵĺ���"NOR"\n";
	else
		return HIG "$Nһɹ����$n" HIG "��ؽ��ʡ�"NOR"\n";
}

void check_npc(object me, object env)
{
	object *ob;
	int i;

	if (! objectp(me) || ! living(me))
		return;

	if (environment(me) != env)
		return;

	ob = all_inventory(env);
	for (i = 0; i < sizeof(ob); i++)
	{
		if (! ob[i]->is_character() || ob[i] == me ||		    
		    ! living(ob[i]) || ob[i]->query("not_living") ||
		    ob[i]->query("id") == "zhang sanfeng")
			continue;

		if (me->is_bad())
		{
			if (userp(ob[i]))
				continue;

			if (ob[i]->query("shen") > 10000)
			{
				message_vision("$N��ŭ�ȵ��������" + RANK_D->query_rude(me) +
					       "����Ȼ�ҵ������佣��\n", ob[i]);
				if (! env->query("on_fight"))
					ob[i]->kill_ob(me);
			} else
			if (ob[i]->is_bad())
			{
				message_vision(random(2) ? "$N������Ц����$n�����ɵúã��ɵúá�\n" :
							   "$Nƴ�����ƣ���$n�����ֵܼ��͸ɰ���",
					       ob[i], me);
			}
			continue;
		}

		if (me->is_not_good())
			continue;

		if (ob[i]->query("shen") > 10000 && ! userp(ob[i]))
		{
			message_vision(random(2) ? "$N�޵����ý����ý���\n" :
						   "$N̾�������˽�������������˰���\n",
				       ob[i]);
		} else
		if (ob[i]->query("shen") < -10 && ! userp(ob[i]))
		{
			int ob_exp, my_exp;
			ob_exp = ob[i]->query("combat_exp");
			my_exp = me->query("combat_exp");
			if (ob_exp > my_exp * 2 || ob_exp > 1500000)
			{
				message_vision(random(2) ? "$N��$n���������������������ǰ��Ū��\n" :
							   "$Nһ����Ц����$n��������Ϊ����˭�������᣿����������\n",
					       ob[i], me);
			} else
			if (ob_exp > 20000)
			{
				message_vision(random(2) ? "$N��ɫ��Щ���Ծ���\n" :
							   "$N¶�����µ���ɫ��\n",
					       ob[i]);
				if (env->query("no_fight"))
					continue;
				message_vision(random(2) ? "$Nŭ��һ��������Ҷ���Ҫ���ˣ���\n" :
							   "$Nһ�Բ�������������$n�����μ��졣\n",
					       ob[i], me);
				ob[i]->kill_ob(me);
			} else
			{
				message_vision(random(2) ? "$N��ͨһ����̱���ڵأ�˫�ּ�ҡ�����������ң���Ĳ����ң���\n" :
							   "$Nһ�����£����Ͱ͵�ʲôҲ˵��������\n",
					       ob[i], me);
				if (! env->query("no_fight"))
					ob[i]->unconcious();
			}
		}
	}
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int n;
	int my_exp, ob_exp;

	if (me->is_bad() || victim->is_good())
		return - damage_bonus / 2;

	if (me->is_not_good() || victim->is_not_bad())
		return 0;

	if (me->query_skill_mapped("sword") != "taiji-jian" ||
	    me->query_skill("taiji-jian", 1) < 100)
		// only increase damage
		return damage_bonus / 2;

	switch (random(4))
	{
	case 0:
		if (! victim->is_busy())
			victim->start_busy(me->query_skill("sword") / 10 + 2);
		return HIC "$N��ǰһ�������е�" NOR+HIY "���佣" NOR+HIC "�û�������ԲȦ��"
		       "��$n��ȥ������ϸ��֮����$n���һ\n"
		       "������֪��εֵ���ֻ���������ˡ�"NOR"\n";

	case 1:
		n = me->query_skill("sowrd");
		victim->receive_damage("qi", n, me);
		victim->receive_wound("qi", n, me);
		n = me->query("eff_jing");
		n /= 2;
		victim->receive_damage("jing", n, me);
		victim->receive_wound("jing", n / 2, me);
		return random(2) ? HIY "$Nһ�����������е����佣����һ�����磬��ৡ���ɨ��$n��"NOR"\n":
				   HIY "$NͻȻ�����ȵ�����аħ������������������������佣"
				   HIY "����һ����$n��ʱ������ǰһ����"NOR"\n";
	}

	// double effect
	return damage_bonus;
}

void start_borrowing()
{
	remove_call_out("return_to_zhang");
	call_out("return_to_zhang", 7200 + random(600));
}

void return_to_zhang()
{
	object me;

	me = environment();
	if (! objectp(me))
		return;

	while (objectp(environment(me)) && ! playerp(me))
		me = environment(me);
 
	if (playerp(me))
	{
		if (me->is_fighting())
		{
			call_out("return_to_zhang", 1);
			return;
		}

		message_vision("��Ȼһ���䵱�������˹���������$N��æ�к������������������������û�"
			       "���佣�������ڲ�����ô����\n"
			       "$N���������ˣ����ˣ�����û�ȥ�ɡ���\n"
			       "$N���������䵱���Ӵ��ߡ�\n", me);
	} else
	{
		message("vision", "��Ȼһ���䵱�������˹������������佣��̾�˿�����ҡҡͷ���ˡ�\n",
			me);
	}

	destruct(this_object());
}
