// channel block command..
// Modified by Marz, 04/18/96
// updated by doing

#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	
	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	if (! arg)
		return notify_fail("ָ���ʽ: unchblk <player id>\n");
		
	ob = UPDATE_D->global_find_player(arg);
	if (! ob)
		return notify_fail(LOCAL_MUD_NAME() + "��û������ˣ�\n");

	if (! ob->query("chblk_on"))
	{
		UPDATE_D->global_destruct_player(ob);
		return notify_fail("����˵�Ƶ��Ŀǰ�úõġ�\n");
	}

	ob->delete("chblk_on");
	ob->delete("chblk_by");
	write("�����" + ob->name(1) + "��Ƶ����\n");
	tell_object(ob, me->name(1) + "�������Ƶ����\n");

	UPDATE_D->global_destruct_player(ob, 1);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : unchblk <���>

�������ĳ����ҵ�Ƶ����

HELP );
	return 1;
}
