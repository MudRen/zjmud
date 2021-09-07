// lingshe.c ������
// by jeeny

#include <weapon.h>
#include <ansi.h>

inherit F_OBSAVE;
inherit STAFF;

string do_wield();
string do_unwield();

void create()
{
	set_name(HIW "������" NOR, ({ "lingshe zhang", "staff", "lingshe" }));
	set_weight(1500);
	if (clonep())
		destruct(this_object());
	else {
		set("long", @LONG
����һ������ë���Ȼ�ı��ȣ���������ŷ������ƾ����Ⱥͺ��߹���ս
���ٻغϡ���ͷ���Ÿ������Ц����ͷ����Ŀ�����������������ݣ���ι
�綾���趯ʱ��������˼��ɵ��������������ǲ����������������ߣ�
���������������ѷ���
LONG );
		set("unit", "��");
		set("value", 800000);
		set("no_sell", 1);
		set("du", 3) ;
		set("material", "steel");
		set("wield_msg", (: do_wield :));
		set("unwield_msg", (: do_unwield :));
		set("stable", 80);
	}
	init_staff(200);
	setup();
	restore();
}

string do_wield()
{
	object me;

	me = this_player();
	remove_call_out("check_npc");
	call_out("check_npc", 0, me, environment(me));
	if (me->query("shen") < -10000)
		return HIW "$Nһ����Х��ȡ��$n" HIW "��һʱ�䣬����ϮϮ��"NOR"\n";
	else
	if (me->query("shen") <= 0)
		return HIC "$Nһ���֣���Ȼ��$n" HIW "�������С�"NOR"\n";
	else
	if (me->query("shen") > 10000)
		return HIB "$N�߶����µ�����һ��$n" HIB "��"NOR"\n";
	else
		return HIB "$Nһ����Ц����ৡ���һ��������$n" HIB "��"NOR"\n";
}

string do_unwield()
{
	object me;

	me = this_player();
	remove_call_out("check_npc");
	if (me->query("shen") <= 0)
		return HIC "$Nһ���֣������������ȡ�"NOR"\n";
	else
	if (me->query("shen") > 10000)
		return HIG "$N��$n" HIG "�����������Ļ��������顱������ͣ��"NOR"\n";
	else
		return HIG "$Nһɹ����$n" HIG "������䡣"NOR"\n";
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
		    ob[i]->query("id") == "ouyang feng")
			continue;

		if (me->is_good())
		{
			if (userp(ob[i]))
				continue;

			if (ob[i]->query("shen") < -10000)
			{
				message_vision("$N��ŭ�ȵ��������" + RANK_D->query_rude(me) +
					       "����Ȼ�ҵ��������ȣ�\n", ob[i]);
				if (! env->query("on_fight"))
					ob[i]->kill_ob(me);
			} else
			if (ob[i]->is_good())
			{
				message_vision(random(2) ? "$N������Ц����$n�����ɵ�Ư������֮"
							   "���ߣ�Ҳ������̨������\n" :
							   "$Nƴ�����ƣ���$n�����ֵ���Ϊ������"
							   "һ�󹦰�",
					       ob[i], me);
			}
			continue;
		}

		if (me->is_not_bad())
			continue;

		if (ob[i]->query("shen") < -10000 && ! userp(ob[i]))
		{
			message_vision(random(2) ? "$N�޵������ȣ����ȣ�\n" :
						   "$N̾����Ҳ��֪ŷ���ֽ����ɺã�\n",
				       ob[i]);
		} else
		if (ob[i]->query("shen") > 10 && ! userp(ob[i]))
		{
			int ob_exp, my_exp;
			ob_exp = ob[i]->query("combat_exp");
			my_exp = me->query("combat_exp");
			if (ob_exp > my_exp * 2 || ob_exp > 1500000)
			{
				message_vision(random(2) ? "$N��$n���������������������ǰ��Ū��\n" :
							   "$Nһ����Ц����$n��������Ϊ����˭��ŷ"
							   "���壿����������\n",
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
				message_vision(random(2) ? "$N��ͨһ����̱���ڵأ�˫�ּ�ҡ"
							   "�����������ң���Ĳ����ң���\n" :
							   "$Nһ�����£����Ͱ͵�ʲôҲ˵"
							   "��������\n",
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

	if (me->is_good() || victim->is_bad())
		return - damage_bonus / 2;

	if (me->is_not_bad() || victim->is_not_good())
		return 0;

	if (me->query_skill_mapped("staff") != "lingshe-zhangfa" ||
	    me->query_skill("lingshe-zhangfa", 1) < 100)
		// only increase damage
		return damage_bonus / 2;

	switch (random(4))
	{
	case 0:
		if (! victim->is_busy())
			victim->start_busy(me->query_skill("staff") / 10 + 2);
		return HIB "$N��ǰһ�������е�" NOR+HIW "������" NOR+HIB "�����벻����"
		       "�Ƕ���$n��ȥ���ȷ������籩������ҡ�$n���һ\n"
		       "������֪��εֵ���ֻ���������ˡ�"NOR"\n";

	case 1:
		n = me->query_skill("staff");
		victim->receive_damage("qi", n, me);
		victim->receive_wound("qi", n, me);
		n = me->query("eff_jing");
		n /= 2;
		victim->receive_damage("jing", n, me);
		victim->receive_wound("jing", n / 2, me);
		return random(2) ? HIB "$Nһ�����������е������Ȼ���һ���׹⣬��ৡ���ɨ��$n��"NOR"\n":
				   HIB "$NͻȻ�����ȵ�����ʲô�������ɣ�����������������������"
				   HIB "����һ����$n��ʱ������ǰ������ǧ�����ߴܶ���"NOR"\n";
	}

	// double effect
	return damage_bonus;
}

void start_borrowing()
{
	remove_call_out("return_to_feng");
	call_out("return_to_feng", 7200 + random(600));
}

void return_to_feng()
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
			call_out("return_to_feng", 1);
			return;
		}

		message_vision("��Ȼһ��ŷ�����ҵĵ������˹���������$N��æ�к���������ʦү��"
			       "���������û������ȣ������ڲ�����ô����\n"
			       "$N���������ˣ����ˣ�����û�ȥ�ɡ���\n"
			       "$N���Ƚ���ŷ�����ҵ��Ӵ��ߡ�\n", me);
	} else
	{
		message("vision", "��Ȼһ��ŷ�����ҵ������˹��������������ȣ�̾�˿�����ҡҡ"
				  "ͷ���ˡ�\n", me);
	}

	destruct(this_object());
}

// ���б������ݵĽӿں���
mixed save_dbase_data()
{
	mapping data;

	data = ([ "du" : query("du") ]);


	return data;
}

// ���ܴ������ݵĽӿں���
int receive_dbase_data(mixed data)
{
	if (! mapp(data))
		return 0;

	if (! undefinedp(data["du"]))
	{
		set ("du", data["du"]);
	}

	return 1;
}

