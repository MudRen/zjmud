// force.c

#include <ansi.h>

inherit SKILL;

int valid_learn(object me)
{
    	if ((int)me->query_skill("force", 1) < 10)
		return notify_fail("��Ļ����ڹ���򲻹�������ѧϰ�����ڹ���\n");

    	return 1;
}

// hit effect called by combatd
mixed force_hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int damage;
	int me_fac;
	int victim_fac;
	int f;
	int m_lvl;
	int v_lvl;
	string skill;
	mixed result;

	skill = victim->query_skill_mapped("force");
	if (stringp(skill))
	{
		if (result = SKILL_D(skill)->valid_damage(me, victim, damage_bonus))
			return result;
	}

	me_fac = (int)me->query("neili");
	if (me_fac > (int)me->query("max_neili"))
		me_fac = (int)me->query("max_neili");

	victim_fac = (int)victim->query("neili");
	if (victim_fac > (int)victim->query("max_neili"))
		victim_fac = (int)victim->query("max_neili");

	if ((int)me->query("combat_exp") < (int)victim->query("combat_exp") * 20)
		me->add("neili", -factor);

	damage = me_fac / 20 + factor - victim_fac / 24;

	if (damage < 0)
	{
		v_lvl = victim->query_skill("force");
		m_lvl = me->query_skill("force");
		if (! me->query_temp("weapon") &&
		    m_lvl + random(m_lvl / 3) < v_lvl)
		{
			result = ([ "damage" : damage * 2 ]);
			damage = -damage;
			me->receive_damage("qi", damage * 4, victim);
			me->receive_wound("qi", damage * 4, victim);
			if (damage < 10)
				result += ([ "msg" : HIY "$N" HIY "�ܵ�$n"
						     HIY "�����������ƺ�һ����"NOR"\n" ]);
			else if (damage < 20)
				result += ([ "msg" : YEL "$N" YEL "��$n"
						     YEL "���������𣬡��١���һ������������"NOR"\n" ]);
			else if (damage < 40)
				result += ([ "msg" : HIC "$N" HIC "��$n"
						     HIC "������һ���ؿ������ܵ�һ���ش�����������������"NOR"\n" ]);
			else if (damage < 80)
				result += ([ "msg" : HIR "$N" HIR "��$n"
						     HIR "������һ����ǰһ�ڣ��������ɳ�������"NOR"\n" ]);
			else
				result += ([ "msg" : RED "$N" RED "��$n"
						     RED "������һ��ֻ�����������ϣ���Ѫ�������������˹�ȥ��"NOR"\n" ]);
			return result;
		}

		return 0;
	}

	damage -= victim->query_temp("apply/armor_vs_force");
	if (damage_bonus + damage < 0)
		return - damage_bonus;
	if ((f = random(me->query_skill("force"))) < damage)
		return f;

	return damage;
}

int shaolin_check(object me)
{
	int lvl;
	int n, d;
	mapping skmap;
	string sk;

	if (! userp(me))
		// only user does effect
		return 0;

	n = 0;
	skmap = me->query_skills();
	if (! skmap || ! sizeof(skmap))
		return 0;

	foreach (sk in keys(skmap))
	{
		if (! SKILL_D(sk)->is_shaolin_skill())
			continue;

		if (SKILL_D(sk)->valid_enable("force") &&
		    me->query_skill_mapped("force") != sk)
			continue;

		d = skmap[sk];
		if (d > 240) d = (d - 240) / 2 + 240;

		n += d * d / 100 * d;
	}

	if (n < 10000) return 0;
	lvl = me->query_skill("buddhism", 1);
	lvl *= lvl * lvl / 25;
	if (me->query("family/family_name") == "������")
		lvl += lvl / 2;
	if (lvl < n * 9 / 10)
	{
		write(RED "��ֻ��������һ���ʹ����ȫ�޷�������Ϣ����"
		      "��ס���һ�����ƶ���ĺ����乶��¡�"NOR"\n");
		message("vision", RED + me->name() + RED "��Ȼ���һ����"
			"�ƶ���ĺ����乶��£�������ʹ��֮����"NOR"\n",
			environment(me), ({ me }));
		me->receive_damage("jing", 200 + random(200));
		me->receive_damage("qi", 400 + random(400));
		return 1;
	} else
	if (lvl < n)
	{
		write(HIR "��ֻ������Ϣһ�����ң���֫�ٺ���ʱ���䣬��"
		      "��ü�������������Ĳ�����"NOR"\n");
		message("vision", HIR + me->name() + RED "������ס��"
			"��������ü������΢΢������"NOR"\n",
			environment(me), ({ me }));
		me->receive_damage("jing", 100 + random(100));
		me->receive_damage("qi", 200 + random(200));
		return 1;
	} else
	if (lvl < n * 11 / 10)
	{
		write(HIY "������е��ķ����ң�������������"
		      "�٣�����������Щ���ѡ�"NOR"\n");
	} else
	if (lvl < n * 13 / 10)
	{
		write(HIC "�������е������ĸо���"NOR"\n");
	}
	return 0;
}

