// user.c

#include <origin.h>
#include <user.h>
#include <ansi.h>
#include <command.h>

inherit CHARACTER;
inherit F_AUTOLOAD;
inherit F_SAVE;

// ��������
private int die_protect(object ob);
private void cancle_die_protect(object ob);

// ��վʹ��
static int admin_flag = 0;	      // �Ƿ�������Ĺ���Ա��

// �����Ƿ�������
static int user_cracked = 0;	    // RESTORE ʱ������ݲ����øñ�־

static int net_dead;		    // ��־���Ƿ�Ͽ�������
static int last_age_set = 0;	    // ��һ�θ���AGE��ʱ��
static int user_say = 0;		// һ��ʱ�������������say-action
static int user_command = 0;	    // һ��ʱ��������ҷ��͵�����
static int attach_flag = 0;	     // �Ƿ����ں�ϵͳ����
int	at_time = 0;		 // ��ʲôʱ������
int	ban_to = 0;		  // ��ʲôʱ�������
string     ban_say_msg = "";	    // ��ֹ˵������Ϣ

static string my_defeater_id;	   // ��һ�δ��������ID
static string my_killer_id;	     // ��һ��ɱ����˵�ID
static int    craze = 0;		// ��ŭ

#define DEFAULT_PRISON	  "/d/register/prison"

// globals variables
string  prison = 0;
int     time_to_leave = 0;

int	is_stay_in_room()	{ return 1; }
int     is_player()		{ return clonep(); }
string  query_prison()	  { return prison; }
int     query_time_to_leave()   { return time_to_leave; }
int     is_in_prison()	  { return stringp(prison); }
int     is_net_dead()	   { return net_dead || ! interactive(this_object()); }

varargs string calc_sec_id(int raw);

#define MAX_COMMAND_ONE_SECTION	 30
#define MAX_SAY_ONE_SECTION	     4
#define BAN_SAY_PERIOD		  60

int query_current_neili_limit();
int query_neili_limit();
int query_current_jingli_limit();
int query_jingli_limit();
int query_potential_limit();
int query_experience_limit();

int is_user() { return 1; }

// �ж��Ƿ���й���Ȩ�ޣ�����ǰ汾����վ�����ͨ�� PASSWD
// �������ù�������й���Ȩ�ޡ����и�Ȩ�޵���ʦ����ʹ������
// clone��call��log��smash��copyskill�����
int is_admin()  { return admin_flag == 1222; }
int set_admin() { if (previous_object() == find_object("/cmds/usr/passwd")) admin_flag = 1222; }

void create()
{
	::create();
	set_name("ʹ�������", ({ "user object", "user", "object" }) );
}

void terminal_type(string term_type)
{
	set_temp("terminal_type", term_type);
	message("system", "�ն˻���̬�趨Ϊ " + term_type + "��\n", this_object());
}

void reset()
{
	int lv;

	if ((int)query("potential") - (int)query("learned_points") < 100)
		add("potential", 1);

	if ((int)query("thief") > 0)
		add("thief", -1);

	if ((int)query("total_hatred") > 0)
		add("total_hatred", -1);

	if ((lv = query_skill("xiantian-gong", 1)) >= 60 ||
	    (lv = query_skill("quanzhen-xinfa", 1)) >= 60)
	{
		if (can_improve_skill("force"))
			improve_skill("force", lv * 20);

		if (query_skill("quanzhen-xinfa", 1) >= 60 &&
		    can_improve_skill("quanzhen-xinfa"))
			improve_skill("quanzhen-xinfa", lv * 10);

		if (query_skill("xiantian-gong", 1) >= 60 &&
		    can_improve_skill("xiantian-gong") &&
		    SKILL_D("xiantian-gong")->valid_learn(this_object()))
			improve_skill("xiantian-gong", lv * 10);
	}
}

// This is used by F_SAVE to determine the filename to save our data.
string query_save_file()
{
	string id;

	id = geteuid();
	if (! id) id = getuid();
	if (! stringp(id)) return 0;
	return sprintf(DATA_DIR "user/%c/%s", id[0], id);
}

// override set function
mixed set(string idx, mixed para)
{
	if (idx == "name" && clonep(this_object()) &&
	    geteuid(this_object()))
	{
		NAME_D->change_name(this_object(), para, 1);
		return para;
	} else
		return ::set(idx, para);
}

