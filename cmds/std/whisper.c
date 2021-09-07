// whisper.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string dest, msg;
	object ob;
	object env;
	mixed info;

	if (! arg || sscanf(arg, "%s %s", dest, msg) != 2)
		return notify_fail("��Ҫ��˭����Щʲô��\n");

	env = environment(me);
	ob = present(dest, env);
	if (! ob || ! ob->is_character())
		return notify_fail("��Ҫ��˭���\n");

	if (me->ban_say(1))
		return 0;

	if (info = env->query("no_say"))
	{
		if (stringp(info))
		{
			write(info);
			return 1;
		}

		write("����ط����ܽ�����\n");
		return 1;
	}

	write(WHT "����" + ob->name() + WHT "�Ķ�������˵����" +
	      msg + ""NOR"\n");
	tell_room(environment(me), me->name() + "��" + ob->name()
		+ "����С����˵��Щ����\n", ({ me, ob }));
	if (! userp(ob)) ob->relay_whisper(me, msg);
	else
		tell_object(ob, WHT + me->name() +
				WHT "����Ķ�������˵����" + msg + ""NOR"\n");
	return 1;
}

int help(object me)
{
	write( @TEXT
ָ���ʽ��whisper <ĳ��> <ѶϢ>

���ָ�����������ͬһ�����е��˶������ NPC ���ڡ�
TEXT );
	return 1;
}