int hatred_check(object me)
{
	int hatred;
	int force;
	int i;

	hatred = me->query("total_hatred");
	force = me->query_skill("force");
	if (hatred < 3 * force)
		return 0;
	else
	if (hatred < 4 * force)
		write(HIY "��ֻ������Ѫ����������֮�������嵴��"NOR"\n");
	else
	if (hatred < 5 * force)
		write(HIR "��ֻ����Ѫ�����ţ�����ɱ������������һʱ�̲�סֻ����������"NOR"\n");
	else
	if (hatred < 6 * force)
	{
		write(HIR "����ͷһʹ����Ϣ�������Ʋ�ס��ֻ������ǰ������ð��"NOR"\n");
		return 1;
	} else
	{
		write(RED "һʱ����ֻ����ɱ���󳤣��������գ��������³嵴���������������\n"
			  "��ҡҡ�λ�ǿ֧Ƭ�̣�ɤ��һ����ǰ��ʱ����һ�ڣ������ˡ�һ�µ��ڵ��ϡ�"NOR"\n");
		me->unconcious();
		call_out("do_owner_die", 0, me);
		return 1;
	}

	return 0;
}

void do_owner_die(object me)
{
	mapping sk;
	string skill;

	if (! objectp(me))
		return;

	me->receive_damage("qi", 1);
	sk = me->query_skills();
	foreach (skill in keys(sk))
	{
		if (! SKILL_D(skill)->valid_enable("force") ||
		    skill == "force")
			continue;
		if (sk[skill] > 50)
			sk[skill] /= 2;
	}

	if (me->query("max_neili") > 500)
		me->set("max_neili", me->query("max_neili") / 2);

	me->set_temp("die_reason", "ɱ¾̫�أ��������Ķ���");
	me->die();
	me->set("total_hatred", me->query("total_hatred") / 2);
}

varargs mapping query_pfm(string type)
{
	// ��ѯ���ܵ� pfm ���
	string dir,filename;
	string  *all_file;
	int i,l;
	mapping pfms;

	dir = file_name(this_object())+"/";
	pfms = ([]);

	if (file_size(dir + "exert/") == -2)
	{
		all_file = list_dirs(dir + "exert/");
		if (sizeof(all_file))
		{
			for (i = 0; i < sizeof(all_file); i++)
			{
				filename = all_file[i];
				l = strlen(filename);
				if (filename[l - 1] == 'c' && filename[l - 2] == '.')
					filename = filename[0..l - 3];

				if(type&&(dir + "exert/"+filename)->pfm_type()
					&&member_array(type,(dir + "exert/"+filename)->pfm_type())==-1)
					continue;

				if((dir + "exert/"+filename)->query_name())
					pfms[filename] = (dir + "exert/"+filename)->query_name()+":exert";
				else
					pfms[filename] = filename+":exert";
			}
		}
		all_file = list_dirs(dir + "perform/");
		if (sizeof(all_file))
		{
			for (i = 0; i < sizeof(all_file); i++)
			{
				filename = all_file[i];
				l = strlen(filename);
				if (filename[l - 1] == 'c' && filename[l - 2] == '.')
					filename = filename[0..l - 3];

				if(type&&(dir + "perform/"+filename)->pfm_type()
					&&member_array(type,(dir + "perform/"+filename)->pfm_type())==-1)
					continue;

				if((dir + "perform/"+filename)->query_name())
					pfms[filename] = (dir + "perform/"+filename)->query_name()+":perform";
				else
					pfms[filename] = filename+":perform";
			}
		}
	}
	else if (file_size(dir) == -2)
	{
		all_file = list_dirs(dir);
		if (sizeof(all_file))
		{
			for (i = 0; i < sizeof(all_file); i++)
			{
				filename = all_file[i];
				l = strlen(filename);
				if (filename[l - 1] == 'c' && filename[l - 2] == '.')
					filename = filename[0..l - 3];

				if(type&&(dir + filename)->pfm_type()
					&&member_array(type,(dir + filename)->pfm_type())==-1)
					continue;

				if((dir+filename)->query_name())
					pfms[filename] = (dir+filename)->query_name()+":exert";
				else
					pfms[filename] = filename+":exert";
			}
		}
	}
	return pfms;
}

// can I exercise force?
int do_effect(object me)
{
	return shaolin_check(me) || hatred_check(me);
}
