// promote.c
// updated by doing

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string old_status, new_status;
	int my_level, ob_level, level;
	int sp_flag;

	if (! VERSION_D->is_release_server() && me->is_admin())
		sp_flag = 1;
	else
		sp_flag = 0;

	if (! sp_flag && ! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg || sscanf(arg, "%s %s", arg, new_status) != 2)
		return notify_fail("ָ���ʽ��promote <ʹ����> <�ȼ�>\n");

	if (wiz_level(new_status) < 0)
		return notify_fail("û�����ֵȼ���\n");

	ob = UPDATE_D->global_find_player(arg);
	if (! objectp(ob))
		return notify_fail("��ֻ�ܸı�ʹ���ߵ�Ȩ�ޡ�\n");

	if (! sp_flag &&
	    (wiz_level(me) < wiz_level(new_status) ||
	     wiz_level(me) < wiz_level(ob)))
	{
		UPDATE_D->global_destruct_player(ob, 1);
		write("��û������Ȩ����\n");
		return 1;
	}

	old_status = wizhood(ob);

	seteuid(getuid());
	if (! (SECURITY_D->set_status(ob, new_status)))
	{
		UPDATE_D->global_destruct_player(ob, 1);
		write("�޸�ʧ�ܡ�\n");
		return 1;
	}

	message_vision("$N��$n��Ȩ�޴� " + old_status + " ��Ϊ " +
		       new_status + " ��\n", me, ob);
	seteuid(getuid());
	ob->setup();

	UPDATE_D->global_destruct_player(ob, 1);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : promote <ĳ��> (Ȩ�޵ȼ�)

��������Ȩ�޵ȼ�, (player) (immortal) (apprentice) (wizard)
(arch) (admin)
һ�� admin ������Ȩ�����κεȼ�, �� arch ֻ�������� arch��
HELP );

	return 1;
}
