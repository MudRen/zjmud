// chat room
// by Doing

#include <room.h>
#include <ansi.h>
#include <command.h>

inherit ROOM;

int is_chat_room() { return 1; }
int do_help(string arg);

string look_board();
int do_ban(string arg);
int do_invite(string arg);

void setup()
{
	set("channel_id", "���쾫��");
	::setup();
}

void create()
{
	set("short", "������");
	set("long", @DESC
����ʲôҲû�С�
DESC );
	set("no_fight", 1);
	set("no_sleep_room",1);
	set("item_desc", ([
		"chalkboard" : (: look_board :),
	]));

	setup();
}

void init_room(object out_room, object me)
{
	object board;

	set("owner_id", me->query("id"));
	set("startroom", base_name(out_room));
	set("short", me->name(1) + "(" + me->query("id") + ")��������");
	set("long", sort_string("������" + me->name(1) + "Ϊ����ṩ����"
				"���ң��м伸�����ʣ���������ɢɢ�İ��Ų�"
				"ˮ���̻Ҹף���������һ�صĹ���Ƥ����ͷ��"
				"����֮��տյ�����ʲôҲû�С����ſ�����"
				"бб�ķ���һ���ڰ�(chalkboard)������д��"
				"�����֡�\n", 64, 4));
	set("exits/out", base_name(out_room));

	if (me->query("env/auto_ban"))
		do_ban(me->query("env/auto_ban"));

	if (me->query("env/auto_invite"))
		do_invite(me->query("env/auto_invite"));

	CHANNEL_D->do_channel(out_room, "sys",
			      sprintf("%s(%s)��%s������һ�������ҡ�",
				      me->name(1), me->query("id"),
				      out_room->short()));
	if (me->query_skill("idle-force", 1) >= 300)
	{
		board = new("/clone/board/chatroom_b");
		board->set_from_me(me, this_object());
	}
}

private string look_board()
{
	string topic;

	if (! stringp(topic = query("topic")))
		return "����ƾ��Ծ���������� - �������ԡ�\n";

	return "����Ļ����ǣ�" + topic + "\n";
}

int is_owner(object me)
{
	if (me->query("id") == query("owner_id") ||
	    me->query("couple/id") == query("owner_id"))
		return 1;

	return notify_fail("�㲻����������ҵ����ˣ�û�з�����Ȩ����\n");
}

int welcome(object me)
{
	string *ban;
	string *can;

	if (is_owner(me))
		return 1;

	if (query("ban_all"))
	{
		if (! arrayp(can = query("can")))
			return notify_fail("�������˲������κ��˽�����������ҡ�\n");

		if (member_array(me->query("id"), can) == -1)
			return notify_fail("�����ڲ��ܽ�����������ҡ�\n");
		return 1;
	}

	if (! arrayp(ban = query("ban")))
		return 1;

	if (member_array(me->query("id"), ban) != -1)
		return notify_fail("�����ڲ��ܽ�����������ҡ�\n");

	return 1;
}

int invisible_for(object me)
{
	if (! query("secret") ||
	    welcome(me))
		return 0;

	return 1;
}

