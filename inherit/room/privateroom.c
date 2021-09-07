// privateroom.c

// ���Ǽ̳����ַ������͵ģ������Ա��淿�ݵ������ͷ�����autoload����Ʒ��
// �������ݵĶ��󣬼̳��߱�����/data/room/...Ŀ¼������ļ�����ʱ����
// �����ļ���������ͬ����׺��ͬ��
//
// KEY_DOOR����У����Ǵ��ŵ�λ�á�

#pragma save_binary

#include <ansi.h>

inherit ROOM;
inherit F_OBSAVE;
inherit F_AUTOLOAD;

int do_unlock(string arg);
int do_lock(string arg);
int do_break(string arg);
void this_open_door();
void this_close_door(int silent);
string query_save_file();

int is_private_room() { return 1; }

string room_owner_id()
{
	string rid;

	if (! stringp(rid = query("room_owner_id")))
	{
		if (sscanf(file_name(this_object()),
			   DATA_DIR "room/%s/%*s", rid) != 2)
			return 0;
	}

	return rid;
}

int is_room_owner(object me)
{
	string rid;

	rid = room_owner_id();
	return (me->query("id") == rid || me->query("couple/id") == rid);
}

int restore()
{
	// this object (/inherit/room/privateroom) doesn't need to save
	if (base_name(this_object()) + ".c" == __FILE__)
		return 0;

	return ::restore();
}

int save()
{
	int res;

	// this object (/inherit/room/privateroom) doesn't need to save
	if (base_name(this_object()) + ".c" == __FILE__)
		return 0;

	this_close_door(1);
	save_autoload();
	res = ::save();
	clean_up_autoload();
	return res;
}

void setup()
{
	::setup();
	restore();
	//restore_autoload();
}

// the callback function of F_OBSAVE
mixed save_dbase_data()
{
	mapping data;

	data = ([ "long" : query("long"),
		  "short" : query("short"),
		  "autoload" : this_object()->query_autoload_info() ]);

	if (! undefinedp(query("room_key")))
		data += ([ "room_key" : query("room_key") ]);

	return data;
}

// the callback function of F_OBSAVE
int receive_dbase_data(mixed data)
{
	if (! mapp(data))
		return 0;

	if (! undefinedp(data["long"]))
		set("long", data["long"]);

	if (! undefinedp(data["short"]))
		set("short", data["short"]);

	if (! undefinedp(data["room_key"]))
		set("room_key", data["room_key"]);

	if (! undefinedp(data["short"]))
		this_object()->set_autoload_info(data["autoload"]);

	return 1;
}

void remove()
{
	this_close_door(1);
	save();
}

void init()
{
	if (query("KEY_DOOR"))
	{
		add_action("do_knock", "knock");
		add_action("do_unlock", "unlock");
		add_action("do_lock", "lock");
		add_action("do_unlock", "open");
		add_action("do_lock", "close");
		add_action("do_break", "break");
	}

	add_action("do_kickout", "kickout");
}

int do_kickout(string arg)
{
	string entry;
	object me, ob;
	object oob;

	if (! arg)
		return notify_fail("��Ҫ��˭�߳�ȥ��\n");

	me = this_player();
	ob = present(arg, this_object());

	if (! objectp(ob))
		return notify_fail("�㿴˭��˳�ۣ�\n");

	if (ob == me)
		return notify_fail("�������ˮ��\n");

	if (me->query("couple/id") == ob->query("id"))
	{
		if (me->query("gender") != "Ů��")
			return notify_fail("��Ҫ�Ҵ����š�\n");
		else
			return notify_fail("���ɶ����ô�׺���\n");
	}

	if (! is_room_owner(me))
		return notify_fail("���ֲ�����������ˣ����ʲô��\n");

	if (! query("no_fight"))
		return notify_fail("������ȭͷ���˵������β�ʩչ����ʵ���죿\n ");

	if (me->query("couple/id") == query("room_owner_id"))
	{
		oob = UPDATE_D->global_find_player(room_owner_id());
		if (! objectp(oob))
			return notify_fail("���ݴ����޷���ѯ��ҡ�\n");
		entry = oob->query("private_room/entry");
		UPDATE_D->global_destruct_player(oob);
	} else
		entry = me->query("private_room/entry");

	if (! stringp(entry))
		return notify_fail("���ݴ����޷���ѯ���ڡ�\n");

	message_vision("$N���һ���������" + RANK_D->query_self_rude(me) +
		       "����ȥ����\n˵�գ�����һ�Ű�$n���๾������˳�ȥ��\n",
		       me, ob);
	ob->move(entry);
	message("vision", "ֻ��һ�����ӣ�һ�˲ҽ��Ŵ�����"
			  "���˳��������ص��䵽�˵��ϡ�\n",
		environment(ob), ob);
	tell_object(ob, HIR "��ֻ���û����ʹ����ͷ�����ˡ�"NOR"\n");
	ob->receive_damage("qi", 150);
	if (! ob->is_busy())
		ob->start_busy(5);
	return 1;
}

