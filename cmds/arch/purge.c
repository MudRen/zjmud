// purge.c

#include <ansi.h>

#define SYNTAX	"ָ���ʽ��purge <ʹ��������> because <ԭ��>\n"

inherit F_CLEAN_UP;

private int do_purge_players(int day);

int main(object me, string arg)
{
	string name, reason;
	int day;
	object ob;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg)
		return notify_fail(SYNTAX);

	if (sscanf(arg, "%s because %s", name, reason) != 2)
		return notify_fail(SYNTAX);

	if (wiz_level(me) <= wiz_level(name) && ! is_root(me))
		return notify_fail("��û��Ȩ��ɾ��������\n");

	seteuid(getuid());
	if (file_size(DATA_DIR + "login/" + name[0..0] + "/" + name + __SAVE_EXTENSION__) < 0)
		return notify_fail("û����λʹ���ߡ�\n");

	if (ob = find_player(name))
		CHANNEL_D->do_channel(this_object(), "rumor", "ʹ����" +
				      ob->query("name") + "��" +
				      me->query("name") + "ɾ���ˡ�");

	// remove the user from disk
	UPDATE_D->remove_user(name);

	tell_object(me, "ʹ���� " + capitalize(name) + " ɾ�����ˡ�\n");
	log_file("static/purge", sprintf("%s %s purged %s because %s.\n",
		 log_time(), geteuid(this_player(1)), name, reason));

	return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ��purge <ʹ��������> because <ԭ��>

���һ��ʹ���߻��������һ�������������ߵ�ʹ���ߡ�
HELP );
    return 1;
}