int do_ban(string arg)
{
	object me;
	string *ban;
	string *can;
	string msg;
	string *all;
	int i;

	me = this_player();
	if (! is_owner(me) || arg && ! stringp(arg))
		return 0;

	if (! arrayp(ban = query("ban"))) ban = ({ });
	if (! arrayp(can = query("can"))) can = ({ });

	if (! arg)
	{
		if (query("ban_all"))
		{
			write("�����ھܾ�����û�о���������˽��������ҡ�\n");
			return 1;
		}

		if (! sizeof(ban))
		{
			write("�����ڲ�û�оܾ��κ��˽��������ҡ�\n");
			return 1;
		}

		msg = "��ĺ�������\n" HIR;
		for (i = 0; i < sizeof(ban); i++)
		{
			msg += sprintf("%12-s", ban[i]);
			if (! ((i + 1) % 4)) msg += "\n";
		}

		if (i % 4) msg += "\n";
		msg += NOR;
		write(msg);
		return 1;
	}

	if (arg == "all" || arg == "ALL" || arg == "-all" || arg == "-ALL")
	{
		if (! query("ban_all"))
		{
			write("���ڿ�ʼ�㽫�ܾ���Щû�о�����"
			      "����˽��������ҡ�\n");
			set("ban_all", 1);
		} else
			write("��ղ��Ѿ��ܾ���Щû�о�������"
			      "���˽����������ˡ�\n");
		return 1;
	}

	if (member_array(arg, ban) != -1)
	{
		write("���������Ѿ����趨Ϊ�ܾ����ڵ���ʿ�ˡ�\n");
		return 1;
	}

	if (arg == me->query("id"))
	{
		write("�ܾ����Լ����ڣ����ǲ��Ǵ��������⣿\n");
		return 1;
	}

	if (arg == query("owner_id"))
	{
		write("��������Ҳ��������棿���������е������ˡ�\n");
	}

	all = explode(arg, ",") - ({ "", query("owner") }) - ban;
	if (! sizeof(all))
	{
		write("��Щ�������Ѿ����趨Ϊ�������ڵ���ʿ�ˡ�\n");
		return 1;
	}
	if (sizeof(ban) > 50)
	{
		write("���ˣ����Ѿ�ָ��̫������ˣ�������ɴ�"
		      "������е���(invite all)���ں��ˡ�\n");
		return 1;
	}

	ban += all;
	can -= all;
	arg = implode(all, ",");
	write("�㽫(" + arg + ")�����˺������������ڿ�ʼ�ܾ������ڡ�\n");
	set("ban", ban);
	set("can", can);
	return 1;
}

int do_invite(string arg)
{
	object me;
	object ob;
	string *ban;
	string *can;
	string msg;
	string *all;
	int i;

	me = this_player();
	if (! is_owner(me) || arg && ! stringp(arg))
		return 0;

	if (! arrayp(ban = query("ban"))) ban = ({ });
	if (! arrayp(can = query("can"))) can = ({ });

	if (! arg)
	{
		if (! query("ban_all"))
		{
			write("������ͬ���κ�û�б��ܾ����˽��������ҡ�\n");
			return 1;
		}

		if (! sizeof(can))
		{
			write("�����ڲ�û���ر������κ��˽��������ҡ�\n");
			return 1;
		}

		msg = "������Щ�������صع���Ҫ������ģ�\n" HIC;
		for (i = 0; i < sizeof(can); i++)
		{
			msg += sprintf("%12-s", can[i]);
			if (! ((i + 1) % 4)) msg += "\n";
		}

		if (i % 4) msg += "\n";
		msg += NOR;
		write(msg);
		return 1;
	}

	if (arg == "all" || arg == "ALL" || arg == "-all" || arg == "-ALL")
	{
		if (query("ban_all"))
		{
			write("���ڿ�ʼ��ͬ��������û�б�����"
			      "���������˶��ܽ��������ҡ�\n");
			delete("ban_all");
		} else
			write("���Ѿ�ͬ��������û�б��������"
			      "�����˶��ܽ����������ˡ�\n");
		return 1;
	}

	if (member_array(arg, can) != -1)
	{
		write("���������Ѿ����趨Ϊ�������ڵ���ʿ�ˡ�\n");
		return 1;
	}

	if (arg == me->query("id"))
	{
		write("�������Լ���������û�������Ҫ��\n");
		return 1;
	}

	if (arg == query("owner_id"))
	{
		write("��������ô���ƺ����һ���ˡ�\n");
	}

	all = explode(arg, ",") - ({ "", query("owner") }) - can;
	if (! sizeof(all))
	{
		write("��Щ�������Ѿ����趨Ϊ�������ڵ���ʿ�ˡ�\n");
		return 1;
	}

	if (sizeof(can) > 50)
	{
		write("���ˣ����Ѿ�ָ��̫������ˣ�������ɴ�"
		      "������е���(invite all)���ں��ˡ�\n");
		return 1;
	}

	ban -= all;
	can += all;
	arg = implode(all, ",");
	write("�㽫(" + arg + ")�������������������ڿ�ʼ�ر����������ڡ�\n");
	set("ban", ban);
	set("can", can);

	if (sizeof(all) == 1 &&
	    objectp(ob = find_player(arg)) &&
	    ! present(ob, this_object()))
		TELL_CMD->main(me, arg + " ���ҵ�������������ɣ�");
	return 1;
}

