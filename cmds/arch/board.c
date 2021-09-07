// board.c
// created by doing

#include <ansi.h> 
#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string *file;
	string msg;
	string board;
	int i, j;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	seteuid(getuid());

	file = map_array(get_dir("/clone/board/"), (: "/clone/board/" + $1 :));
	i = sizeof(file);
	if (! i)
	{
		write("Ŀǰû���κ����԰档\n");
		return 1;
	}

	if (arg)
	{
		sscanf(arg, "%d", j);
		j--;
		if (j < 0 || j >= i)
			return notify_fail("û��������԰塣\n");

		return me->force_me("goto " + file[j]->query("location"));
	}

	msg = "Ŀǰ" + LOCAL_MUD_NAME() + "�����԰���������Щ��\n";
	for (j = 0; j < i; j++)
		msg += sprintf(HIY "%2d" NOR ". %s\n", j + 1, file[j]->short());

	msg += "�� board n ȥ�����뿴�����԰塣\n";
	write(msg);
	return 1;
}
