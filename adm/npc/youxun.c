// youxun.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;
inherit F_UNIQUE;

static object *receiver;

object *query_receiver() { return receiver; }

int ask_fee();
int ask_bomb();
int ask_shedu();
int ask_duwan();
int ask_list();
int filter_listener(object user);

void create()
{
	set_name("��Ѷ", ({ "you xun", "you", "xun", "youxun" }) );
	set("nickname", HIG "��������" NOR);
	set("gender", "����" );
	set("age", 42);
	set("long", "������ר�Ŵ�̽��������Ϣ����Ѷ��\n");
	set("attitude", "friendly");
	set("skill_youxun", 1);
	set("max_jing", 500);
	set("max_qi", 500);
	set("str", 21);
	set("icon","00625");
	set("int", 29);
	set("con", 21);
	set("dex", 35);
	set("combat_exp", 250000);

	set("inquiry", ([
		"ҥ��": "����С�Ĵ�ţ��˭��ҥ���Ҷ��ܲ������",
		"�շ�" : (: ask_fee :),
		"ը��" : (: ask_bomb :),
		"�߶�" : (: ask_shedu :),
		"��ҩ" : (: ask_duwan :),
		"�˵�" : (: ask_list :),
		"����" : "�ٺٺ٣��������˭��������Ϣ�Ǹ���ͨ...",
		"��Ȫˮ"    : "���ɵ�ը�ˣ�����ƿ���ʣ�",
		"������" : "��ѧô(idle-force)�����˽̣�����Ǯ�ġ�",
	]));

	set("vendor_goods", ({
		"/clone/gift/feidan",
		"/clone/gift/feimao",
		"/clone/gift/kuangquan",
	}));

	set("chat_chance", 1);
	set("chat_msg",({
		"��Ѷ��������С����û��ı��£��ͻ������Ϣ����������ʦ��ҥ����Ҳ��֪����\n",
		"��Ѷ����һָ�������˰����������Ӿ��ܲ���ҥ�ԣ����������¥�ۡ�\n",
		"��Ѷ�����е�˵��������㲻�����㣬��������ô������ĳ��֪����\n",
	}));

	set_skill("dodge", 150);
	set_skill("unarmed", 50);
	set_skill("idle-force", 500);

	setup();
	carry_object("d/city/obj/cloth")->wear();

	if (! clonep(this_object()))
	{
		move("/d/city/kedian");
		message_vision("$NЦ���������������ˣ������ˡ�\n", this_object());
		set("startroom", "/d/city/kedian");
	}

	set_temp("bomb_count", 1);
}

void init()
{
	add_action("do_list", "list");
	add_action("do_buy", "buy");
}

mixed accept_ask(object ob, string topic)
{
	object fob;
	if (topic == ob->query("id"))
	{
		command("laugh " + topic);
		return 1;
	}
	fob = find_player(topic);
	if (! fob || ! ob->visible(fob)) fob = find_living(topic);
	if (! fob || ! ob->visible(fob) || ! environment(fob))
		return;

	ob->set_temp("pending/ask_youxun", topic);
	message_vision(CYN "$N" CYN "�ٺټ�Ц��������$n"CYN "С��������û�����⣬������Ҫ50���ƽ𣬲����ۣ���"NOR"\n", this_object(), ob);
	return 1;
}

int recognize_apprentice(object me, string skill)
{
	if (skill != "idle-force")
	{
		if (me->add_temp("illegal_learn", 1) > 3)
		{
			command("say �����㷳��������");
			message_vision("$nһ�Ű�$N�߳����⣡\n",
				       me, this_object());
			me->set_temp("illegal_learn", 2);
			me->move("/d/city/beidajie1");
			me->unconcious();
		} else
			command("say ��ֻ�̷����񹦣����������书��");
		return -1;
	}

	message_vision("$N��$n��̷����񹦵ľ��ϡ�\n", me, this_object());

	if (me->query_temp("learned_idle_force"))
	{
		if (me->add_temp("too_many_xue", 1) > 3)
		{
			command("say ������£�����");
			message_vision("$n����һ�Ű�$N�߳����⣡\n",
				       me, this_object());
			me->set_temp("too_many_xue", 1);
			me->move("/d/city/beidajie1");
			me->unconcious();
		} else
			command("say ���Ȱ��ҸղŽ�����������˵�ɣ�");
		return -1;
	}

	command("say �����ˣ���������ּ��!@#$%^&");

	if (me->query("potential") < me->query("learned_points") + 10)
	{
		write("������ϡ���Ϳ��������Ǳ�ܲ����ˡ�\n");
		return -1;
	}

	if (me->query_skill("idle-force", 1) > 500)
	{
		write("�����������룬��Щ�Ҷ�������������ѶҲ��֪����ô���ˡ�\n");
		return -1;
	}

	me->set_temp("learned_idle_force", 1);
	me->add("learned_points", 10);
	write(HIG "�����������������ã����Ͻ��з�����ϰ��"NOR"\n");
	return -1;
}