int save()
{
	int res;

	if (user_cracked)
		// ���ݲ����������ܱ���
		return 1;

	if (query_temp("user_setup"))
	{
		save_autoload();
		set("sec_id", calc_sec_id());   // save sec_id
		res = ::save();
		clean_up_autoload();		// To save memory
	} else
	{
		set("sec_id", calc_sec_id());   // save sec_id
		res = ::save();
	}

#if INSTALL_EXAMINE
	EXAMINE_D->examine_player(me);
#endif
	return res;
}

int restore()
{
	int res;
	string sec_id;

	res = ::restore();
	if (res)
	{
/*
		if (stringp(sec_id = query("sec_id")))
		{
			if (crypt(calc_sec_id(1), sec_id) != sec_id)
			{
				// ���ݲ�����
				log_file("static/user",
					 sprintf("%s %s's data my be corrupt.\n",
						 log_time(), getuid()));
				user_cracked = 1;
				return 0;
			}
		} else
		{
			log_file("static/user",
				 sprintf("%s %s lost assure key.\n",
					 log_time(), getuid()));
			user_cracked = 1;
			return 0;
		}
*/
		// ��������
		user_cracked = 0;

		set("id", getuid(this_object()));
	}

	return res;
}

// This function updates player's age, called by heart_beat()
void update_age()
{
	int lastset;
	int age,month;
	int all,*lvs,delta,i;

	lvs = ({ 300, 1000, 2500, 4500, 6000, 10000, 15000, 25000, 50000, 999999999 });
	if( !(lastset=query("zjvip/last_vip_set"))) lastset=time();
	if(query("zjvip/times")>0)
	{
		all = query("zjvip/all_pay")+query("zjvip/sign_exp");
		for(i=0;i<sizeof(lvs);i++)
		{
			if(all < lvs[i])
			{
				set("zjvip/level",1+i);
				break;
			}
		}
		if(query("zjvip/level")>10) set("zjvip/level",10);
		add("zjvip/times", lastset - time());
		if(query("zjvip/times")<=0)
		{
			set("zjvip/times", 0);
			tell_object(this_object(),RED"���VIP��Աʱ���ѵ��ڣ�"NOR"\n");
		}
	}
	else
	{
		set("zjvip/times", 0);
	}
	set("zjvip/last_vip_set",time());

	if (! last_age_set)
	{
		last_age_set = time();
		add("mud_age", 0);
	}

	if ((delta = (time() - last_age_set)) > 100)
		// time too long
		delta = 100;

	if (! environment() || ! environment()->is_chat_room() || ! query("env/halt_age"))		
	{
		// Update age
		add("mud_age", delta);
		if (time_to_leave)
			time_to_leave -= delta;
	}

	last_age_set = time();
	age = query("age_modify") + query("mud_age") / 259200;
	age += 14;
	month = (query("mud_age")%259200)/21600;
	set("month",month);
        if (query("age") != age) {
		set("age", age);
		set("kar", 10+random(21));
		tell_object(this_object(), "ʱ�������죬��֪�������Ѿ�" + chinese_number(age) + "���ˣ������������֪����ô����\n");
	}
}

void setup()
{
	// We want set age first before new player got initialized with
	// random age.
	last_age_set = 0;
	update_age();

	::setup();

	// set the enable flag to enable save
	set_temp("user_setup", 1);

	restore_autoload();

	if (query("doing"))
		CLOSE_D->continue_doing(this_object());
}

void user_dump(int type)
{
	if (environment()&&environment()->query("close_room"))
		return;
	switch(type)
	{
	case DUMP_NET_DEAD:
		if (environment())
		{
			tell_room(environment(), query("name") + "���߳��� " + NET_DEAD_TIMEOUT / 60 + " ���ӣ��Զ��˳�������硣\n");
		}
		catch(command("halt"));
		catch(command("quit"));
		if (this_object())
		{
			QUIT_CMD->force_quit(this_object());
		}
		break;

	case DUMP_IDLE:
		if (query_temp("learned_idle_force"))
		{
			message_vision("$N��Ц���������������������ˣ�\n",
				       this_object());
			tell_object(this_object(), "�㾭����ʱ��ķ�"
				    "�������ڶԷ����񹦵����������һ�㣡\n");
			improve_skill("idle-force", 360000);
			delete_temp("learned_idle_force");
		} else
			tell_object(this_object(), "�Բ������Ѿ��������� " +
				    IDLE_TIMEOUT / 60 + " �����ˣ����´�������\n");
		if (environment())
		{
			tell_room(environment(), "һ��紵�����������е�" + query("name") +
				   "��Ϊһ�ѷɻң���ʧ�ˡ�\n", ({this_object()}));
		}
		command("quit");
		if (this_object() && ! query("doing"))
		{
			// command quit failed.
			QUIT_CMD->force_quit(this_object());
		}
		break;
	default:
		return;
	}
}

