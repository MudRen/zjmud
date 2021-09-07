// channel block command..

#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	
	if (! SECURITY_D->valid_grant(me, "(wizard)") && !me->query("game_manager"))
		return 0;

	if (! arg)
		return notify_fail("ָ���ʽ: chblk <player id>\n");
    
	ob = UPDATE_D->global_find_player(arg);
	if (! ob)
		return notify_fail(LOCAL_MUD_NAME() + "��û������ˣ�\n");

	if (wiz_level(ob) > 0)
	{
		UPDATE_D->global_destruct_player(ob);
		return notify_fail("�㲻�ܹر���ʦ��Ƶ����\n");
	}

	if (ob->query("chblk_on"))
	{
		UPDATE_D->global_destruct_player(ob);
		return notify_fail("����˵�Ƶ���Ѿ����ر��ˡ�\n");
	}

	ob->set("chblk_on", 1);
	ob->set("chblk_by", geteuid(me));
	write("��ر���" + ob->name(1) + "��Ƶ����\n");
	tell_object(ob, me->name(1) + "�ر������Ƶ����\n");

	UPDATE_D->global_destruct_player(ob, 1);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : chblk <���>

������ر�ĳ����ҵ�Ƶ����

HELP );
	return 1;
}
