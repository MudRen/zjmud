#pragma optimize
#pragma save_binary

inherit F_DBASE;

#include <ansi.h>

int clean_up() { return 1; }

void auto_relaim();

void create()
{
	seteuid(ROOT_UID);
	set("channel_id", "�ڴ澫��");
	CHANNEL_D->do_channel( this_object(), "sys", "�ڴ澫���Ѿ�������");
	call_out("auto_relaim", 40);
}

void auto_relaim()
{
	int i;

	if (i = reclaim_objects())
		CHANNEL_D->do_channel( this_object(), "sys",
			sprintf("ϵͳ�Զ���� %d ��������", i));

	remove_call_out("auto_relaim");
	call_out("auto_relaim", 300 + random(60));
}