void append_receiver(object ob)
{
	if (! receiver)
		receiver = ({ ob });
	else
		if (member_array(ob, receiver) == -1)
			receiver += ({ ob });
}

int accept_object(object me, object ob)
{
	string wid;

	if (clonep(this_object()))
	{
		command("hehe");
		command("say ��������Ѷ����ٰ�������");
		return 1;
	}

	if (ob->id("visible bomb"))
	{
		command("say ��Ҫ�ˣ��Ǿͻ����Ұɡ�");
		return 1;
	}

	if (! stringp(ob->query("money_id")))
	{
		switch (me->query_temp("youxun_refused"))
		{
		case 0:
			command("heihei");
			command("say �������������Űɡ�");
			me->set_temp("youxun_refused", 1);
			return 0;

		case 1:
			message_vision("$N����һ�ţ���$n���˳�ȥ���������ʲô�ң�\n",
				       this_object(), me);
			break;

		case 2:
			message_vision("$N����һ�ţ��ݺݵİ�$n���˳�ȥ��������������ң�\n",
				       this_object(), me);
			me->receive_damage("qi", 100);
			me->receive_wound("qi", 10);
			break;

		default:
			message_vision("$N��ŭ��һ������ڣ��ͼ�$n��ֽƬһ�����˳�ȥ��\n",
				       this_object(), me);
			command("chat* heng " + me->query("id"));
			me->unconcious();
			break;
		}

		me->add_temp("youxun_refused", 1);
		me->move("/d/city/beidajie1");
		message_vision("ֻ����ž����һ����$N�ݺݵ�ˤ���˵��ϡ�\n", me);
		return -1;
	}

	if (ob->value() < 3000)
	{
		message_vision("$N�ӹ�$n�ݹ�ȥ��" + ob->name() +
			       "��������ü�����������Ǯ�����ˣ��㲻Ҫ�͸��Ұɣ�\n",
			       this_object(), me);
		destruct(ob);
		return 1;
	}

	me->delete_temp("youxun_refused", 1);
	if (stringp(wid = me->query_temp("pending/ask_youxun", 1)))
	{
		object fob;

		if (ob->value() < 500000)
		{
			message_vision("$N��Цһ�������������Ǯ���㻹�Ǵ�³�нŻ���ࡣ��\n",
				       this_object());
			return 0;
		}

		me->delete_temp("pending/ask_youxun");
		fob = find_player(wid);
		if (! fob || ! me->visible(fob)) fob = find_living(wid);
		if (! fob || ! me->visible(fob) || ! environment(fob))
		{
			message_vision("$N����ͷ��$n����������... �ղ��һ���������Ϣ�أ���ô��ôһ���...��\n",
				       this_object(), me);
			return 0;
		}

		destruct(ob);
		command("whisper " + me->query("id") +" �ݿɿ���Ϣ������˸ղ���" +
			environment(fob)->short() + "��");
		return 1;
	}

	if ((int)me->query_temp("receive_rumor_time") < time())
		me->set_temp("receive_rumor_time", time());
	me->add_temp("receive_rumor_time", ob->value() / 3000 * 60);
	message_vision("$N�ֵúϲ�£�죬��æ�ӹ�" + ob->name() +
		       "����ͷ�����Ķ�$n�����ã��ã�\n", this_object(), me);
	command("tell " + me->query("id") +
		sprintf(" Ҫ�� %d ������������ҥ����һ���Ҵ������ϵס�",
			(me->query_temp("receive_rumor_time") - time()) / 60));
	destruct(ob);
	append_receiver(me);
	return 1;
}

int ask_fee()
{
	int n;
	object me;

	me = this_player();
	if (me->query_temp("receive_rumor_time") < time())
	{
		command("say ���󲻹���ʮ�����Ӱ���һ���ӣ�");
		return 1;
	}

	n = me->query_temp("receive_rumor_time") - time();
	n /= 60;
	if (! n)
	{
		command("tell " + me->query("id") +
			" ���ϵ�ʱ��������������Ϣ�������Ǯ������");
	} else
	{
		command("tell " + me->query("id") +
			sprintf(" �㻹���� %d ���ӵ���Ϣ��", n));
	}

	message("visoin", name() + "���ֹ����Ķ�" + me->name() +
			  "˵��һЩ����\n", environment(me), ({ me }));
	return 1;
}

