// leagued.c

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

// ͬ�����������10��
#define MAX_LEAGUE_FAME	 1000000000

// ÿ��ͬ�������100������
#define MAX_HATRED_PERSON       100

// �����˳�����ʱ��ÿ���Ƴ����ٸ�
#define HATREDP_REMOVED	 10

mapping league_fame;
mapping last_league_fame;

// ͬ�˶Գ��˳�޶ȵ�����
private int sort_hatred(string id1, string id2, mapping hatred);

void create()
{
	seteuid(getuid());
	restore();
	set_heart_beat(1800 + random(30));
	if (! mapp(league_fame)) league_fame = ([ ]);
}

void remove()
{
	save();
}

public void mud_shutdown()
{
	save();
}

// ������ά��ͬ�˵�ͨ����Ϣ
private void heart_beat()
{
	int t;
	int last;
	string *all_fam;
	string fam;

	t = time();
	last = query("last_check");
	if ((t / 86400) != (last / 86400))
	{
		// ���������˱仯������ͬ�˵�������Ϣ
		all_fam = keys(league_fame) - ({ 0 });
		last_league_fame = ([ ]);

		foreach (fam in all_fam)
			last_league_fame[fam] = league_fame[fam];
	}
	set("last_check", t);

	// ����ͬ�˵�������Ϣ
	save();
}

// ����ͬ���������������Ϊ�գ�����mapping���ͣ�����������ͬ
// �˵������������������� �򷵻ظ��������ڵ��Ǹ�ͬ�˵���
// �������������ͬ�ˣ��򷵻ظ�ͬ�˵�������
public mixed query_league_fame(mixed ob)
{
	string fname;

	if (stringp(ob))
		return league_fame[ob];

	if (objectp(ob))
	{
		if (stringp(fname = ob->query("league/league_name")))
			return league_fame[fname];
		else
			return 0;
	}

	return league_fame;
}

// ��ѯ�����ͬ��������Ϣ
public mapping query_all_last_league_fame()
{
	if (! mapp(last_league_fame))
		// û���������Ϣ�����ؽ����
		return league_fame;

	// ���������ͬ��������Ϣ
	return last_league_fame;
}

// ��ѯͬ�˵ĳ����Ϣ�������ob������ͬ�˵����֣�Ҳ����ͬ��
// �е����
public mapping query_league_hatred(mixed ob)
{
	mapping hatred;
	string fname;

	if (objectp(ob))
		fname = ob->query("league/league_name");
	else
	if (stringp(ob))
		fname = ob;
	else
		fname = 0;

	if (! stringp(fname) || ! mapp(hatred = query(fname + "/hatred")))
		return 0;

	return hatred;
}

// �仯ͬ�������������ob������ͬ�˵����֣�Ҳ����ͬ���е���
// �
public void add_league_fame(mixed ob, int n)
{
	int new_fame;
	string fname;

	if (objectp(ob))
		fname = ob->query("league/league_name");
	else
	if (stringp(ob))
		fname = ob;
	else
		fname = 0;

	if (! stringp(fname) || undefinedp(query(fname + "/member")))
		return;

	// �����µ�ͬ������
	new_fame = league_fame[fname] + n;
	if (new_fame < 0) new_fame = 0;
	if (new_fame > MAX_LEAGUE_FAME)
		new_fame = MAX_LEAGUE_FAME;
	league_fame[fname] = new_fame;
}