// net_dead: called by the gamedriver when an interactive player loses
// hir network connection to the mud.
private void net_dead()
{
	object link_ob;

	this_object()->remove_interactive();

	if (! query("doing")&&!(environment(this_object())&&environment(this_object())->query("close_room")))
		set_heart_beat(0);

	if (objectp(link_ob = query_temp("link_ob")))
	{
		if (link_ob->query_temp("ip_number"))
		{
			link_ob->set("last_on", time());
			link_ob->set("last_from",link_ob->query_temp("ip_number"));
			link_ob->save();
		}
		destruct(link_ob);
	}

	net_dead = 1;
	if (userp(this_object()) && ! query("doing")&&!(environment(this_object())&&environment(this_object())->query("close_room")))
	{
		call_out("user_dump", NET_DEAD_TIMEOUT, DUMP_NET_DEAD);
		tell_room(environment(), query("name") + "�����ˡ�\n", this_object());
		CHANNEL_D->do_channel(this_object(), "sys", "�����ˡ�");
		remove_all_enemy(1);
	} else
	{
		if (environment())
			message("vision", name() + "�����ˡ�\n",
				environment(), ({ this_object() }));
	}
}

// reconnect: called by the LOGIN_D when a netdead player reconnects.
void reconnect()
{
	set_heart_beat(1);
	net_dead = 0;
	remove_call_out("user_dump");
	tell_object(this_object(), "�������ӳɹ���\n");
}

// skill variable & function
#define MAX_NEILI_IMPROVE       query("con")
#define MAX_JINGLI_IMPROVE      query("con")

int query_neili_limit()
{
	string *skill_names;
	mapping skills;
	int neili_limit;
	int base_lvl, lvl;
	int tmp;
	int i;
	string fam;

	skills = this_object()->query_skills();
	if (! mapp(skills))
		return 0;

	skill_names = keys(skills);

	base_lvl = ((int) skills["force"]) / 2; 
	neili_limit = base_lvl * 10;
	for (i = 0; i < sizeof(skill_names); i++)
	{
		if (file_size(SKILL_D(skill_names[i]) + ".c") == -1)
		{
			// No such skill
			continue;
		}

		if (! SKILL_D(skill_names[i])->valid_enable("force"))
			continue;

		lvl = (int) skills[skill_names[i]];
		tmp = (base_lvl + lvl) * 10;
		tmp += (int) SKILL_D(skill_names[i])->query_neili_improve(this_object());
		if (tmp > neili_limit) neili_limit = tmp;
	}

	neili_limit += neili_limit * query("improve/neili") / 100;
	if (query("breakup"))
		neili_limit += neili_limit * 3 / 10;

	if (query("special_skill/mystery"))
		neili_limit += query("con") * 15;

	fam = query("family/family_name");
	if (query("class") == "bonze" &&
	    (fam == "ѩɽ��" || fam == "������" || fam == "������" || fam == "Ѫ����"))
		neili_limit += 500;

	return neili_limit;
}

int query_gain_qi()
{
	int gain_qi;
	gain_qi = query("gain/max_qi");
	if (query("special_skill/ghost"))
		gain_qi = gain_qi*7/10;
	if(query("family/family_name")=="�䵱��"||query("family/family_name")=="ȫ���")
		gain_qi += gain_qi/10;
	return gain_qi;
}

int query_gain_damage()
{
	int gain_damage;
	gain_damage= query("gain/damage");
	return gain_damage;
}

int query_gain_break()
{
	int gain_break;
	gain_break= query("gain/break");
	return gain_break;
}

