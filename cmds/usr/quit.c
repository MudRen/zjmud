// quit.c

#include <command.h>
#include <config.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

void create() 
{
	seteuid(getuid());
	set("name", "����ָ��");
	set("id", "quit");
	set("channel_id", "����");
}

int main(object me, string arg)
{
	int i;
	int doing;
	object *inv, link_ob;

	if (LOGIN_D->get_madlock()) 
		return notify_fail("ʱ���Ѿ���գ�û�����ܹ��˳����ʱ���ˡ�\n");

	if (me->is_busy() && ! me->query("doing"))
		return notify_fail("��������æ���������£������˳���Ϸ��\n");

	if (me->query_condition("killer"))
		return notify_fail("���������ڱ�ͨ�������������˳���Ϸ��\n");

	if (me->is_fighting())
		return notify_fail("���������ڴ�ܣ���ô��˵�߾��ߣ�\n");

	if (me->query_competitor())
		return notify_fail("�üһ�����ں��˱��䣬��ô�ܿ��\n");

	if (me->dps_count() > 0)
		return notify_fail("�üһ������˱��˾��뿪�\n");

//	if (me->over_encumbranced())
//		return notify_fail("�����ϱ��Ķ���̫���ˣ��޷��뿪������硣\n");

	if (me->run_override("quit"))
		return 1;

	link_ob = me->query_temp("link_ob");

	if (objectp(link_ob))
	{
		// Are we possessing in others body ?
		if (link_ob->is_character())
		{
			write("��Ļ��ǻص�" + link_ob->name(1) + "�����ϡ�\n");
			exec(link_ob, me);
			link_ob->setup();
			link_ob->write_prompt();
			return 1;
		}

		if (link_ob->query_temp("ip_number"))
		{
			link_ob->set("last_on", time());
			link_ob->set("last_from",
				     link_ob->query_temp("ip_number"));
			link_ob->set("registered",
				     me->query("registered"));
			link_ob->save();
		}
		destruct(link_ob);
	}

	if (me->query("doing")||(environment(me)&&environment(me)->query("close_room")))
	{
		if (! interactive(me))
			return 1;

		write("����ʱ���ߣ����ﲻ�˳�...\n");
		message("vision", me->name() + "�����ˡ�\n",environment(me), ({ me }));
		me->save();
		link_ob = new(LOGIN_OB);
		exec(link_ob, me);
		destruct(link_ob);
		return 1;
	}

#if INSTALL_EXAMINE
	EXAMINE_D->examine_player(me);
#endif

	me->log_command("quit");
	me->force_me("unset sign1");
	me->force_me("team dismiss");
	write("��ӭ�´�������\n");
	if (environment(me))
	{
		if(environment(me)->query("out_room"))
		{
			environment(me)->no_die(me);
			me->move(environment(me)->query("out_room"));
		}
		message("vision", me->name() + "�뿪��Ϸ��\n",environment(me), ({ me }));
	}

	CHANNEL_D->do_channel(this_object(), "sys",me->name() + "[" + me->query("id") + "]�뿪��Ϸ�ˡ�");


	log_file("stat", sprintf("%-8s %-10s %-18s %-18s %-15s.\n",
				 me->name(1), me->query("id"),
				 ctime(me->query_temp("logon_time")),
				 ctime(time()),
				 interactive(me) ? query_ip_number(me) : "unknow"));

	me->save();
	me->set_magic_move();
	me->end_log();
	destruct(me);
	return 1;
}

int force_quit(object me)
{
	if (previous_object() != me ||
	    ! playerp(me))
		return notify_fail("�㲻�ܴݻ��������\n");

	seteuid(getuid());
	me->save();
	if (environment(me) != find_object(VOID_OB))
		me->move(VOID_OB, 1);
	destruct(me);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : quit | exit

����(��)����ʱ�뿪ʱ, �����ô�һָ�
HELP );
    return 1;
}

