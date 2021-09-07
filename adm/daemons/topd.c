// topd.c ����������ҵ���������

#include <ansi.h>

#pragma optimize
#pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

static int ok = 0;


void clean_old()
{
	string *ids;
	int i;

	if(!dbase) return;
	ids = keys(dbase);
	for(i=0;i<sizeof(ids);i++)
	{
		if(time()-dbase[ids[i]]["last"] > 86400*30)
			delete(ids[i]);
	}
}

void create()
{
	seteuid(getuid());
	restore();
	set_heart_beat(30);
	clean_old();
}

void remove()
{
	save();
}

void mud_shutdown()
{
	save();
}

public string *all_users()
{
	if(!dbase)
		return 0;
	return keys(dbase);
}

public void map_user(object user)
{
	string name;
	mapping info;
	int i;

	info = ([]);
	name = user->query("id");
	info["balance"] = user->query("balance");
	info["name"] = user->query("name");
	info["per"] = user->query("per");
	info["all_pay"] = user->query("zjvip/all_pay");
	info["yuanbao"] = user->query("yuanbao");
	info["PKS"] = user->query("combat/PKS");
	info["daoshi_exp"] = user->query("zjvip/daoshi_exp");
	info["dizi_fanli"] = user->query("zjvip/dizi_fanli");
	info["combat_exp"] = user->query("combat_exp");
	info["gold"] = MONEY_D->player_carry(user);
	info["last"] = time();
	info["s_last"] = user->query("shimen/last");
	if(!same_week(info["s_last"],info["last"]))
		user->set("shimen/today",0);
	if(i=user->query("shimen/today")) info["shimen"]=i;
	else info["shimen"]=0;
	set(name,info);
}

public void add_shimen(object user)
{
	string name;
	mapping info;

	if( !mapp(dbase ) ) return;
	name = user->query("id");
	if(undefinedp(dbase[name])) return;
	info = dbase[name];
	if(undefinedp(info["shimen"])) info["shimen"]=1;
	else info["shimen"]+=1;
	set(name,info);
}

public void clear_shimen()
{
	string *names;
	int i;

	if( !mapp(dbase ) ) return;
	names = keys(dbase);
	for(i=0;i<sizeof(names);i++)
	{
		set(names[i]+"/shimen",0);
	}
}

mixed set_user(string prop, mixed data)
{
	if( !mapp(dbase ) ) dbase = ([]);

	if( strsrch(prop, '/')!=-1 )
		return _set( dbase , explode(prop, "/"), data );

	dbase[prop] = data;
	return 1;
}

mixed query_user(string prop)
{
	mixed data;

	if( !mapp(dbase) ) return 0;

	if( undefinedp(dbase[prop]) && (strsrch(prop, '/')!=-1) )
		data = _query(dbase, explode(prop, "/"));
	else
	{
		data = dbase[prop];
	}

	return data;
}

string get_name(string id)
{
	string data;

	if( !mapp(dbase) ) return 0;

	if( undefinedp(dbase[id]) )
		data = "������";
	else
	{
		data = dbase[id]["name"];
	}

	return data;
}
void heart_beat()
{
	int GMT = time() + localtime(0)[8];
	string d, times;
	int h, s;

	times = ctime(GMT);
	//Sun(������) Mon(����һ)  Tue(���ڶ�)  Wed(������)  Thu(������)  Fri(������)  Sat(������)
	d = times[0..2];//����
	h = to_int(times[10..12]);//ʱ
	s = to_int(times[14..15]);//��

	if ((d == "Mon") &&(h == 0) &&(s == 0) && !ok) {
		clear_shimen();
		ok = 1;
	} else if (s!=0)
		ok = 0;
	if(s/10==0) save();
}

string query_save_file() { return DATA_DIR "topd"; }
