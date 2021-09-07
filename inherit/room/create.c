// create.c
// create chat room
// by Doing

#pragma save_binary

#include <ansi.h>
#include <room.h>

inherit ROOM;

void setup()
{
	set("channel_id", "���쾫��");
	::setup();
}

varargs private mixed query_chat_room(string id)
{
	object *rooms;
	rooms = filter_array(children(CHAT_ROOM),
			     (: clonep($1) && stringp($1->query("owner_id")) &&
				$1->query("startroom") == base_name(this_object()) :));
	if (id)
	{
		rooms = filter_array(rooms, (: $1->query("owner_id") == $(id) :));
		if (sizeof(rooms) < 1)
			return 0;
		return rooms[0];
	}
	return rooms;
}

int do_chathere(string arg)
{
	object *rooms;
	object owner;
	string *msg;
	int i;

	rooms = query_chat_room();
	if (! sizeof(rooms))
		return notify_fail("Ŀǰû���κ��˽��������ҡ�\n");

	write("Ŀǰ��" + short() + "����������������Щ��\n"
	      HIC "��" HIY "������������������������������������������������������������" HIC "��"NOR"\n");
	msg = allocate(sizeof(rooms));
	for (i = 0; i < sizeof(rooms); i++)
	{
		if (rooms[i]->invisible_for(this_player()))
		{
			msg[i] = 0;
			continue;
		}

		owner = find_player(rooms[i]->query("owner_id"));
		msg[i] = sprintf("  %-30s    ���ڣ�%d��",
				 rooms[i]->short(),
				 sizeof(filter_array(all_inventory(rooms[i]), (: userp($1) && this_player()->visible($1) :))));
		if (rooms[i]->welcome(this_player()))
			msg[i] = HIC + msg[i] + NOR;
		else
			msg[i] = HIR + msg[i] + NOR;
	}
	msg = sort_array(filter_array(msg, (: stringp :)), 1);
	write(implode(msg, "\n") + "\n"
	      HIC "��" HIY "������������������������������������������������������������" HIC "��"NOR"\n");
	return 1;
}

int do_enter(string arg)
{
	object ob;
	object me;
	object ride;

	if (! arg)
		return do_chathere(arg);

	me = this_player();
	if (! objectp(ob = query_chat_room(arg)) ||
	    ob->invisible_for(me))
		return notify_fail("û����������ҡ�\n");

	if (objectp(ride = me->query_temp("riding")))
		return notify_fail("û��˵����������" + ride->name() +
			 	   "�������ҵġ�\n");

	if (me->is_busy())
		return notify_fail("����æ������˵�ɡ�\n");

	if (me->query("doing") == "scheme")
		return notify_fail("����ƻ�������˵�ɡ�\n");

	message_vision("$N�첽��" + ob->short() + "��ȥ��\n", me);
	if (! ob->welcome(me))
	{
		message("vision", "ȴ��" + me->name() + "ת��һȦ�����"
			"㬵����˻����������ǲ�̫���˼һ�ӭ��\n",
			environment(me), ({ me }));
		tell_object(me, "�˼Ҳ���ӭ�㣬�㻹�Ǳ�ȥɨ���ˡ�\n");
		return 1;
	}
	me->move(ob);
	message("vision", me->name() + "���˽�����\n",
		environment(me), ({ me }));
	return 1;
}

int do_newchat(string arg)
{
	object *rooms;
	object me;
	object room;

	me = this_player();
	rooms = filter_array(children(CHAT_ROOM),
			     (: clonep($1) && $1->query("owner_id") == $(me)->query("id") :));
	if (sizeof(rooms) > 0)
		return notify_fail("���Ѿ������������ˣ��ڹر���֮ǰ��������\n");

	if (me->query_skill("idle-force", 1) < 10)
		return notify_fail("��ķ����񹦵ȼ�̫�ͣ����޷�������һ������������\n");

	room = new(CHAT_ROOM);
	room->init_room(this_object(), me);
	write("�㽨���������ҡ�\n");
	message_vision("$N���ʼ磬��" + room->short() + "��ȥ��\n", me);
	me->move(room);
	if (find_call_out("clean_chat_room") == -1)
		call_out("clean_chat_room", 15 * 60);
	return 1;
}

int do_clean(string arg)
{
	object *rooms;
	int i;

	if (! is_root(this_player()))
		return notify_fail("��û��Ȩ����������������ҡ�\n");

	rooms = query_chat_room();
	if (! sizeof(rooms))
		return notify_fail("Ŀǰû���κ��˽��������ҡ�\n");

	if (arg)
	{
		rooms = filter_array(rooms, (: $1->query("owner_id") == $(arg) :));
		if (! sizeof(rooms))
			return notify_fail("Ŀǰ " + arg + " ��û�н��������ҡ�\n");
	}

	rooms = filter_array(rooms, (: ! sizeof(filter_array(all_inventory($1), (: userp($1) || playerp($1) || $1->is_chatter() ||
										   $1->is_item_make() && $1->is_stay_in_room() :))) :));
	if (! sizeof(rooms))
		return notify_fail("Ŀǰû�пյķ��������������ҡ�\n");

	for (i = 0; i < sizeof(rooms); i++)
	{
		write(rooms[i]->short() + "������ˡ�\n");
		destruct(rooms[i]);
	}

	return 1;
}

void clean_chat_room()
{
	object *rooms;

	remove_call_out("clean_chat_room");
	rooms = query_chat_room();
	rooms->clean_up();
	rooms -= ({ 0 });
	if (sizeof(rooms))
		call_out("clean_chat_room", 15 * 60);
}

int do_help(string arg)
{
	switch (arg)
	{
	case "here":
		write(@HELP
�����������ʹ��������Щ����������ص����
    enter	����һ��������
    chathere     ���������������
    newchat      �����µ�������
HELP );
		break;

	case "enter":
		write(@HELP_ENTER
ָ���ʽ : enter <������ID>

��ָ���������ָ���������ң��������죬��Ȼǰ��ı�֤�㲻�ǲ�
�ܻ�ӭ�����

���ָ�chathere��newchat
HELP_ENTER );
		break;

	case "chathere":
		write(@HELP_CHATHERE
ָ���ʽ : herechat

��ָ������������ﶼ����Щ�����ң����п���ȥ�Ǻ�ɫ�ı�ʾ�㲻
�ܻ�ӭ���������ڡ�

���ָ�enter��newchat
HELP_CHATHERE );
		break;
	case "newchat":
		write(@HELP_NEW_CHAT
��ָ�������Լ�����һ�������ң�����Ҫ��һ������������������
ʮ�����ܹ����������ҡ�

���ָ�enter��chathere
HELP_NEW_CHAT );
		break;

	case "clean":
		write(@HELP_CLEAN
���Ŀǰû���˵������ҡ�
HELP_CLEAN );
		break;

	default:
		return notify_fail("��Ҫ�鿴ʲô������\n");
	}

	return 1;
}

void add_all_action()
{
	// add all action for this_player()
	add_action("do_enter", "enter");
	add_action("do_chathere", "chathere");
	add_action("do_newchat", "newchat");
	add_action("do_help", "help");
	add_action("do_clean", "clean");
}

