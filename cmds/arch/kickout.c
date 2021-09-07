// kickout.c

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

void kickout_player(object me, object ob);

int main(object me, string arg)
{
	object ob;

	if (! SECURITY_D->valid_grant(me, "(arch)") && !me->query("game_manager"))
		return 0;

	if (! arg)
		return notify_fail("��Ҫ��˭��\n");

	ob = LOGIN_D->find_body(arg);
	ob = MESSAGE_D->find_user(arg);
	if (! ob || ! me->visible(ob))
		return notify_fail("��... ���������?\n");

	if (! userp(ob) && base_name(ob) != USER_OB &&
	    ! ob->is_chatter())
		return notify_fail("��ֻ�ܰ�����߳�ȥ��\n");

	if (ob == me)
		return notify_fail("��Ĵ����ǲ��ǽ���ˮ��\n");

	if (wiz_level(me) < wiz_level(ob))
		return notify_fail("����ॡ���һ�������ߵ����塣\n");

	this_object()->kickout_player(me, ob);
	return 1;
}

void kickout_player(object me, object ob)
{
	object link_ob;

	if (previous_object() &&
	    ! is_root(previous_object()) &&
	    ! sscanf(base_name(previous_object()), "/clone/special/%*s"))
		return;

	log_file("static/kickout_player", sprintf("%s %-9s kickout %s\n",
			log_time(), geteuid(me), geteuid(ob)));

	tell_object(me, "���" + ob->query("name") + "ǿ���˳�����Ϸ��\n");
	tell_object(ob, "�㱻" + me->query("name") + "ǿ���˳�����Ϸ��\n");
	CHANNEL_D->do_channel(this_object(), "rumor",
			      sprintf("%s��%sǿ���˳�����Ϸ��",
			      ob->name(), me->name()));
	seteuid(ROOT_UID);
	if (ob->is_chatter())
	{
		MESSAGE_D->user_logout(ob, "�㱻" + me->name(1) +
					   "���˳�ȥ��\n");
		return;
	}

	if (objectp(link_ob = ob->query_temp("link_ob")))
	{
		catch(link_ob->save());
		destruct(link_ob);
	}

	catch(ob->save());
	destruct(ob);
	seteuid(getuid());
}

int help(object me)
{
write(@HELP
ָ���ʽ : kickout <ĳ��>

HELP );
    	return 1;
}