int query_gain_armor()
{
	int gain_armor;
	gain_armor= query("gain/armor");
	return gain_armor;
}

int query_current_neili_limit()
{
	int neili;
	string force;
	string fam;

	force = query_skill_mapped("force");
	neili = (int)query_skill("force", 1) / 2 * 10;
	if (stringp(force) && force != "")
	{
		neili += (int)query_skill(force, 1) * 10;
		neili += SKILL_D(force)->query_neili_improve(this_object());
	}    

	neili += neili * query("improve/neili") / 100;
	if (query("breakup"))
		neili += neili * 3 / 10;

	if (query("special_skill/mystery"))
		neili += query("con") * 15;

	fam = query("family/family_name");
	if (query("class") == "bonze" &&
	    (fam == "ѩɽ��" || fam == "������" || fam == "������" || fam == "Ѫ����"))
		neili += 500;

	return neili;
}

int query_jingli_limit()
{
	int limit;

	limit = ((int)query("magic_points") / 30) + query("int") * 20;
	limit += limit * query("improve/jingli") / 100;
	if (query("animaout"))
		limit += limit * 3 / 10;
	return limit;
}

int query_current_jingli_limit()
{
	return query_jingli_limit();
}
//������߿�������Ǳ�ܼ���
int query_potential_limit()
{
	int p;

	if (ultrap(this_object()))//��ʦ
		p = 20000;
	else
		p = query_int() * 300;
	if(environment(this_object())&&environment(this_object())->query("close_room"))
		p *=2;
	return (int)query("learned_points") + p;
}
//ʵս��Ἣ��-������߿�������ʵս��Ἣ��
int query_experience_limit()
{
	int p;

	if (ultrap(this_object()))
		p = 10000;
	else
	{
		p = query("score");
		if (p < 100)
			p = p / 2;
		else
		if (p < 300)
			p = p / 4 + 25;
		else
		if (p < 1100)
			p = (p - 300) / 8 + 100;
		else
			p = (p - 1100) / 16 + 200;
		if (p > 8000)
			p = 8000;
	}
	return (int)query("learned_experience") + p;
}

int improve_potential(int n)
{
	int max;

	max = query_potential_limit() - query("potential");
	if (max <= 0)
	{
		tell_object(this_object(),"Ǳ���Ѵ����ޣ���ʱ�޷�����������\n");
		return 0;
	}
	if (n > max) n = max;
	add("potential", n);
	return n;
}

int improve_experience(int n)
{
	int max;

	max = query_potential_limit() - query("experience");
	if (max <= 0) return 0;
	if (n > max) n = max;
	add("experience", n);
	return n;
}

int can_improve_neili()
{
	return query("improve/neili") < MAX_NEILI_IMPROVE;
}

int can_improve_jingli()
{
	return query("improve/jingli") < MAX_NEILI_IMPROVE;
}

int improve_neili(int n)
{
	int delta;

	if ((delta = query_neili_limit() - query("max_neili")) <= 0)
		return 0;

	if (n > delta) n = delta;
	add("max_neili", n);
	 setup();
	return n;
}

int improve_jingli(int n)
{
	int delta;

	if ((delta = query_jingli_limit() - query("max_jingli")) <= 0)
		return 0;

	if (n > delta) n = delta;
	add("max_jingli", n);
	 setup();
	return n;
}

int accept_fight(object ob)
{
	if (query_temp("pending/fight") == ob)
		return 1;

	tell_object(this_object(), YEL "�����Ը��ͶԷ����б��ԣ�����Ҳ��" +
		    ob->name() + "("+ (string)ob->query("id")+")"+
		    "��һ�� fight ָ�"NOR"\n");

	tell_object(ob, YEL "���ڶԷ�������ҿ��Ƶ���������ȶԷ�ͬ���" +
	      "�ܽ��б��ԡ�"NOR"\n");

	return 0;
}

int accept_hit(object ob)
{
	if (! die_protect(ob))
		return 0;

	message_vision("$N��ȵ���" + ob->name() + "����Ҫ��ʲô��\n",
		       this_object(), ob);
	return 1;
}

int accept_kill(object ob)
{
	if (is_killing(ob->query("id")))
		return 1;

	if (! die_protect(ob))
		return -1;

	tell_object(this_object(), HIR "�����Ҫ��" + ob->name() +
		"�����ಫ������Ҳ�������(" + (string)ob->query("id") +
		")��һ�� kill ָ�"NOR"\n");
	return 1;
}

