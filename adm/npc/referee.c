// referee.c ��ƽ��

inherit NPC;
#include <ansi.h>;

int do_bihua(string arg);
int do_no();
void shout_message(string msg);

void create()
{
	set_name("��ƽ��", ({ "gongping zi", "zi", "referee" }) );
	set("gender", "����");
	set("age", 35);
	set("no_get", 1);
	set("long",
		"����һλ�ɷ���ǵ�������ˣ����������ķ����Ժ�������������˽��\n");
	set("combat_exp", 60000);
	set("shen_type", 1);
	set("attitude", "friendly");

	set("apply/attack", 50);
	set("apply/defense", 50);

	set("max_qi", 800);
	set("max_jing", 800);
	set("max_neili", 800);

	setup();

	carry_object("/clone/misc/cloth")->wear();
	carry_object("/clone/weapon/changjian")->wield();
}


void init()
{
	::init();
	add_action("do_team", "team");
	add_action("do_bihua", "bihua");
	add_action("do_bihua", "bi");
	add_action("do_bihua", "hit");
	add_action("do_bihua", "fight");
	add_action("do_bihua", "qiecuo");
	add_action("do_halt", "halt");
	add_action("do_halt", "h");
	add_action("do_no", "beg");
	add_action("do_no", "steal");
	add_action("do_no", "quanjia");
	add_action("do_no", "persuade");
	add_action("do_no", "touxi");
	add_action("do_no", "ansuan");
	add_action("do_no", "kill");
}

int do_team(string arg)
{
	if (! arg)
		return 0;

	if (sscanf(arg, "kill %*s") == 1)
	{
		message_vision("$N����ǰ���͸���$nһ�����⣬$n�������˹�ȥ��\n",
			       this_object(), this_player());
		this_player()->unconcious();
		return 1;
	}

	return 0;
}

int do_bihua(string arg)
{
	object me;
	object ob;
	object old;

	if (! arg || ! objectp(ob = present(arg)))
	{
		write("��Ҫ��˭�Ȼ���\n");
		return 1;
	}

	me = this_player();
	if (me == ob)
	{
		write("���ǲ�����Ϊ���¾����Լ����ϴ���û�еڶ���Ӣ���ˡ�\n");
		return 1;
	}

	if (! userp(ob))
	{
		write("�������˼���ս�������˼Ҹ���û�����㡣\n");
		return 1;
	}

	if (! living(ob))
	{
		write("�㻹�ǵ��˼�������˵�ɡ�\n");
		return 1;
	}

	if (me->is_fighting() && me->query_competitor())
	{
		write("���������ں�" + me->query_competitor()->name() +
		      "�����ء�\n");
		return 1;
	}

	if (ob->is_fighting())
	{
		write("�˼����ڶ��֣�����ȥ���ָ�ʲô��\n");
		return 1;
	}

	if (me->query("qi") * 100 / me->query("max_qi") < 70)
	{
		write("�����������������棬�α�æ�Ŷ��֣�\n");
		return 1;
	}

	if (ob->query("qi") * 100 / ob->query("max_qi") < 70)
	{
		write("�˼������ƺ�������֧�����ǵȻ����˵�ɡ�\n");
		return 1;
	}

	if (me->query("combat_exp") < 10000)
	{
		write("��ƽ����Ц���������Ķ����ģ�����ô����û��"
		      "��˵���������������������ҡ�\n");
		return 1;
	}

	if (ob->query("combat_exp") < 10000)
	{
		write("��ƽ�ӿ�����������˰ɣ�" + ob->name() +
		      "�书��΢��������ƺ���ʧ��ݡ�\n");
		return 1;
	}

	if (old = me->query_temp("pending/fight"))
	{
		if (old == ob)
		{
			write("���������˼���ս�������˼һ�û�д�Ӧ��\n");
			return 1;
		}

		tell_object(old, me->name() + "�ı����ⲻ��������ս�ˡ�\n");
		tell_object(me, "��ı����ⲻ������" + old->name() + "��ս�ˡ�\n");
	}

	if (ob->query_temp("pending/fight") != me)
	{
		me->set_temp("pending/fight", ob);
		message_vision(HIY "\n$N" HIY "������$n" HIY "���������һᣬ���Ǻβ�һ��"
			       "�ߵͣ�����" + name() + "����Ϊ���Ǽ�֤�ɺã�"NOR"\n",
			       me, ob);
		return 1;
	}

	ob->delete_temp("pending/fight");

	message_vision(HIY "\n$N" HIY "��ͷ�����ܺã����ɣ����ؿ�����"NOR"\n",
		       me, ob);

	shout_message(me->name(1) + "(" + me->query("id") + ")����" +
		      RANK_D->query_self(me) + me->name(1) + "����������" +
		      RANK_D->query_respect(ob) + "��̡�");
	me->set_override("win",  bind((: call_other, __FILE__, "player_win",  environment() :), me));
	me->set_override("lost", bind((: call_other, __FILE__, "player_lost", environment() :), me));
	ob->set_override("win",  bind((: call_other, __FILE__, "player_win",  environment() :), ob));
	ob->set_override("lost", bind((: call_other, __FILE__, "player_lost", environment() :), ob));
	me->competition_with(ob);
	return 1;
}