int ask_bomb()
{
	object ob;
	object me;
	int n;

	me = this_player();
	if (wizardp(me))
	{
		if (! objectp(ob = present("bomb", this_object())))
			ob = new("/clone/gift/xianxing");
		command("say �ȵȣ�С����͸��㡣");
		ob->move(me, 1);
		return 1;
	}

	n = ((int)me->query_temp("receive_rumor_time")) - time();
	if (n < 0) n = 0;	
	n /= 60;
	if (! n)
	{
		command("shake");
		command("say �������������Ҳ���ʶ�㡣");
		return 1;
	}

	if (! (ob = present("visible bomb", this_object())) &&
	   query_temp("bomb_count") <= 0)
	{
		command("say ��ϧ���ҵ�������㣬������ͷû������");
		return 1;
	}

	if (! ob) catch(ob = new("/clone/gift/xianxing"));

	if (! ob)
	{
		command("say �ҵ�ը���ܳ�... ���������ˣ�");
		return 1;
	}

	command("heihei");
	command("say �������չ�������������ϣ��Ҿ͸���һ��ը����");
	if (! environment(ob)) ob->move(this_object());
	command("give bomb to " + me->query("id"));
	add_temp("bomb_count", -1);
	remove_call_out("restore_bomb");
	call_out("restore_bomb", 150);
	return 1;
}

private void restore_bomb()
{
	set_temp("bomb_count", 1);
}

void receive_report(object user, string verb)
{
	string msg;

	msg = sprintf("��˵%s(%s)��Ҫ��ҥ���ˡ�",
		      user->query("name"), user->query("id"));
	if (random(100) < 7)
	{
		command("heihei");
		command("say " + msg);
	}

	if (! receiver)
		return;

	receiver = filter_array(receiver, (: filter_listener :));
	if (! sizeof(receiver))
	{
		receiver = 0;
		return 0;
	}

	message("vision", HIG "��Ѷ���ĵĸ����㣺" + msg + "\n",receiver, user);
}

private int filter_listener(object ob)
{
	if (! objectp(ob))
		return 0;

	if (present("rumor generator", ob))
		return 1;

	if (ob->query_temp("receive_rumor_time") > time())
		return 1;

	ob->delete_temp("receive_rumor_time");
	return 0;
}

int ask_duwan()
{
	object me;
	object ob;

	me = this_player();
	if (! wizardp(me) || wiz_level(me) < 2)
	{
		command("say ��... ��Ҫ��ҩ��ʲô���¶����Ƿ����ģ�");
		return 1;
	}

	command("consider");
	command("shzi");
	catch(ob = new("/clone/misc/duwan"));
	if (! ob)
	{
		command("say ������˵����⣬����ʱ�ò������ˡ�");
		return 1;
	}
	ob->move(this_object());
	command("give " + ob->query("id") + " to " + me->query("id"));
	command("say ����Ƕ��Ϲ����ģ�ǧ����Ҹ�©�˳�ȥ��");
	return 1;
}

int ask_shedu()
{
	object me;
	object ob;

	me = this_player();
	if (! wizardp(me) || wiz_level(me) < 2)
	{
		command("say ��... ��Ҫ��ҩ��ʲô���¶����Ƿ����ģ�");
		return 1;
	}

	command("heihei");
	command("shzi");
	catch(ob = new("/clone/misc/shedu"));
	if (! ob)
	{
		command("say �߶����˵����⣬����ʱ�ò�������");
		return 1;
	}
	ob->move(this_object());
	command("give " + ob->query("id") + " to " + me->query("id"));
	command("say �����ŷ������Ū�ģ��ɱ�˵���Ҹ���İ���");
	return 1;
}

int ask_list()
{
	object me;

	me = this_player();
	if (me->query_temp("can_buy/youxun/nuclues-bomb", 1))
	{
		command("say ��զ��ô���£��û���˵����...");
		return 1;
	}
	command("shzi");
	command("whisper " + me->query("id") + " �������в��ٺö��������˵úܣ��˵��������ƽ�һ����");
	me->set_temp("can_buy/youxun/nuclues-bomb", 1);
	return 1;
}

int do_list(string arg)
{
	if (arg && ! id(arg))
		return notify_fail("����û������ˡ�\n");

	if (this_player()->query_temp("can_buy/youxun"))
	{
		command("shzi");
		return ::do_list();
	}

	message_vision("$N����æ�ڣ���$n��������ֻ����Ϣ���������ٺ١���\n",
		       this_object(), this_player());
	return 1;
}

int do_buy(string arg)
{
	object me;
	string my_id;

	if (arg && sscanf(arg, "%s from %s", arg, my_id) == 2 && ! id(my_id))
		return notify_fail("����û������ˡ�\n");

	me = this_player();
	if (! me->query_temp("can_buy/youxun"))
	{
		message_vision("$N����˫���Ұڣ���$n��������˵���˲���"
			       "�����ģ��ҿ�����ʵ�ˣ���\n",
			       this_object(), this_player());
		return 1;
	}

	return ::do_buy(arg);
}