int accept_ansuan(object who)
{
	if (! die_protect(who))
		return 0;

	command(random(2) ? "say �ţ���ô..." : "say �������ã�");
	return 1;
}

int accept_touxi(object who)
{
	if (! die_protect(who))
		return -1;

	switch (random(2))
	{
	case 0:
		message_vision("$N���һ�����е����������" +
			       RANK_D->query_rude(who) + "���治Ҫ������\n",
			       this_object(), who);
		break;

	default:
		message_vision("$N�ֻ�֮�䣬����˵����ֻ�ý���$n"
			       "��һ�С�\n", this_object(), who);
		break;
	}

	return 1;
}

int die_protect(object ob)
{
	object me = this_object();

	// ֻ�����֮�������������
	if (! userp(me) || ! userp(ob))
		return 1;

	// �����˳��ﲻ������������
	if (me->query_temp("in_pkd"))
		return 1;

	// ȥ�������ߵ�����������Ϣ
	if (userp(me))
		cancle_die_protect(ob);

	// �������ߴ��ڱ���ʱ�ڣ�������ʧ��
	if (me->query("die_protect/last_dead") + me->query("die_protect/duration") > time()+7200)
	{
		message_vision("$N���ڱ�����ʱ�ڣ�$n���ܽ��й�����\n",me, ob);
		return 0;
	}

	return 1;
}

void cancle_die_protect(object ob)
{
	ob->delete("die_protect");
}

int auto_cmd()
{
	string *sss,str;
	object me;
	int i,max;
	me = this_object();

	if(!me->query("env/sign1")||!stringp(str = me->query("env/sign5"))) return 1;
	sss = explode(str,";");
	max = sizeof(sss);
	if(max>5) max = 5;
	for(i=0;i<max;i++)
	{
		me->force_me(sss[i]);
	}
	return 1;
}

int reject_command()
{
	int t;

	if (wizardp(this_object()))
		return 0;

	t = time() & 0xFFFFFFFE;
	if (at_time != t)
	{
		at_time = t;
		user_command = 1;
		user_say = 0;
	} else
		user_command++;

	if (user_command > MAX_COMMAND_ONE_SECTION)
	{
		user_command = 0;
		if (! query("born"))
			// not born yet
			return 0;
		return 1;
	}

	return 0;
}

void ban_say_until(int ban_period, string msg)
{
	int t;

	t = time();
	if (ban_to > t)
		ban_to += ban_period;
	else
		ban_to = t + ban_period;
	ban_say_msg = msg;
}

int ban_say(int raw)
{
	int t;

	if (wizardp(this_object()))
		return 0;

	if (is_in_prison())
	{
		notify_fail("��ʡʡ�ɣ��ú�������Σ������ڡ�\n");
		return 1;
	}

	t = time() & 0xFFFFFFFE;
	if (ban_to > t)
	{
		notify_fail(ban_say_msg + "������" +
			    appromix_time(ban_to - t) + "�Ժ��ٳ��ԡ�\n");
		return 1;
	}

	if (! raw)
		return 0;

	if (at_time != t)
	{
		at_time = t;
		user_say = 1;
		user_command  = 0;
	} else
		user_say++;

	if (user_say > MAX_SAY_ONE_SECTION)
	{
		ban_say_until(BAN_SAY_PERIOD, "ϵͳ��ֹ���ͳ���Ϣ");
		notify_fail(HIR "�����㷢������Ϣ̫�࣬���ϵͳ��ʱ"
			    "��ֹ�㷢����Ϣ��"NOR"\n");
		return 1;
	}

	return 0;
}

void permit_say(int n)
{
	if (ban_to <= time())
		return;

	if (! n)
		ban_to = 0;
	else
		ban_to -= n;

	if (ban_to <= time())
		tell_object(this_object(), "����Լ���������Ϣ�ˣ�\n");
}

