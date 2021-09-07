// chatter.c

#include <ansi.h>
#include <command.h>
#include <net/messaged.h>

inherit F_DBASE;
inherit F_NAME;
inherit F_ALIAS;
inherit F_COMMAND;

#define MAX_FILE_SIZE   200000

#define CHAT_LOOK_CMD   "/cmds/chat/look"

static string record_string = 0;
static string command_result = 0;
static function done_input = 0;

int is_character() { return clonep(); }
int is_chatter() { return clonep(); }
int is_stay_in_room() { return 1; }

void create()
{
	set_name("������", ({ "chatter object", "chatter" }));
	seteuid(0);
}

void setup()
{
	if (! is_chatter()) return;

	seteuid(getuid());
	enable_player();

	UPDATE_D->set_title(this_object());

	// Why I add command: do_look ? Because sometime
	// this_player() will requested in the command look
	add_action("do_look", "look");
}

string find_chat_command(string verb)
{
	return (string)COMMAND_D->find_command(verb, ({ "/cmds/chat/" }));
}

string long()
{
	return "����" + name() + "��������ǡ�\n";
}

int accept_fight(object ob)
{
	message_vision("$N��æ��$n������λ" + RANK_D->query_respect(ob) +
		       "���л��ú�˵����ô����������ӣ�\n",
		       this_object(), ob);
	return 0;
}

int accept_hit(object ob)
{
	message_vision("$N���˿�$n�����˸���Ƿ���Ե����ļ��ˡ�\n",
		       this_object(), ob);
	return 0;
}

int accept_kill(object ob)
{
	message_vision("$Nһ���޹�������$n���Ե�ί�����ˡ�\n",
		       this_object(), ob);
	return 0;
}

int accept_ask(object ob, string topic)
{
	if (! strlen(topic))
		return 0;

	MESSAGE_D->tell_user(this_object(), FUN_NOTICE,
			     sprintf("%s(%s)��������йء�%s������Ϣ��\n",
				     name(1), query("id"), topic));
	return 1;
}

void start_record()
{
	record_string = "";
}

void stop_record()
{
	record_string = 0;
}

string query_record()
{
	return record_string;
}

void receive_message(string msgclass, string msg)
{
	if (record_string)
	{
		record_string += msg;
		return;
	}

	if (command_result &&
	    (this_player() == this_object()) &&
	    (msgclass == "vision" ||
	     msgclass == "tell_object" ||
	     msgclass == "write"))
	{
		command_result += msg;
		return;
	}

	MESSAGE_D->tell_user(this_object(), FUN_VISION, msg);
}

string full_name()
{
	return sprintf("%s(%s)", name(1), query("id"));
}

int visible(mixed ob)
{
	if (wiz_level(this_object()) >= wiz_level(ob))
		return 1;

	// load the environment variable from user2
	if (stringp(ob) && ! objectp(ob = MESSAGE_D->find_user(ob)))
		return 0;

	// check the setting: invisble
	if (ob->query("invisible"))
		return 0;

	return 1;
}

int force_me(string arg)
{
	int flag;
	int result;

	set_temp("notify_fail", "����Ҫ��ʲô��\n");

	// start record command result
	flag = objectp(this_player());
	if (! flag) command_result = "";

	result = ::force_me(arg);

	if (! flag)
	{
		if (sizeof(command_result))
			MESSAGE_D->tell_user(this_object(), FUN_NOTICE, command_result);

		// stop record commmand_result
		command_result = 0;
	}

	return result;
}

varargs int move(mixed dest, int raw)
{
	object ob;

	if (objectp(dest))
		ob = dest;
	else
	if (stringp(dest))
	{
		call_other(dest, "???");
		ob = find_object(dest);
		if (! ob)
		{
			MESSAGE_D->tell_object(this_object(), FUN_NOTICE,
					       HIR "���޷��ƶ���(" + HIG +
					       dest + HIR ")��"NOR"\n");
			return 0;
		}

	} else
		return 0;

	move_object(dest);
	if (! raw) CHAT_LOOK_CMD->main(this_object(), 0);
	return 1;
}

// start edit
void edit(function f, string content)
{
	if (! functionp(f) || functionp(done_input))
		return;

	done_input = f;
	delete_temp("inputed");
	if (! stringp(content))
		content = "";
	MESSAGE_D->tell_user(this_object(), FUN_INPUT, content);
}

