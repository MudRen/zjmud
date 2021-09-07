// Inherit: condiction:poison

#include <ansi.h>
#include <condition.h>

// Notify here:
// If someone try to dispel all condition, he must dispel
// one by one.
// If the dispel function of a condition was null, then
// the condition will be ignore from dispel, BUT, IF THE
// DISPEL FUNCTION RETURN BY ONE, the object will stop
// to dispel next condition.
// Or, the condition may not ill or poison, only for other
// purpose, so the dispel function of the condition should
// return by -1 to indicate it.

// Here is the base of poison-condition. If you want to
// design a non-poison condition, just don't inherit me.

// -----------------------------------------------------------

// Some creature may be poison, or some drug, medice, when
// other one has been ... So the caller doesn't want to call
// 'apply_condition' but do_effect.

// Description of the poison:
// level : the poison's level, refer the force skill
// remain: how much poison left, -1 will be non-limit
// id    : who make this poison
// name  : the name of the poison, defulat:"nature poison"

string chinese_name() { return "��"; }

string update_msg_others()
{
	return HIG "$N" HIG "ʹ���������һ����"NOR"\n";
}

string update_msg_self()
{
	return HIG "���е�$?" HIG "�����ˡ�"NOR"\n";
}

string die_msg_others()
{
	return RED "$N" RED "˻���Ž����������Ͳ��ٴ����ˡ�"NOR"\n";
}

mapping mixed_poison(mapping p1, mapping p2)
{
	mapping p;
	int r;

	if (! p1 && ! p2)
		return 0;

	p = allocate_mapping(4);

	// calculate the remain poison
	if (p1) r = (p1["remain"] ? p1["remain"] : (int)p1["level"] * (int)p1["duration"]);
	else    r = 0;

	if (p2) r += (p2["remain"] ? p2["remain"] : (int)p2["level"] * (int)p2["duration"]);

	if (! p2)
	{
		p["level"]  = p1["level"];
		p["id"]     = p1["id"];
		p["name"]   = p1["name"];
		p["remain"] = r;
		return p;
	}	

	if (! p1)
	{
		p["level"]  = p2["level"];
		p["id"]     = p2["id"];
		p["name"]   = p2["name"];
		p["remain"] = r;
		return p;
	}

	// generate the new id
	if (! p1["id"]) p1["id"] = p2["id"]; else
	if (! p2["id"]) p2["id"] = p1["id"];

	if (! p1["id"] || p1["id"] != p2["id"])
		// poison made by two man mixed
		p["id"] = "...";
	else
		p["id"] = p1["id"];

	// compare & decide the new level
	p["level"] = p1["level"];
	if (p["level"] < p2["level"])
		p["level"] = p2["level"];

	// generate the new poison name
	if (! p1["name"]) p1["name"] = p2["name"]; else
	if (! p2["name"]) p2["name"] = p1["name"];
	if (! p1["name"] || p1["name"] != p2["name"])
	{
		// two poison mixed
		if (p["level"] >= 100)
			p["name"] = "�綾";
		else
			p["name"] = "��";
	} else
		p["name"] = p1["name"];

	// decide the remain of poison
	p["remain"] = r;

	return p;
}

int do_effect(object ob, string cnd, mapping p)
{
	mapping cnd_info;
	int d;

	if (! p || ! intp(p["level"]) || ! intp(p["duration"]) ||
	    ! stringp(p["id"]))
		return 0;

	if (! stringp(p["name"])) p["name"] = this_object()->chinese_name();

	cnd_info = mixed_poison(ob->query_condition(cnd), p);
	ob->apply_condition(cnd, cnd_info);
	return 1;
}

