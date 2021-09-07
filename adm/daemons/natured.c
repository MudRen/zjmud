// natured.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <localtime.h>

#define REMEMBER_CHAR	   '#'
#define GAME_TIME(t)	    (t - 971000000)
#define DATE_SCALE	      365

static int current_day_phase = -1;
mapping *day_phase;

mapping *read_table(string file);

void select_day_phase();

mixed *query_localtime(int t)
{
	mixed *lt;

	t = GAME_TIME(t);
	if (t < 1) t = 1;
	lt = localtime((t % 86400) * 365);
	lt[LT_MON];
	lt[LT_YEAR] = t / 86400;
	return lt;
}

int query_hour()	{ return query_localtime(time())[LT_HOUR]; }
int query_day()	 { return query_localtime(time())[LT_MDAY]; }
int query_month()       { return query_localtime(time())[LT_MON] + 1; }
int query_year()	{ return query_localtime(time())[LT_YEAR]; }

void create()
{
	day_phase = read_table("/adm/etc/nature/day_phase");
	select_day_phase();
}

void update_day_phase()
{
	string msg;

	msg = color_filter(day_phase[current_day_phase]["outcolor"] +
			   day_phase[current_day_phase]["time_msg"] + ""NOR"\n");
	message("outdoor:vision", msg, all_interactive());
	if (! undefinedp(day_phase[current_day_phase]["event_fun"]))
		call_other(this_object(), day_phase[current_day_phase]["event_fun"]);
}

void select_day_phase()
{
	mixed *lt;
	int i, t, n;

	remove_call_out("select_day_phase");

	// Get minutes of today.
	lt = query_localtime(time());
	lt[LT_MON]++;
	t = lt[LT_HOUR];

	// Find the day phase for now.
	for (i = 0; i < sizeof(day_phase) - 1; i++)
		if (t < day_phase[i + 1]["hour"]) break;

	if (i >= sizeof(day_phase) - 1)
	{
		// the last hour
		n = 24 - t;
		i = 0;
	} else
		n = day_phase[i + 1]["hour"] - t;

	// calculate the call out time
	n = n * 60 - lt[LT_MIN];
	n = n * 60 / 365 + 1;
	if (n < 1) n = 1;
	call_out("select_day_phase", n);

	if (i != current_day_phase)
	{
		current_day_phase = i;
		update_day_phase();
	}
}

void event_midnight()
{
	string msg;
	int m, d;

	m = query_month();
	d = query_day();

	msg = 0;
	switch (m * 100 + d)
	{
	case  321:
		msg = HIG "�������ڵ��ˣ������������Ķ��������￪ʼ���ա�"NOR"\n";
		break;
	case  622:
		msg = HIR "���������ˣ�����Խ��Խ�ȣ����е����ﶼ�쳣��Ծ��"NOR"\n";
		break;
	case  923:
		msg = HIY "��Ȼ�������ˣ����һƬ��ƣ������ջ��ʱ�ڡ�"NOR"\n";
		break;
	case 1222:
		msg = HIW "���Ա����ĺ���ɨ����أ������ֿ�ʼ�˼ž������ߡ�"NOR"\n";
		break;
	}

	if (msg)
		message("vision", HIC "��������ʱ��" + msg,
			msg, all_interactive());

	switch(m)
	{
	//spring weather
	case 3: case 4: case 5:
		switch(random(3))
		{
		case 0:
			day_phase = read_table("/adm/etc/nature/spring_rain");
			break;
		case 1:
			day_phase = read_table("/adm/etc/nature/spring_sun");
			break;
		case 2:
			day_phase = read_table("/adm/etc/nature/spring_wind");
			break;
		}
		break;
	//summer weather
	case 6: case 7: case 8:
		switch(random(3))
		{
		case 0:
			day_phase = read_table("/adm/etc/nature/summer_rain");
			break;
		case 1:
			day_phase = read_table("/adm/etc/nature/summer_sun");
			break;
		case 2:
			day_phase = read_table("/adm/etc/nature/summer_wind");
			break;
	     }
	     break;
	//autumn weather
	case 9: case 10: case 11:
		switch(random(3))
		{
		case 0:
			day_phase = read_table("/adm/etc/nature/autumn_rain");
			break;
		case 1:
			day_phase = read_table("/adm/etc/nature/autumn_sun");
			break;
		case 2:
			day_phase = read_table("/adm/etc/nature/autumn_wind");
			break;
		}
		break;
	//winter weather
	case 12: case 1: case 2:
		switch(random(3))
		{
		case 0:
			day_phase = read_table("/adm/etc/nature/winter_rain");
			break;
		case 1:
			day_phase = read_table("/adm/etc/nature/winter_sun");
			break;
		case 2:
			day_phase = read_table("/adm/etc/nature/winter_wind");
			break;
		}
		break;
	default:
		day_phase = read_table("/adm/etc/nature/day_phase");
	}
}