// thow the person into prison
void get_into_prison(object ob, string p, int time)
{
	object me;

	me = this_object();
	if (! p) p = prison;
	if (! p) p = DEFAULT_PRISON;

	if (prison && base_name(environment()) == p)
	{
		time_to_leave += time * 60;
		if (ob && time)
			CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
				"��˵" + query("name") + "�����ڱ�" +
				ob->query("name") + "�ӳ���" +
				appromix_time(time * 60) + "��");
		return;
	}

	if (prison && prison == p && base_name(environment()) != prison)
	{
		p->catch_back(me);
		me->set("startroom", prison);
		me->move(prison);
		message_vision("��ž����һ����$N�ݺݵ�ˤ���˵��ϡ�\n", me);
		if (living(me))
			me->enable_player();

		CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
			"��˵" + query("name") + "Խ��Ǳ�ӣ������ץ"
			"��ȥ�ˡ�");

		save();
		return;
	}

	p->catch_ob(me);

	if (ob)
	{
		CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
			"��˵" + query("name") + "��" + ob->query("name") +
			"�ͽ���" + p->short() + HIM "������" +
			appromix_time(time * 60) + "��");
	}

	me->set("startroom", prison);
	me->move(p);
	prison = p;
	time_to_leave += time * 60;
	save();

	message_vision("��ž����һ����$N���ص�ˤ���˵��ϡ�\n", me);
	me->set("jing", 1);
	me->set("eff_jing", 1);
	me->set("qi", 1);
	me->set("eff_qi", 1);
	me->set("jingli", 0);
	me->set("neili", 0);
	me->receive_damage("jing", 0);
	if (living(me))
		me->enable_player();
}

// out of prison
void leave_prison(object ob, int time)
{
	object me;

	me = this_object();
	if (time)
	{
		time_to_leave -= time * 60;
		if (time_to_leave > 0)
		{
			if(ob)
				CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor","��˵" + query("name") + "�����ڱ�" +
					ob->query("name") + "������" + appromix_time(time * 60) + "��");
			else
				CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor","��˵" + query("name") + "�����ڱ�������" + appromix_time(time * 60) + "��");
			return;
		}
	}

	time_to_leave = 0;

	if (! prison->free_ob(me))
		return;

	prison = 0;

	if (living(me))
		me->enable_player();
	else
		me->revive();
	save();

	if (ob)
		CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
			"��˵" + query("name") + "��" + ob->name() +
			"��ǰ�ͷ��ˡ�");
	else
		CHANNEL_D->do_channel(find_object(MASTER_OB), "rumor",
			"��˵" + query("name") + "�Ѿ������ͷ��ˡ�");
}

varargs void die(object killer)
{
	if (prison)
	{
		set_temp("die_reason", "�����ڼ�����");
		clear_condition(0);
		receive_damage("qi", 0);
		if (living(this_object()))
			enable_player();
	}
	
	::die(killer);
	save();
}

void update_in_prison()
{
	object me;

	me = this_object();
	me->set("qi", 0);
	me->set("jing", 0);
	me->set("neili", 0);

	if (! living(me))
		return;

	if (time_to_leave > 0)
	{
		if (environment() && base_name(environment()) != prison)
		{
			// escape from prison?
			get_into_prison(0, 0, 0);
		}
		return;
	}

	leave_prison(0, 0);
}

int is_attach_system()
{
	return attach_flag;
}

// start attaching
int attach_system()
{
	attach_flag = 1;
}

// stop, deatched
int detach_system()
{
	attach_flag = 0;
}

string command_verb()
{
	return query_verb();
}

#define CRAZE_LIMIT_1   7000    // for ��������
#define CRAZE_LIMIT_2   5000    // for �ĺ�����

// ��ŭ��Ϣ
int query_craze() { return craze; }

// ���ķ�ŭ��Ϣ
int query_max_craze()
{
	switch (query("character"))
	{
	case "��������" :
		return CRAZE_LIMIT_1;

	case "�ĺ�����" :
		return CRAZE_LIMIT_2;
	default:
		return 0;
	}
}

// �����Ƿ������ŭ��״̬
int is_most_craze()
{
	return (craze > 0) && (craze >= query_max_craze());
}

// ��Ϊ���򵹶���ŭ
void craze_of_defeated(string defeater_id)
{
	my_defeater_id = defeater_id;
}

// ��Ϊ�����ж���ŭ
void craze_of_die(string killer_id)
{
	my_killer_id = killer_id;
	craze = query_max_craze();
}