int dispel(object me, object ob, mapping cnd)
{
	int my_lvl;
	int need_lvl;
	int cost_neili;
	int power;
	int dis;
	string pos;

	if (! cnd || ! intp(cnd["level"]) || ! intp(cnd["remain"]) ||
	    ! stringp(cnd["id"]))
		return 0;

	if (! stringp(cnd["name"]))
		cnd["name"] = "��";

	pos = cnd["name"];
	if (me->query("neili") < 200)
	{
		tell_object(me, "���������㣬�޷���ɢ" + pos + "��\n");
		return -1;
	}

	need_lvl = cnd["level"] + 10;
	if (ob->query("breakup"))
		need_lvl = need_lvl * 7 / 10;

	if (ob->query("immune/poison") == -1)
		need_lvl = 1;
	else
		need_lvl -= ob->query("immune/poison");
	if (need_lvl < 1) need_lvl = 1;

	if (me != ob)
		need_lvl += need_lvl / 5;

	if (cnd["id"] == me->query("id"))
		need_lvl = 50;

	my_lvl = me->query_skill("force") +
		 me->query_skill("poison") / 5 +
		 me->query_skill("dispel-poison", 1) +
		 me->query_temp("apply/dispel-poison");
	if (need_lvl > my_lvl)
	{
		if (me == ob)
		{
			tell_object(me, MAG "�������ڹ���ɢ" + pos +
				    "��Ȼ���ƺ�û�а��Ч����"NOR"\n");
			me->start_busy(1);
			return -1;
		} else
		{
			tell_object(me, MAG "�������ڹ�����" + ob->name() +
				    "��ɢ" + pos + "��Ȼ���ƺ�û�а��Ч����"
				    ""NOR"\n");
			tell_object(ob, MAG + me->name() + "��������������"
				    "����������������һ����ģ�����Ż�¡�"
				    ""NOR"\n");
			me->start_busy(1);
			if (! ob->is_busy())
				ob->start_busy(1);
			return -1;
		}
	}

	// ȥ������
	power = my_lvl + me->query_skill("dispel-poison", 1) +
		me->query_temp("apply/dispel-poison");
	if (ob->query("breakup"))
		power += power * 3 / 10;
	if (me == ob)
	{
		if (cnd["id"] == me->query("id"))
		{
			tell_object(me, WHT "�������ڹ�����" + pos +
				    "������ɢ��"NOR"\n");
			me->add("neili", -100);
			cnd["remain"] = 0;
			me->start_busy(1);
		} else
		{
			cost_neili = me->query("neili");
			dis = me->query("neili") * power / (cnd["level"] + 1) / 2;
			if (cnd["remain"] == -1)
				cnd["remain"] = 10000;
			if (dis >= cnd["remain"])
			{
				dis = cnd["remain"];
				cost_neili = cnd["remain"] * 2 * (cnd["level"] + 1) /
					     power;
				tell_object(me, WHT "�������ڹ�����" + pos +
					    "������ɢ��"NOR"\n");
			} else
			{
				tell_object(me, WHT "�������ڹ�����ɢ��һЩ" + pos +
					    "��"NOR"\n");
			}
			cnd["remain"] -= dis;
			if (cnd["remain"] < 0)
				cnd["remain"] = 0;
			me->add("neili", -cost_neili);
			me->start_busy(2 + random(2));
		}
	} else
	{
		if (cnd["id"] == me->query("id"))
		{
			tell_object(me, WHT "�������ڹ�������" + ob->name() +
				    "��" + pos + "������ɢ��"NOR"\n");
			me->add("neili", -150);
			cnd["remain"] = 0;
			me->start_busy(2);
			if (! ob->is_busy())
				ob->start_busy(1);
		} else
		{
			cost_neili = me->query("neili");
			dis = me->query("neili") * power / (cnd["level"] + 1) / 4;
			if (cnd["remain"] == -1)
				cnd["remain"] = 10000;
			if (dis >= cnd["remain"])
			{
				dis = cnd["remain"];
				cost_neili = cnd["remain"] * 4 * (cnd["level"] + 1) /
					     power;
				tell_object(me, WHT "�������ڹ�������" + ob->name() +
					    "��" + pos + "������ɢ��"NOR"\n");
			} else
			{
				tell_object(me, WHT "�������ڹ�������" + ob->name() +
					    "��ɢ��һЩ" + pos + "��"NOR"\n");
			}
			cnd["remain"] -= dis;
			if (cnd["remain"] < 0)
				cnd["remain"] = 0;
			me->add("neili", -cost_neili);
			me->start_busy(4 + random(4));
			if (! ob->is_busy())
				ob->start_busy(2 + random(2));
		}
	}

	if ( cnd["remain"] == 0)
		ob->clear_condition(this_object()->name());

	return 1;
}