// This is called everyday noon by update_day_phase, defined in the
// "event_fun" field in /adm/etc/nature/day_phase

void event_noon()
{
	object *ob;
	object env;
	int    ic;
	int    con;
	int    month;
	string ill, msg;
	int    i;

	if (random(4)) return;
	switch(month = query_month())
	{
	case 3: case 4: case 5:
		ill = "ill_kesou";
		msg = HIG + "��Ȼ��ͷһ���������о��ƺ�Ҫ�����ˡ�"NOR"\n";
		ic  = 5;
		break;
	case 6: case 7: case 8:
		ill = "ill_zhongshu";
		msg = HIG+"ͻȻ������֮��һ���ڣ��������ˡ�"NOR"\n";
		ic  = 5;
		break;
	case 9: case 10: case 11:
		ill = "ill_shanghan";
		msg = HIG+"��������˸���ս��ͷ������ģ�����˺����ˡ�"NOR"\n";
		ic  = 5;
		break;
	case 12: case 1: case 2:
		ill = "ill_dongshang";
		msg = HIG+"��֫��ĩ��һ��ֱ�������㱻�����ˡ�"NOR"\n";
		ic  = 0;
		break;
	}

	if (random(4) == 0)
	{
		ill = "ill_fashao";
		msg = HIG+"��ż�з纮����������������"NOR"\n";
	}

	ob = users();
	for (i = 0; i < sizeof(ob); i++)
	{
		if (! objectp(env = environment(ob[i]))) continue;
		if (! env->query("outdoors")) continue;
		if (! living(ob[i])) continue;
		con = ob[i]->query_con();
		con = con / 2 + random(con);
		switch (ill)
		{
		case "ill_shanghan":
		case "ill_dongshang":
			con += ob[i]->query_temp("apply/warm") +
			       env->query_temp("warm");
			break;

		case "ill_zhongshu":
			con -= ob[i]->query_temp("apply/warm") +
			       env->query_temp("warm");
			break;
		}

		if (con + ic < 25 )
		{
			ob[i]->apply_condition(ill, 30 - con);
			tell_object(ob[i], msg);
		}
	}
}

string outdoor_room_description()
{
	return color_filter(day_phase[current_day_phase]["outcolor"] + "    " +
			    day_phase[current_day_phase]["desc_msg"] + "��\n");
}

string game_time()
{
	mixed *lt;
	string *ms = ({ "��", "��", "��", "��", });

	lt = query_localtime(time());

	return sprintf("%s��%s%s��%s��%sʱ", 
		       chinese_number(lt[LT_YEAR]),
		       ms[((lt[LT_MON] + 1) % 12) / 3],
		       chinese_number(lt[LT_MON] + 1),
		       chinese_number(lt[LT_MDAY]),
		       chinese_number(lt[LT_HOUR]), );
}

int to_game_time(int t)
{
	return GAME_TIME(t);
}

mapping *read_table(string file)
{
	string *line, *field, *format;
	mapping *data;
	int i, rn, fn;

	line = explode(read_file(file), "\n");
	data = ({});
	for(i = 0; i < sizeof(line); i++)
	{
		if (line[i] == "" || line[i][0] == REMEMBER_CHAR) continue;
		if (! pointerp(field))
		{
			field = explode(line[i], ":");
			continue;
		}
		if (! pointerp(format))
		{
			format = explode(line[i], ":");
			continue;
		}
		break;
	}

	for( rn = 0, fn = 0; i < sizeof(line); i++)
	{
		if (line[i] == "" || line[i][0] == REMEMBER_CHAR ) continue;
		if (! fn) data += ({ allocate_mapping(sizeof(field)) });
		sscanf(line[i], format[fn], data[rn][field[fn]]);
		fn = (++fn) % sizeof(field);
		if (! fn) ++rn;
	}
	return data;
}

mapping *query_day_phase() { return day_phase; }