int do_kickout(string arg)
{
	object me;
	object ob;
	int i;

	me = this_player();
	if (! is_owner(me))
		return 0;

	if (! arg)
		return notify_fail("��Ҫ��˭�߳�ȥ��\n");

	ob = present(arg, this_object());
	if (! ob)
		return notify_fail("����û������˰���\n");

	if (ob->query("id") == "men shen")
	{
		message_vision("$N��$n��ϸ�ĵ��������պá�\n",
			       me, ob);
		destruct(ob);
		return 1;
	}

	if (! ob->is_character())
		return notify_fail("������ˣ��ǿɲ��ǻ��ˡ�\n");

	if (ob == me)
		return notify_fail("�������ˮ��\n");

	message_vision("$N����һ�ţ���$n���๾����߳���ȥ��\n",
		       me, ob);
	ob->move(query("startroom"));
	if (! ob->is_busy())
		ob->start_busy(3);
	message("vision", "ֻ����žડ�һ����" + ob->name() +
		"�Ǳ������Ĺ��˳�����ƨ�����滹�����������"
		"��һ��Ьӡ��\n", environment(ob), ({ ob }));
	return 1;
}

int do_closechat()
{
	object me;
	object ob;
	object *obs;
	int i;

	me = this_player();
	if (! is_owner(me))
		return 0;

	message_vision("$Nվ���������˸������������߰��߰ɣ������ˡ�\n", me);
	obs = filter_array(deep_inventory(this_object()), (: userp :));
	for (i = 0; i < sizeof(obs); i++)
	{
		message_vision("$N���˳�ȥ��\n", obs[i]);
		obs[i]->move(query("startroom"));
		if (living(obs[i]))
			message("vision", obs[i]->name() + "��" + short() +
				"�������˳�����\n", environment(obs[i]), ({ obs[i] }));
		else
			message("visoin", obs[i]->name() + "���˴�" + short() +
				"����̧�˳�����\n", environment(obs[i]), ({ obs[i] }));
	}
	CHANNEL_D->do_channel(this_object(), "sys",
			      sprintf("%s��%s(%s)����ˡ�",
				      short(),
				      me->name(1), me->query("id")));
	destruct(this_object());
	return 1;
}

int do_summon(string arg)
{
	object ob;

	if (! is_owner(this_player()))
		return 0;

	if (arg != "menshen" && arg != "men shen")
		return notify_fail("��Ҫ�ٻ�ʲô��\n");

	if (objectp(present("men shen", this_object())))
	{
		write("�����Ѿ�������Ϊ������ˡ�\n");
		return 1;
	}

	if (this_player()->query_skill("idle-force", 1) < 100)
	{
		write("��ķ�����ˮƽ���ޣ����޷�������һ����������\n");
		return 1;
	}

	ob = new("/clone/gift/menshen");
	message_vision("$N��Ȼ��˵���ˣ�����һ�����������һ"
		       "��ͻȻ���ϵ���һ���껭��\n���滭��"
		       "һ��������׳������$N��������������"
		       "���������档\n", this_player());
	ob->move(this_object());
	return 1;
}

int do_secret(string arg)
{
	object me;

	if (! arg)
	{
		write("����������" + (query("secret") ? "��������״̬��\n"
						      : "���ڹ���״̬��\n"));
		return 1;
	}

	me = this_player();
	if (! is_owner(me))
		return 0;

	if (arg == "on" || arg == "ON" || arg == "+")
	{
		if (query("secret"))
		{
			write("�����������Ѿ������ܵ��ˡ�\n");
			return 1;
		}

		message_vision("$N�������صĿ��˿����ܣ�����ָ����"
			       "��ǰ��С��������������\n", me);
		set("secret", 1);
		message("vision", HIG "�����������Ѿ������ܵ��ˡ�"NOR"\n",
			all_inventory());
	} else
	if (arg == "off" || arg == "OFF" || arg == "-")
	{
		if (! query("secret"))
		{
			write("���������Ҳ��������ܵġ�\n");
			return 1;
		}

		message_vision("$N�������Ŀ��˿����ܣ�����������ǲ�"
			       "�Ƕ�˵�����Ļ��ˣ���\n", me);
		delete("secret");
		message("vision", HIC "�����������Ѿ��ǹ������ˡ�"NOR"\n",
			all_inventory());
	} else
		do_help("secret");

	return 1;
}

