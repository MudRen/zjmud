// drive.c
//
// ���Լ�ʻ����Ʒ

#include <dbase.h>

int is_transport() { return 1; }

void set_owner(object me)
{
	set_temp("owner", me);
}

object query_owner()
{
	return query_temp("owner");
}

// ���Ƿ���Լ�ʻ��
int can_drive_by(object me)
{
	object owner;

	if (! objectp(owner = query_owner()))
		return 1;

	if (owner == me || environment(owner) != environment())
		return 1;

	return notify_fail("����" + owner->name() + "�ĳ������Ҷ�ʲô��\n");
}