// ͬ�˼��ɱ
public void league_kill(object killer, object victim)
{
	int kexp;
	int vexp;
	string vfam;
	string kfam;
	string kid;
	int fame_delta;
	mapping hatred;
	mixed *d;

	// ֻ�����֮��ĳ�ɱ�ż�������
	if (! objectp(killer) || ! playerp(killer) ||
	    ! objectp(victim) || ! playerp(victim))
		return;

	// ��ʦ֮��ıȻ��ɲ�������
	if (wizardp(killer) || wizardp(victim))
		return;

	// �鿴��������������Ľ���ͬ��
	kfam = killer->query("league/league_name");
	vfam = victim->query("league/league_name");

	if (killer->is_brother(victim) && killer->is_killing(victim->query("id")))
		// ɱ������ֵܣ���������10%
		killer->add("weiwang", -killer->query("weiwang") / 10);

	if (! stringp(kfam) && ! stringp(vfam))
		// ������ͬ���ڣ����ؼ�����
		return;

	kexp = killer->query("combat_exp");
	vexp = victim->query("combat_exp");

	if (kfam == vfam)
	{
		if (! killer->is_killing(victim->query("id")))
			// ʧ����ɱ���������
			return;

		// �ֵܼ��ɱ��������ᣬֱ�ӿ۳����˺͸���1/10������
		add_league_fame(kfam, -league_fame[kfam] / 10);
		killer->add("weiwang", -killer->query("weiwang") / 10);
		return;
	}

	if (kexp < vexp * 3 && vexp >= 100000)
	{
		// ɱ�ֵľ��鲻��ԶԶ�Ĵ��ڶԷ������ұ�ɱ��
		// ����һ���ľ��飬�⽫����ͬ�������Ľ��͡�
		fame_delta = vexp + killer->query("score") * 2 +
			     killer->query("weiwang") * 10;
		fame_delta /= 1000;
	} else
		// ���־���̫�٣����ǲ��̫�󣬲�Ӱ������
		fame_delta = 0;

	// �鿴ɱ�����ڵ�ͬ���Ƿ������ߣ������ޣ����ܹ�
	// ���������ı仯��
	if (stringp(kfam))
	{
		string path;

		path = kfam + "/hatred/"+ victim->query("id");
		d = query(path);
		if (arrayp(d) && sizeof(d) >= 2 && intp(d[1]))
		{
			// ������ߣ�ͬ�˻�ö��������
			if (d[1] > 2000)
				CHANNEL_D->do_channel(this_object(), "rumor",
					"��˵" + killer->name(1) + "������" +
					victim->name(1) + "��Ϊ" +
					kfam + "����һ�ڶ�����");
			fame_delta += d[1] / 3;

			// �Դ��˵ĳ�޽���(���͵�Ҫ�����ӵ�Ҫ��)��
			// ������Կ�fame_delta ���޶ȹ�˾�Ĳ���
			d[1] -= fame_delta;
			if (d[1] <= 0)
				delete(path);
			else
				set(path, d);
		}
	}

	// ��������ͬ�˵�����
	add_league_fame(killer,  fame_delta);
	add_league_fame(victim, -fame_delta);

	// ͳ�Ƹ�ɱ�ֶԱ��ŵĲк��̶�
	if (! stringp(vfam))
		return;

	// ��޳̶Ⱥ������ı仯������һ����������(K����)����
	// �ǳ�޳̶ȵ��������ı仯��
	vexp = vexp / 1000 + 1;
	if (vexp > 5000)
		vexp = (vexp - 5000) / 16 + 2000;
	else
	if (vexp > 1000)
		vexp = (vexp - 1000) / 4 + 1000;

	kid = killer->query("id");
	if (! mapp(hatred = query(vfam + "/hatred")))
	{
		set(vfam + "/hatred/" + kid,
		    ({ killer->name(), vexp }));
		return;
	}

	// ÿ��ͬ������¼���ɸ�����
	if (! undefinedp(d = hatred[kid]))
	{
		if (! arrayp(d) || sizeof(d) < 2 ||
		    ! intp(d[1]) || ! stringp(d[0]))
		{
			// ���ID�����ݳ��˹���
			d = 0;
		}
	} else
	if (sizeof(hatred) >= MAX_HATRED_PERSON)
	{
		string *ids;
		int i;

		// ����ȥ��һЩ�ˣ�Ϊʲô��ȥ��һ��������Ϊ
		// �˷�ֹ����Ƶ���Ľ��й��˲�����
		ids = sort_array(keys(hatred),
				 (: sort_hatred :), hatred);
		for (i = 0; i < sizeof(ids) && i < HATREDP_REMOVED; i++)
			map_delete(hatred, ids[i]);
	}

	if (! arrayp(d))
		d = ({ killer->name(1), vexp });
	else
	{
		d[0] = killer->name(1);
		d[1] += vexp;
	}

	// ��¼����˵���Ϣ
	hatred[kid] = d;
}