// calucate the damage of jing per heart beaten
int jing_damage(object me, mapping cnd)
{
	int d;

	d = cnd["level"];

	if (d >= 64)
		d = 24 + (d - 64) / 8;
	else
	if (d >= 32)
		d = 16 + (d - 32 ) / 4;
	else
		d /= 2;
	if (d < 10) d = 10;

	return d / 2 + random(d);
}

// calucate the damage of qi per heart beaten
int qi_damage(object me, mapping cnd)
{
	int d;

	d = cnd["remain"];
	if(d<0) d = 0;
	d = cnd["level"]/2+sqrt(d)/2;

	return d;
}

// die reason
string die_reason(string name)
{
	if (! name || name == "��")
		return "����������";
	else
		return name + HIM "����������";
}

int update_condition(object me, mapping cnd)
{
	int jd;
	int qd;
	int jw;
	int qw;
	int improve;
	int kkk;

	if (! mapp(cnd) || me->query_temp("nopoison")) return 0;

	if (! intp(cnd["level"]) ||
	    ! intp(cnd["remain"] ||
	    ! stringp(cnd["id"])))
		return 0;

	jd = this_object()->jing_damage(me, cnd);
	qd = this_object()->qi_damage(me, cnd);

	if (! living(me) && (me->query("jing") < jd || me->query("qi") < qd))
	{
		me->set_temp("die_reason", die_reason(cnd["name"]));
		message_vision(die_msg_others(), me);
		me->die();
		return 1;
	}

	jw = jd / 2;
	qw = qd / 2;
	if (jw > me->query("eff_jing"))
	{
		jw = me->query("eff_jing");
		if (jw < 0) jw = 0;
	}

	if (qw > me->query("eff_qi"))
	{
		qw = me->query("eff_qi");
		if (qw < 0) qw = 0;
	}

	improve = (int)me->query("immune/poison");
	if (improve != -1)
	{
		me->receive_damage("jing", jd);
		me->receive_wound("jing",  jw);
		me->receive_damage("qi",   qd);
		me->receive_wound("qi",    qw);
	}
	tell_object(me, HIM "��"+cnd["name"]+"����������Ѫ - " + qd +  "������"+qw+"��"NOR"\n");
	tell_object(me, HIM "��"+cnd["name"]+"������������ - " + jd +  "������"+jw+"��"NOR"\n");

//	if (cnd["id"] == "nature poison" || improve == -1 || cnd["level"] / 2 + random(cnd["level"]) < (int)me->query_skill("force") + improve)
	if (1)
	{
		// ����������������
		if (improve == -1)
			cnd["remain"] = 0;
		else
			cnd["remain"] -= improve;

		kkk = me->query_skill("force");
		if(kkk<1) kkk = 1;

		if (cnd["remain"] <= kkk)
		{
			message("vision", HIM + me->name() + "��������"
				"��һ��������������ɫ�ö��ˡ�"NOR"\n",
				environment(me), ({ me }));
			tell_object(me, HIM "��������ϵ�" + cnd["name"] +
				    HIM "��ס�����ˣ��о��Ϻö��ˣ���"
				    "������������һ������"NOR"\n");
			return 0;
		}

		// ����ȥ��
		cnd["remain"] -= kkk;
		if(playerp(me))
			tell_object(me, HIM "����Ŀǰ���ڹ���Ϊ������ʣ�඾�ؽ���" + cnd["remain"]/kkk +  "�غ�֮�������"NOR"\n");
		me->apply_condition(this_object()->name(), cnd);
	}

	message("vision", replace_string(update_msg_others(), "$N",
			  me->name()), environment(me), ({ me }));
	tell_object(me, replace_string(update_msg_self(), "$?", cnd["name"]));

	return CND_NO_HEAL_UP | CND_CONTINUE;
}