int do_knock(string arg)
{
	object me;
	string exit;
	object room;

	if (! arg || arg != "men" && arg != "door")
		return notify_fail("��Ҫ��ʲô��\n");

	if (stringp(exit = query("KEY_DOOR/exit")) &&
	    query("exits/" + exit))
		return notify_fail("��������ǿ��ģ���������ʲô��\n");

	if (! query("room_key"))
		return notify_fail("�����￪���ֲ���Կ�ף�������ʲô��\n");

	me = this_player();
	message_vision("$N����ǰȥ���������ơ��������˼����š�\n", me);

	if (objectp(room = find_object(query("KEY_DOOR/room"))))
		message("vision", "�������ơ��ļ������죬������������"
			"�����š�\n", room);

	return 1;
}

int do_unlock(string arg)
{
	object me;
	string exit;

	if (! arg || arg != "men" && arg != "door" && arg != "gate")
		return notify_fail("��Ҫ��ʲô��\n");

	if (! stringp(exit = query("KEY_DOOR/exit")))
		return notify_fail("����û������Ҫ�򿪡�\n");

	if (query("exits/" + exit))
		return notify_fail("��������ǿ��ģ����ض��һ���ˡ�\n");

	me = this_player();
	if (stringp(query("room_key")))
	{
		if (! present(query("room_key"), me) )
		{
			message("vison", me->name() + "�����������ſڸ���"
					 "���죬��֪���ڸ�ʲô��\n",
					 this_object(), ({ me }));
			tell_object(me, "����˰��쾢��Ҳû�д�����������"
					"Կ�ײ��ԡ�\n");
			return 1;
		}

		message_vision("$N�ߵ���ǰ������Կ�ף�����һŤ��ž��һ����"
			       "�ſ��ˡ�\n", me);
	} else
		message_vision("$N�ߵ���ǰ������һת�����š�\n", me);

	this_open_door();
	return 1;
}

int do_lock(string arg)
{
	string exit;

	if (! arg || arg != "men" && arg != "door" && arg != "gate")
		return notify_fail("��Ҫ����ʲô��\n");

	if (! stringp(exit = query("KEY_DOOR/exit")))
		return notify_fail("����û������Ҫ���ϡ�\n");

	if (! query("exits/" + exit))
		return notify_fail("��������Ѿ������ˣ����ض��һ���ˡ�\n");

	message_vision("$N����һ���ţ����ѵ���һ���������ˡ�\n",
		       this_player());
	this_close_door(1);
	return 1;
}

int do_break(string arg)
{
	if (! arg || arg != "men" && arg != "door" && arg != "gate")
		return notify_fail("��Ҫ�ƻ�ʲô��\n");

	if (is_room_owner(this_player()))
		return notify_fail("����ë���������Լ����ţ�Ҫ��"
				   "û��Կ����һ�ѡ�\n");

	write("�㵨�Ӳ�С����Ȼ���ô���լ��\n");
	return 1;
}

void this_open_door()
{
	string exit;
	string room;
	object ob;

	if (! stringp(exit = query("KEY_DOOR/exit")))
		return;

	if (! stringp(room = query("KEY_DOOR/room")))
		return;

	set("exits/" + exit, room);

	if (! (objectp(ob = find_object(room))))
		 catch(ob = load_object(room));

	if (! ob) return;

	message("vision", "\n��������һ���Ŵ��Ǳ߱��˴��ˡ�\n", ob);
	ob->set("exits/" + ob->query("KEY_DOOR/exit"),
		ob->query("KEY_DOOR/room"));

	remove_call_out("this_close_door");
	call_out("this_close_door", 10);
}

void this_close_door(int silent)
{
	string exit;
	string room;
	object ob;

	if (! stringp(exit = query("KEY_DOOR/exit")) ||
	    ! query("exits/" + exit))
		return;

	if (! silent)
		message("vision", "\nһ��紵�������ѵ���һ���Ź����ˡ�\n",
			this_object());
	delete("exits/" + exit);

	if (! (room = query("KEY_DOOR/room")))
		return;

	if (ob != find_object(room))
		 catch(ob = load_object(room));

	if (! ob) return;

	message("vision", "\n���ѵ���һ���Ź����ˡ�\n", ob);
	ob->delete("exits/" + ob->query("KEY_DOOR/exit"));
}

string query_save_file()
{
	string file;
	string arg;

	file = base_name(this_object());
	if (! file || ! sscanf(file, "/data/room/%s", arg)) return 0;

	return file;
}