void player_win(object env, object me)
{
	object ob;

	ob = me->query_competitor();
	if (! objectp(ob))
	{
		shout_message(name() + "̾������α��䣬" + me->name(1) + "��ʤ��");
		return;
	}

	if (environment(ob) != environment(me))
	{
		shout_message(name() + "Ц����" + ob->name(1) +
			      "����ʱ�������ӣ�" + me->name(1) + "��ս��ʤ��");
	} else
	if (me->query("age") > ob->query("age"))
	{
		shout_message(name() + "��ͷ��������Ȼ�������ϵ���������" +
			      me->name(1) + "����սʤ" + ob->name(1) + "��");
	} else
	if (me->query("age") > ob->query("age"))
	{
		shout_message(name() + "�޵�������" + me->name(1) + "����սʤ" +
			      ob->name(1) + "�����ν�ǳ���������ǰ�ˣ�");
	} else
	{
		shout_message(name() + "����" + me->name(1) + "����սʤ" +
			      ob->name(1) + "����ϲ��ϲ��");
	}
}

void player_lost(object env, object me)
{
	mapping exits;
	string exit;

	if (environment(me) != env || ! mapp(exits = env->query("exits")))
		return;

	exit = values(exits)[random(sizeof(exits))];
	me->move(exit);
	tell_room(env, "ֻ��" + me->name() + "���һ����������ȥ��\n");
	message_vision("ֻ��$N���๾��Ĺ�������̨���ߺ�ѽѽ���ڵ������˰��졣\n", me);
}

int do_no()
{
	command("say " + this_player()->name() + "��������Ŀ���������˲���֮�£�");
	return 1;
}

int accept_ansuan(object ob)
{
	message("vision", "һ����Ӱ������" + name() +
		"����һ�ӣ���" + ob->name() + "���˳�ȥ��ˤ�˸���ͷ������\n",
		environment());
	tell_object(ob, "��������ȥ��ȥ��" + name() + "����һ�ӣ����㵯�˻�����\n");
	return notify_fail("�˼��书̫�ߣ��㻹������ʵʵ�Ĳ�Ҫ�Ҷ���\n");
}

void receive_damage(string type, int count) {}

void kill_ob(object ob) {}

void fight_ob(object ob) {}

void shout_message(string msg)
{
	message("channel:chat", HIW "�����䡿" + msg + ""NOR"\n",
		all_interactive());
}

int want_receive_msg() { return 1; }

void receive_message(string msgclass, string msg)
{
	object ob;
	object *bct;

	if (! objectp(ob = environment()) ||
	    ! arrayp(bct = ob->broadcast_to()))
	{
		// needn't broadcast to others
		return;
	}

	message("vision", WHT "�����ֿ챨��" NOR + BBLU +
			  replace_string(msg, NOR, BBLU) + NOR,
		bct);
}