// ȥ������ͬ�˶�ĳ���˵ĳ����Ϣ
public void remove_hatred(string id)
{
	mapping dbase, league, hatred;
	string fam;

	if (! mapp(dbase = query_entire_dbase()))
		// ���ڻ�û�г����Ϣ
		return;

	// �������е�ͬ��
	foreach (fam in keys(dbase))
	{
		reset_eval_cost();

		if (! mapp(league = dbase[fam]))
			continue;

		if (mapp(hatred = league["hatred"]))
			// ȥ����ͬ�˶�ĳ�˵ĳ����Ϣ
			map_delete(hatred, id);

		if (! mapp(hatred) || sizeof(hatred) < 1)
			// ���ͬ���Ѿ�û�г����Ϣ
			map_delete(league, "hatred");
	}

	save();
}

// �鿴�Ƿ���Դ������ͬ��
public mixed valid_new_league(string fname)
{
	if (query(fname + "/member"))
		return "�˼�����н������������ͱ�������ˡ�\n";

	if (! undefinedp(FAMILY_D->query_family_fame(fname)))
		return "�������Ѿ���" + fname + "�ˣ��㻹����ʲô��\n";

	return 0;
}

// ����ͬ��
public void create_league(string fname, int base, object *obs)
{
	mapping league;
	string *channels;
	object ob;

	league_fame[fname] = base;
	if (! mapp(last_league_fame))
		last_league_fame = ([ fname : base ]);
	else
		last_league_fame[fname] = base;

	set(fname, ([ "member" : obs->query("id"),
		      "time"   : time() ]));
	save();

	foreach (ob in obs)
	{
		league = ([ "time" : time(),
			    "league_name" : fname ]);
		ob->set("league", league);
		channels = ob->query("channels");
		if (! arrayp(channels) || ! sizeof(channels))
			channels = ({ "inter" });
		else
		if (member_array("inter", channels) == -1)
			channels += ({ "inter" });

		ob->set("channels", channels);
		ob->save();
	}
}

// ��ɢͬ��
public void dismiss_league(string fname)
{
	string *ids;
	string id;

	// ���������Ϣ
	map_delete(league_fame, fname);
	if (mapp(last_league_fame)) map_delete(last_league_fame, fname);

	// ���ͬ���е�������ҵ������Ϣ
	ids = query(fname + "/member");

	if (arrayp(ids))
	{
		// ͬ���л�����ң�������ǵ���Ϣ
		foreach (id in ids)
		{
			// ������
			reset_eval_cost();
			UPDATE_D->clear_user_data(id, "league");
		}
	}

	// ���ͬ�˵�������Ϣ
	delete(fname);
}

// ��ѯͬ���еĵ���
public string *query_members(mixed ob)
{
	string *member;
	string fname;

	if (objectp(ob))
		fname = ob->query("league/league_name");
	else
	if (stringp(ob))
		fname = ob;
	else
		fname = 0;

	if (! stringp(fname) || ! arrayp(member = query(fname + "/member")))
		return 0;

	return member;
}

// ��ͬ����ȥ��һ����
public varargs void remove_member_from_league(mixed fname, string id)
{
	mapping league;
	string *member;

	if (objectp(fname))
	{
		// fname is user object
		id = fname->query("id");
		if (! stringp(fname = fname->query("league/league_name")))
			return;
	} else
	if (! stringp(fname))
		// or fname must be a league name
		return;

	if (! mapp(league = query(fname)) ||
	    ! arrayp(member = league["member"]))
		// no such league or no member in the league
		return 0;

	member -= ({ id, 0 });
	if (sizeof(member) < 1)
	{
		CHANNEL_D->do_channel(this_object(), "rumor",
			"��˵" + fname + "�˲ŵ��㣬���պ��Ѿ���ɢȥ���Ӵ˽������޴��ֺ��ˡ�");

		// ���������Ϣ
		map_delete(league_fame, fname);
		if (mapp(last_league_fame)) map_delete(last_league_fame, fname);

		// ���ͬ�˵���Ϣ
		delete(fname);
	} else
		league["member"] = member;
}

// ��ͬ��������һ����
public void add_member_into_league(string fname, string id)
{
	string *member;

	if (! arrayp(member = query(fname + "/member")))
		return 0;

	if (member_array(id, member) != -1)
		return 0;

	member += ({ id });
	set(fname + "/member", member);
}

// ��������
private int sort_hatred(string id1, string id2, mapping hatred)
{
	mixed *d1, *d2;

	if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
		return -1;

	if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
		return 1;

	return d1[1] - d2[1];
}

public string query_save_file() { return DATA_DIR "leagued"; }
