// pkd.c

#include <ansi.h>
#include <localtime.h>

inherit F_DBASE;

#define ENTRY_ROOM      "/d/pk/entry"
#define READY_ROOM      "/d/pk/ready"
#define PK_ROOM	 "/d/pk/turen"

// the state of daemon
static int state;

#define SLEEPING	0
#define GET_READY       1
#define STARTING	2

#define GET_READY_TIME  300

static object *total = ({ });
static int ready_time = 0;

// �Ĵα����б�
static mapping *tlist = ({
([      "name" : "����������",
	"time" : ({ 2000, 2030, }),
	"exp"  : ({ 3000, 5000000 }),
	"last_day" : 0,
]),
([      "name" : "�߼�������",
	"time" : ({ 2100, 2130, }),
	"exp"  : ({ 3000, 2000000000 }),
	"last_day" : 0,
]),
});

static int selected;

private void change_state(int new_state);
private void init_player(object me);
private int  start_competition();
private void message_competition(string msg);
private void auto_check();
private void give_bouns(object me);
private void kickout_players();
private void restore_status(object me);
private void send_invite_message();

// �ⲿ�ɵ��õĺ���
int check_out(object me);

// return the time of prompt
int is_pking()	      { return state == STARTING; }
int is_ready()	      { return state == GET_READY; }

void create()
{
	seteuid(ROOT_UID);
	set("channel_id", "��������");
	write("���������Ѿ�������\n");
	state = SLEEPING;
	set_heart_beat(30);
}

int clean_up()
{
	return 1;
}

// join in competition
int join_competition(object ob)
{
	mapping cnd;

	if (state != SLEEPING)
		return notify_fail("�������˳����ھ��л���㻹�ǵȵ���˵�ɡ�\n");

	if (ob->query("combat_exp") < 3000)
		return notify_fail("����㱾�¾ͱ��ȥ����\n");

	if (mapp(cnd = ob->query_condition()) && sizeof(cnd))
	{
		if (! undefinedp(cnd["hunger"]))
			return notify_fail("�㻹�����ҵ�ԵĶ�����˵�ɡ�\n");

		if (! undefinedp(cnd["killer"]))
			return notify_fail("�ٸ�����ͨ���㣬�㻹���������ͷ¶�棿\n");

		if (! undefinedp(cnd["bandage"]))
			return notify_fail("�㻹�ǵȰ������˿�ֹס��Ѫ��˵�ɣ�\n");

		if (! undefinedp(cnd["putizi_drug"]))
			return notify_fail("��շ��������Ӳ��ã��ú��˹������ɰɣ�\n");

		if (! undefinedp(cnd["vote_clear"]))
			return notify_fail("����������ڶ�����б������𵽴����ߡ�\n");

		return notify_fail("������״̬���ѣ����Ǳ��ȥ�ˡ�\n");
	}

	if (! arrayp(total))
		total = ({ ob });
	else
	if (member_array(ob, total) == -1)
		total += ({ ob });

	message_competition((ultrap(ob) ? "����ʦ" : "") + ob->name(1) + "�������˳���");

	init_player(ob);
	set_heart_beat(1);
	return 1;
}

// scan
private void heart_beat()
{
	mixed lt;
	int ti;
	int i;
	int last_day;

	seteuid(ROOT_UID);
	lt = localtime(time());
	ti = lt[LT_HOUR] * 100 + lt[LT_MIN];

	switch (state)
	{
	case SLEEPING:
		last_day = time() / 86400;
		for (i = 0; i < sizeof(tlist); i++)
		{
			if (ti < tlist[i]["time"][0] || ti > tlist[i]["time"][1])
				// not change state
				continue;
			if (last_day == tlist[i]["last_day"])
				// this day has do it
				break;
			tlist[i]["last_day"] = last_day;
			selected = i;

			// chanage state to "GET_READY";
			change_state(GET_READY);
			break;
		}
		break;

	case GET_READY:
		if (time() < ready_time + GET_READY_TIME)
			break;

		// change state to "GET_READY_2";
		change_state(STARTING);
		break;

	case STARTING:
		break;
	}

	if (sizeof(total))
		auto_check();
}