// ��ŭ�Ĺ������ֺ������������������
void craze_defeated(string enemy_id)
{
	if (enemy_id == my_defeater_id)
		my_defeater_id = 0;

	if (enemy_id == my_killer_id)
		my_killer_id = 0;
}

// �Ƿ�����ĳ��
int is_hating(string enemy_id)
{
	if (enemy_id == my_defeater_id ||
	    enemy_id == my_killer_id)
		return 1;

	return 0;
}

// ������ŭ��������������Чֵ
int improve_craze(int amount)
{
	int limit;

	if (amount < 0)
		error("error: improve_craze amount to be less than 0\n");

	limit = query_max_craze();
	craze += amount;
	if (craze > limit)
	{
		amount += limit - craze;
		craze = limit;
	}
	return amount;
}

// ���ķ�ŭ���������ĵ���Чֵ
int cost_craze(int n)
{
	if (n < 0)
		error("error: improve_craze amount to be less than 0\n");

	if (n > craze)
	{
		n = craze;
		craze = 0;
	} else
		craze -= n;
	return n;
}

// �༭�ļ�
void edit_file(string file)
{
	ed(file);
}

int is_vip()
{
	return query("zjvip/times")>0;
}

// �Ƿ��ǽ���ֵܣ�
int is_brother(mixed ob)
{
	string id;

	if (stringp(ob))
		id = ob;
	else
	if (objectp(ob))
		id = ob->query("id");
	else
		return 0;

	// �Ƿ�����ͨ����ֵ�
	if (query("brothers/" + id))
		return 1;

	// �Ƿ��ǽ��˵��ֵ�
	return 0;
}

// �������������ݺ�
string calc_sec_id(int raw)
{
	mapping my;
	string *list;
	string key;
	int sum;
	string str;
	int i;

	sum = 0;

	// �ۼ����е�����
	if (mapp(my = query_entire_dbase()))
	{
		foreach (key in keys(my) - ({ "sec_id" }))
		{
			sum += sizeof(key);
			if (intp(my[key]))
				sum += my[key];
			else
				sum += sizeof(my[key]);
		}
	}
	
	// �ۼ����е��书����
	
	if (mapp(my = query_skills()))
	{
		foreach (key in keys(my))
		{
			sum += sizeof(key);
			if (intp(my[key]))
				sum += my[key];
			else
				sum += sizeof(my[key]);
		}
	}
	// �ۼ�����Я������Ʒ
	if (arrayp(list = query_autoload_info()))
	{
		foreach (key in list)
		{
			sum += sizeof(key);
			if (stringp(key))
				for (i = 0; i < strlen(key); i++) sum += key[i];
		}
	}

	// ת�����ַ���
	str = sprintf("%d", sum);
	str[0] = (sum % 26) + 'a';

	if (! raw) str = crypt(str, 0);
	return str;
}

string query_info()
{
	string msg;
	int dexp, dpot, dmar, dage, dquest, dt;

	if (wiz_level(this_object()) > 0)
		return 0;

	msg = "";
	if (query("chblk_on"))
	{
		if (stringp(query("chblk_by")))
			msg += "Ƶ���Ѿ��� " + query("chblk_by") + " �رա�\n";
		else
			msg += "Ƶ�����ر��С�\n";
	}

	dexp = query("combat_exp") - query("last_examine/combat_exp");
	dpot = query("potential") - query("last_examine/potential");
	dmar = query("experience") - query("last_examine/experience");
	dage = query("mud_age") - query("last_examine/mud_age");
	dquest = query("all_quest") - query("last_examine/all_quest");
	dt = time() - query("last_examine/time");
	if (dquest < 0) dquest += 1000;

	if (dt > 60)
	{
		msg += sprintf("���ϴμ�� %s ������\n"
			       "����ʱ�������� %s��\n"
			       "ʦ����������� %d ����\n"
			       "ƽ��ÿ���ӻ�þ����ٶȣ�%d\n"
			       "ƽ��ÿ���ӻ��Ǳ���ٶȣ�%d\n"
			       "ƽ��ÿ���ӻ������ٶȣ�%d\n",
			       appromix_time(dt),
			       appromix_time(dage),
			       dquest,
			       dexp * 60 / dt, dpot * 60 / dt, dmar * 60 /dt);
	}

	return msg;
}

