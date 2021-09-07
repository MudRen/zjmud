// item.c

#include <dbase.h>
#include <move.h>
#include <name.h>

inherit F_CLEAN_UP;
inherit F_DBASE;
inherit F_MOVE;
inherit F_NAME;

static string s_name;
static string s_id;

void setup()
{
	seteuid(getuid());
}

void set_name(string name, string *id)
{
	::set_name(name, id);
	s_name = ::query("name");
	s_id = ::query("id");
}

string short()
{
	return s_name + "(" + this_object()->real_id() + ")";
}

void clean_me()
{
	string msg;
	object env;

	env = environment();

	if (env->is_character())
	{
		remove_call_out("clean_me");
		return;
	}

	destruct(this_object());
	return;
}

int fire(object me, object ob)
{
	string msg;

	if (this_object()->is_item_make())
		return notify_fail("���۵���ͷ�󺹣���ô��Ҳ�㲻�š�\n");

	if (stringp(msg = query("no_light")))
		return notify_fail(msg);

	switch (query("material"))
	{
	case "wood":
		msg = "$N��$n����$f�����ȼ�ˣ��������������ֻʣ����һ��̼��������\n";
		break;
	case "leather":
	case "feather":
	case "silk":
		msg = "$N��$f��$n�����ˣ����ɢ����һ���������ŵĳ�ζ��\n";
		break;
	case "paper":
	case "cloth":
		msg = "$N������$n���������˼������ܿ�����˸��ɸɾ�����ʲô��û��ʣ������\n";
		break;
	default:
		return notify_fail("�ⶫ������ȥû���㣬����ʡʡ�����ɡ�\n");
	}

	msg = replace_string(msg, "$n", name());
	msg = replace_string(msg, "$f", ob->name());
	message_vision(msg, me);
	destruct(this_object());
	return 1;
}