// the daemon change to a new state
private void change_state(int new_state)
{
	mixed lt;
	int n;

	lt = localtime(time());
	switch (new_state)
	{
	case GET_READY:
		// kickout the player now in competition
		kickout_players();

		ready_time = time();
		message_competition("��˵һ��һ�ȵ�" + tlist[selected]["name"] + "���Ͼ�Ҫ�����ˣ���֪���������������˭��");
		set_heart_beat(1);
		send_invite_message();
		break;

	case STARTING:
		if (! (n = start_competition()))
		{
			message_competition("��˵�����" + tlist[selected]["name"] + "���ȡ���ˣ�����û����");
			new_state = SLEEPING;
		} else
		{
			message_competition("��˵�����" + tlist[selected]["name"] +
					    "������" + chinese_number(n) + "�����֣���...��������ȥ��");
			set_heart_beat(1);
		}
		break;

	default:
		total = ({ });
		break;
	}

	// change to new state
	state = new_state;
	if (state == SLEEPING)
		set_heart_beat(30);
	return;
}

// set player's override functions
private void init_player(object me)
{
	tell_object(me, HIY "����ǰ��Ȼһ��..."NOR"\n");
	me->set_override("unconcious", (: call_other, __FILE__, "check_out" :));
	me->set_override("die", (: call_other, __FILE__, "check_out" :));
	me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
	me->set_temp("backup/killer", me->query_killer());
	me->set_temp("backup/want", me->query_want());
	me->set_temp("in_pkd", 1);

	me->move(sprintf(PK_ROOM "%d", random(12) + 1));
	tell_object(me, HIY "�㶨��һ������ŷ����Լ��Ѿ�����" + environment(me)->short() + HIY "��\n");
	me->set("backup/condition", me->query_condition());
	me->clear_condition();
}

// kickout the players in competition when formal competition
// get ready
private void kickout_players()
{
	object ob;
	string room;
	mapping my;

	if (! arrayp(total))
		return;

	foreach (ob in total)
	{
		if (! objectp(ob))
			continue;
		room = base_name(environment(ob));
		if (! sscanf(room, PK_ROOM "%*s"))
			// not in pk room
			continue;

		my = ob->query_entire_dbase();
		my["eff_qi"] = my["max_qi"];
		my["eff_jing"] = my["max_jing"];
		my["qi"] = 1;
		my["jing"] = 1;

		tell_object(ob, HIC "\n���ϴ����˹��������µ������峡�ˣ��峡�ˣ������߰ɣ���"NOR"\n");

		restore_status(ob);
		ob->move(ENTRY_ROOM);
		message("vision", "ֻ��" + ob->name() + "�㬵����˳�����\n",	environment(ob), ({ ob }));
		if (! living(ob))
			ob->revive();
	}

	total = ({ });
}

private int start_competition()
{
	object env;
	object *obs;
	object shadow;
	int i;

	env = find_object(READY_ROOM);
	if (! objectp(env))
		return 0;

	obs = filter_array(all_inventory(env), (: userp($1) && ! wizardp($1) :));
	if (sizeof(obs) < 2)
		return 0;

	if (sizeof(obs) == 2)
	{
		if (obs[0]->query("couple/id") == obs[1]->query("id"))
		{
			message_vision("���ϴ������溰�����������Ƿ��������μӣ��������˰ɡ���\n", obs[0]);
			return 0;
		}
	}

	message("vision", "һ����Ӱ���˹����������ţ��������������ȥ�ɣ���\n", env);

	for (i = 0; i < sizeof(obs); i++)
	{
		reset_eval_cost();
		init_player(obs[i]);
	}

	set_heart_beat(1);
	message("vision", HIG "���˱����Ѿ���ʼ���춯�ְɣ�\n", obs);
	return sizeof(total = obs);
}

// send message out
private void message_competition(string msg)
{
	CHANNEL_D->do_channel(this_object(), "rumor", msg);
}