int do_topic(string arg)
{
	object me;
	object ob;

	me = this_player();
	if (! is_owner(me))
		return 0;

	if (! arg)
	{
		if (query("topic"))
			write("Ŀǰ�Ļ����ǣ�" + query("topic") + "��\n");
		else
			write("Ŀǰû������ʲô���⡣\n");
		write("�����ָ��ʲô�»��⣿\n");
		return 1;
	}

	if (arg == "none")
	{
		delete("topic");
		message_vision("$N�������������İɣ����ؾ�����ĳ�����⡣\n", me);
		return 1;
	}

	set("topic", arg);
	message_vision("$N�������ǽ��첻��̸̸��" + arg + "��������⡣\n"
		       "˵��ӵ����ҵ�һ���۱��ںڰ��Ϻ���Ϳ�˼����֡�\n", me);
	return 1;
}

int do_help(string arg)
{
	switch (arg)
	{
	case "here":
		write(@HELP
�����������ʹ��������Щ����������ص����
    ban	  ��ֹĳЩ�˷���������
    closechat    �ر����������(�����˶����߳�)
    invite       ����ĳ���˽���������
    kickout      ��ĳ�����߳�������
    summon       ��������
    look	 �������������涼��˭
    out	  �뿪������
    topic	���������ҵĻ���
HELP );
		break;

	case "ban":
		write(@HELP_BAN
ָ���ʽ : ban <���ID> [all]

��ָ�������ָֹ������ҽ�����������ҡ����ָ���Ĳ����� all
���ֹ���е���ҽ��룬��ʱֻ����Щ�����������Ҳ��ܽ��롣��
��ָ���Ӱ���ʱ�Ѿ����������ڵ���ҡ����һ����Ҫ��ֹ���
��ң������ö��ŷֿ������磺ban xxx,yyy,zzz�� �������Ҹոս�
���õ�ʱ����Զ�ִ��ban auto_ban������auto_ban�������õĲ�����

���ָ�kickout, invite
HELP_BAN );
		break;

	case "closechat":
		write(@HELP_CLOSECHAT
ָ���ʽ : closechat

�ر���������ҡ�

HELP_CLOSECHAT );

	case "invite":
		write(@HELP_BAN
ָ���ʽ : invite <���ID> [all]

��ָ����������ָ������ҽ�����������ҡ������ǰ�����ұ�ָ
����ֹ���룬���ʱ״̬ȡ����ͬʱ�����ҿ��Խ���tell�Ļ�����
�յ����������Ϣ�����ָ���Ĳ����� all�����ȡ����ֹ���е���
�ҽ�������ƣ��������ban all ���Եġ����һ����Ҫ��������
�ң������ö��ŷֿ������磺ban xxx,yyy,zzz�� �������Ҹոս���
�õ�ʱ����Զ�ִ��invite auto_invite�� ����auto_invite������
�õĲ�����

���ָ�kickout, ban
HELP_BAN );
		break;

	case "kickout":
		write(@HELP_BAN
ָ���ʽ : invite <���ID>

�߳�ĳһ�����ҵ���ң����ID��men shen���������������

���ָ�ban, invite
HELP_BAN );
		break;

	case "summon":
		write(@HELP_SUMMON
ָ���ʽ : summon menshen

�������һ�ټ��ķ����񹦣������Լ�������������Ϳ���ʹ������
����������������������ң��Զ��߳���Щ��������ҵ��ˡ�
HELP_SUMMON );
		break;

	case "topic":
		write(@HELP_BAN
ָ���ʽ : topic <������Ϣ> | <none>

ָ��һ������Ļ��⡣

HELP_BAN );
		break;

	case "secret":
		write(@HELP_SECRET
ָ���ʽ : secret [+ | on | - | off]

ʹ�Լ��������ҳ�Ϊ���ܵ������ң����߽������״̬��

HELP_SECRET );
		break;

	default:
		return notify_fail("��Ҫ�鿴ʲô������\n");
	}

	return 1;
}

void add_all_action()
{
	// add all action for this_player()
	add_action("do_ban", "ban");
	add_action("do_closechat", "closechat");
	add_action("do_invite", "invite");
	add_action("do_kickout", "kickout");
	add_action("do_invite", "invite");
	add_action("do_topic", "topic");
	add_action("do_help", "help");
	add_action("do_secret", "secret");
	add_action("do_summon", "summon");
}

void init()
{
	add_all_action();
}

int clean_up()
{
	return 1;
}