// finish to edit
void receive_input(string msg)
{
	function f;

	if (! functionp(f = done_input))
		return;

	done_input = 0;

	if (! msg) return;

	// return the notice message
	start_record();
	catch(evaluate(f, msg));
	if (sizeof(record_string))
		MESSAGE_D->tell_user(this_object(), FUN_NOTICE, record_string);
	stop_record();
}

// new file arrival which changed by user
void new_file_arrival(string file, string content)
{
	if (file_size(file) == -2)
	{
		MESSAGE_D->tell_user(this_object(),
				     FUN_NOTICE, "�����ļ�ʧ��\n��");
		return;
	}

	write_file(file, content, 1);
	MESSAGE_D->tell_user(this_object(),
			     FUN_NOTICE, "�ɹ����޸����ļ���\n");
}

// Edit file
varargs void edit_file(string file)
{
	int fs;
	string content;

	fs = file_size(file);
	if (fs == -1)
	{
		content = "";
	} else
	if (fs >= 0 && fs <= MAX_FILE_SIZE)
	{
		content = read_file(file);
	} else
	if (fs > MAX_FILE_SIZE)
	{
		MESSAGE_D->tell_user(this_object(), FUN_NOTICE,
				     "�ļ�̫���ˣ����� FTP ���и��¡�\n");
		return;
	} else
	{
		MESSAGE_D->tell_user(this_object(), FUN_NOTICE,
				     "���ܱ༭����ļ���\n");
		return;
	}

	edit((: new_file_arrival, file :), content);
}

// Am I input now ?
int is_input()
{
	return functionp(done_input);
}

// start more text
void start_more(string msg)
{
	MESSAGE_D->tell_user(this_object(), FUN_MORE, msg);
}

// start more file
void start_more_file(string file)
{
	int fs;
	string content;

	fs = file_size(file);
	if (fs == -1)
	{
		MESSAGE_D->tell_user(this_object(), FUN_NOTICE,
				     "û������ļ���\n");
	} else
	if (fs >= 0 && fs <= MAX_FILE_SIZE)
	{
		content = read_file(file);
	} else
	if (fs > MAX_FILE_SIZE)
	{
		MESSAGE_D->tell_user(this_object(), FUN_NOTICE,
				     "�ļ�̫���ˣ����� FTP ���ز쿴��\n");
		return;
	}

	if (! content)
	{
		MESSAGE_D->tell_user(this_object(), FUN_NOTICE,
				     "��û��Ȩ����ȡ����ļ���\n");
		return;
	}

	MESSAGE_D->tell_user(this_object(), FUN_MORE, content);
}

// special command
int do_look(string arg)
{
	object me = this_object();
	object ob;
	object env;
	string msg;
	string add;
	string fun;

	if (! objectp(env = environment(me)) || env == find_object(VOID_OB))
	{
		MESSAGE_D->tell_user(me, FUN_LOOK, "�����ڴ�����翵�"
				     "����У�����ֻ�������������ǹ⡣\n");
		return 1;
	}

	if (! arg || arg == "")
	{
		arg = 0;
		if (mapp(env->query("exits")))
			// notice the user all the exits
			add = implode(keys(env->query("exits")), ",");

		fun = FUN_LOOK;
	} else
	{
		if (env->query("item_desc/" + arg, 1) ||
		    env->query("exits/" + arg, 1))
		{
			// look item
			fun = FUN_NOTICE;
		} else
		{
			// look object
			ob = present(arg, env);
			if (! ob)
			{
				MESSAGE_D->tell_user(me, FUN_NOTICE,
					"�㿴�˰��죬ȴû�ܷ���(" +
					arg + ")�ڸ�����\n");
				return 1;
			}
			fun = FUN_NOTICE;
		}
	}

	start_record();
	LOOK_CMD->main(me, arg);
	if (sizeof(record_string))
		MESSAGE_D->tell_user(me, fun, record_string, add);
	stop_record();
	return 1;
}

void move_or_destruct()
{
	if (is_chatter()) move(VOID_OB);
}

void log_command(string msg) {}
void clear_written() {}
void write_prompt() {}

string short()
{
	string str, title, nick;

	str = query("name") + "(" + query("id") + ")";
	if (! stringp(title = query_temp("title")))
		title = query("title");
	if (nick = query("nickname"))
	{
		str = "��" + nick + "��" + str;
		if (title) str = title + str;
	} else
	if (title) str = title + " " + str;

	return str;
}
