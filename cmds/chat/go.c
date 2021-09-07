// go.c

#include <ansi.h>
#include <command.h>
#include <net/messaged.h>

inherit F_CLEAN_UP;
void send_exits(object me, object env);

int main(object me, mapping info)
{
	string arg;
	object env;
	object ob;
	mapping exits;

	if (! objectp(env = environment(me)) || env == find_object(VOID_OB))
	{
		MESSAGE_D->tell_user(me, FUN_NOTICE, "�����ڴ�����翵�"
				     "����У�����һƬãã��ûʲô�ط���ȥ�ġ�\n");
		return 1;
	}

	arg = info[ARG];
	if (! stringp(arg))
	{
		send_exits(me, env);
		return MESSAGE_D->error_msg("��Ҫȥ���\n");
	}

	if (! mapp(exits = env->query("exits")))
	{
		send_exits(me, env);
		return MESSAGE_D->error_msg("�������ܶ�û�г��ڣ�����·���ߡ�\n");
	}

	if (! exits[arg])
	{
		send_exits(me, env);
		if (env->query("outdoor"))
			return MESSAGE_D->error_msg("��̧�����ߣ�ȴ����һ��ǽ��\n");
		else
			return MESSAGE_D->error_msg("�������û�г��ڡ�\n");
	}

	call_other(exits[arg], "???");
	if (! find_object(ob = exits[arg]))
	{
		send_exits(me, env);
		return MESSAGE_D->error_msg("ϵͳ�����˴����޷������Ĳ�����\n");
	}

	if (! wizardp(me) || ! me->query("env/invisible"))
	{
		message("vision", me->name() + "ƮƮ�������뿪���\n",
			environment(me), ({ me }));
		message("vision", me->name() + "ƮƮ�������ε��˹�����\n",
			ob, ({ me }));
	}

	if (! me->move(ob))
	{
		send_exits(me, env);
		return MESSAGE_D->error_msg("���޷��ƶ���ָ���ĵص㡣\n");
	}

	return 1;
}

void send_exits(object me, object env)
{
	if (mapp(env->query("exits")))
		// notice the user all the exits
		MESSAGE_D->tell_user(me, FUN_EXITS, implode(keys(env->query("exits")), "\n"));
}