// check all the players who join the competition
private void auto_check()
{
	object ob;
	string msg;
	string room;
	object *lost;
	int i,pot,exp,jifen;

	lost = ({ });
	for (i = 0; i < sizeof(total); i++)
	{
		if (! objectp(total[i]))
			continue;
		room = base_name(environment(total[i]));
		if (! sscanf(room, PK_ROOM "%*s"))
		{
			// not in pk room
			restore_status(total[i]);
			total[i] = 0;
			continue;
		}
		if (total[i]->query("qi") < 1 || total[i]->query("jing") < 1)
			lost += ({ total[i] });
	}

	// kickout the players who lost competition
	foreach (ob in lost)
		check_out(ob);

	total -= ({ 0 });
	if (state == SLEEPING)
	{
		if (sizeof(total) < 1)
			// end of competition. call the change_state
			// function to restore the normal heart beat.
			change_state(SLEEPING);

		return;
	}

	if (state != STARTING)
		return;

	//�����θ�����ǰ5,3,2,1����4��
	if (sizeof(total) < 1)
	{
		msg = "��˵���˴������������������ӵ��ӣ�����һ���˶�û������";
	} else
	if (sizeof(total) == 5)
	{
		jifen = 30*(selected+1);
		for(i=0;i<sizeof(total);i++)
		{
			if(total[i]->query_temp("pkd_pot/5")) continue;
			total[i]->set_temp("pkd_pot/5",jifen);
			total[i]->add("pkd_pot",jifen);
			tell_object(total[i],"����뱾�δ���ǰ5ǿ�����"+jifen+"����֡�\n");
		}
		return;
	} else
	if (sizeof(total) == 3)
	{
		jifen = 30*(selected+1);
		for(i=0;i<sizeof(total);i++)
		{
			if(total[i]->query_temp("pkd_pot/3")) continue;
			total[i]->set_temp("pkd_pot/3",jifen);
			total[i]->add("pkd_pot",jifen);
			tell_object(total[i],"����뱾�δ���ǰ3ǿ�����"+jifen+"����֡�\n");
		}
		return;
	} else
	if (sizeof(total) == 2)
	{
		jifen = 30*(selected+1);
		for(i=0;i<sizeof(total);i++)
		{
			if(total[i]->query_temp("pkd_pot/2")) continue;
			total[i]->set_temp("pkd_pot/2",jifen);
			total[i]->add("pkd_pot",jifen);
			tell_object(total[i],"����뱾�δ���ǰ2ǿ�����"+jifen+"����֡�\n");
		}
		return;
	} else
	if (sizeof(total) == 1)
	{
		// change the daemon's state
		msg = "��˵�������˴���Բ��������" + total[0]->name(1) + "��Ϊ���˹ھ���";
		give_bouns(total[0]);
		kickout_players();
	} else
		return;

	message_competition(msg);
	change_state(SLEEPING);
}

private void give_bouns(object me)
{
	int exp;
	int pot,jifen;
	string msg;
	object ob;

	// lead me out
	restore_status(me);
	tell_object(me, "�������ˬ����...\n");
	me->move(ENTRY_ROOM);
	message("vision", me->name() + "���������˹�����һ����Ц��\n",
		environment(me), ({ me }));

	jifen = 30*(selected+1);

	// bouns
/*
	pot = me->query_potential_limit();
	pot -= me->query("potential");
	exp = me->query("combat_exp") / 500 + 3000;
	msg = HIG "ͨ����δ����������� " + (string)exp + " �㾭��";
	if (pot > 0)
	{
		pot = random(pot / 3) + 1;
		msg += "�� " + (string) pot + " ��Ǳ�ܡ�"NOR"\n";
	} else
	{
		pot = 0;
		msg += "��"NOR"\n";
	}
*/
	ob = new("/clone/vip/jiuzhuan");
	msg = HIG"��ϲ���ñ��δ����ھ������������"HIY+jifen+NOR"��\n";
	msg += HIG"������˴����ھ����⽱����Ʒ"+ob->short()+NOR"��\n";
	ob->move(me);
	me->add("pkd_pot", jifen);
//	me->add("potential", pot);
//	me->add("combat_exp", exp);
	tell_object(me, msg);
}

// remove overide function
// restore condition
private void restore_status(object me)
{
	mapping my;
	mapping cnd;
	string *ks;
	int i;

	me->delete_temp("in_pkd");
	me->delete_temp("pkd_pot");
	me->delete_override("unconcious");
	me->delete_override("die");
	me->delete_override("quit");
	me->remove_all_enemy(1);
	me->remove_all_killer();
	me->clear_condition();
	me->receive_damage("qi", 0);
	me->apply_killer(me->query_temp("backup/killer"));
	me->apply_want(me->query_temp("backup/want"));

	cnd = me->query("backup/condition");
	me->delete("backup/condition");
	me->delete_temp("block_msg/all");
	if (! mapp(cnd)) return;
	ks = keys(cnd);
	for (i = 0; i < sizeof(ks); i++)
		me->apply_condition(ks[i], cnd[ks[i]]);

	my = me->query_entire_dbase();
	if (my["qi"] < 1)       my["qi"] = 1;
	if (my["eff_qi"] < 1)   my["eff_qi"] = 1;
	if (my["jing"] < 1)     my["jing"] = 1;
	if (my["eff_jing"] < 1) my["eff_jing"] = 1;
}

