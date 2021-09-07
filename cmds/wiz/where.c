// where.c
// 06-14-95

inherit F_CLEAN_UP;

int main(object me, string str)
{
	object ob, where, *ob_list;
	int i;

	if (! SECURITY_D->valid_grant(me, "(wizard)"))
		return 0;

	if (! str)
		return notify_fail("ָ���ʽ��where <�������>\n"); 

	ob = find_player(str);
	if (! ob) ob = find_living(str);
	if (! ob || ! me->visible(ob))
	{
		str = resolve_path(me->query("cwd"), str);
		ob = find_object(str);
	}

	if (! ob)
		return notify_fail("û���ҵ������Ʒ��\n");

	where = environment(ob);
	if (! where)
		return notify_fail("����˲�֪��������Ү...\n");

	write(sprintf("%s(%s)������%s(%s).\n",
		(string)ob->name(1),
		(string)ob->query("id"),
		(string)where->short(),
		(string)file_name(where)));
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ: where <����ID>

���ָ����������֪����Ŀǰ���ڵ�λ��.

HELP );
	return 1;
}

