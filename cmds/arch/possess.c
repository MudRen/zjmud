// possess.c
// updated by doing

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	if (! SECURITY_D->valid_grant(me, "(arch)"))
		return 0;

	if (! arg)
		return notify_fail("��Ҫ��˭����\n");

	if (! me->is_admin())
		return notify_fail("�㲻�ܸ���\n");

	ob = present(arg, environment(me));

	if (! ob || ! living(ob))
		return notify_fail("����û��������\n");

	if (geteuid(ob) != geteuid(me))
		return notify_fail(ob->name() + "�� euid ���㲻�ϣ���"
				   "�����и���\n");

	if (ob->query_temp("body_ob"))
		return notify_fail( ob->name() + "�Ѿ����˸�����ˡ�\n");

	message_vision("$N����һ����â���$n���ڡ�\n", me, ob);
	LOGIN_D->enter_world(me, ob, 1);
	ob->clear_written();
	ob->write_prompt();
	return 1;
}

int help()
{
	write(@TEXT
ָ���ʽ��posssess <Ŀ������>

������һ�������ϣ������������������ͬ�� EUID��
�������� quit ָ���ص�ԭ�������塣
TEXT );
	return 1;
}

