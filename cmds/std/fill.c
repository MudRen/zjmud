// drink.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	mapping my;
	object ob;
	function f;

	if (! arg)
		return notify_fail("��Ҫ��ʲô��������ࣿ\n");

	if (! environment(me)->query("resource/water"))
		return notify_fail("����û�еط�����װˮ��\n");

	if (me->is_busy())
		return notify_fail("����һ��������û����ɡ�\n");

	if (me->is_fighting())
		return notify_fail("����æ�Ŵ�ܣ�û����װˮ��\n");

	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û������������\n");

	if (! mapp(my = ob->query("liquid")))
		return notify_fail("�������װ����ˮ��\n");

	if (my["remaining"] && my["name"] != "��ˮ")
		message_vision("$N��" + ob->name() + "��ʣ�µ�" +
			       my["name"] + "������\n", me);

	message_vision("$N��" + ob->name() + "װ����ˮ��\n", me);

	my["type"] = "water";
	my["name"] = "��ˮ";
	my["remaining"]  = ob->query("max_liquid");
	my["drink_func"] = 0;

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : fill <����>
 
���ָ���������ˮ�ĵط�������������ˮ��
 
HELP
    );
    return 1;
}
 