// send invite message
private void send_invite_message()
{
	object *obs;
	int exp_ul, exp_dl;

	exp_dl = tlist[selected]["exp"][0];
	exp_ul = tlist[selected]["exp"][1];
	obs = filter_array(all_interactive(),
			   (: ! wizardp($1) &&
			      $1->query("combat_exp") >= $(exp_dl) &&
			      $1->query("combat_exp") <= $(exp_ul) :));
	if (! sizeof(obs))
		return;

	message("vision", HIR "���յ������ϴ����µ�����������������μ����" +
			  tlist[selected]["name"] + "����û����Ȥȥ�������֣�"NOR"\n",
		obs);
}

int start_by_others(int n)
{
	if (state == STARTING)
		return notify_fail("���ڱ������ڽ����С�\n");

	if (state == GET_READY)
		return notify_fail("���ڱ������ڱ����С�\n");

	if (n < 0 || n >= sizeof(tlist))
		return notify_fail("û������ȼ��ı���(0-" +
				   (sizeof(tlist) - 1) + ")��\n");
	selected = n;
	change_state(GET_READY);
	return 1;
}

object *query_all_competitor()
{
	return total;
}

// overide function of quit
int check_quit(object me)
{
	message_competition("��˵" + me->name(1) +
			    "�������ӣ������ˡ�");
	restore_status(me);
	if (arrayp(total))
		total -= ({ me });

	tell_object(me, "���ӳ������˳���\n");

	// continue run quit function
	me->move(ENTRY_ROOM);
	message("vision", "ֻ��" + me->name() + "������ŵ����˳�����\n",
		environment(me), ({ me }));
	return 1;
}

// overide function of lost(die/unconcious)
int check_out(object me)
{
	object ob;
	mapping my;
	string msg;
	string room;
	int score;

	room = base_name(environment(me));
	if (! sscanf(room, PK_ROOM "%*s"))
	{
		// not in pk room
		total -= ({ me });
		return 0;
	}

	my = me->query_entire_dbase();
	my["eff_qi"] = my["max_qi"];
	my["eff_jing"] = my["max_jing"];
	my["qi"] = 1;
	my["jing"] = 1;

	tell_object(me, HIR "\n�������ǰһ��ģ��...�������ˣ�"NOR"\n");
	if (ob = me->query_last_damage_from())
	{
		msg = "��˵" + me->name(1) + "����" + ob->name(1) + "�Ķ��֣���������̭��";
		tell_object(ob,HIM"�����"+me->name(1)+"����� +"+(selected+1)+NOR"��\n");
	} else
		msg = "��˵" + me->name(1) + "�������ѣ��������ޡ��Ѿ�������̭��";
	message_competition(msg);

	restore_status(me);
	total -= ({ me });
	me->move(ENTRY_ROOM);
	message("vision", "һ����Ӱٿ�Ĵ��˳������漴���ǡ�ž����һ�����ͼ�" + me->name() +"ˤ���˵��ϣ�һ��������������ӡ�\n", environment(me), ({ me }));
	tell_object(me, "�������У�����ñ������������������ص�ˤ���˵��ϡ�\n");
	if (! living(me))
		me->revive();
	return 1;
}

// reject_join?
string reject_join(object me)
{
	int exp;

	if (state == STARTING)
		return "����" + tlist[selected]["name"] + "���ھ��У�"
		       "�㻹���´������ɡ�";

	if (state != GET_READY)
		return "����ûҪ���б���������������ʲô��";

	exp = me->query("combat_exp");
	if (exp < tlist[selected]["exp"][0])
		return "�㻹�����˰ɣ�����㾭��ͱ��ȥ�����ˡ�";

	if (exp > tlist[selected]["exp"][1])
		return "Ŷ...���书��˸�ǿ����λ��Ǳ��С�������ˡ�";

	return 0;
}
