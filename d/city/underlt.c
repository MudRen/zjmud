// underlt.c
// ��̨����

inherit ROOM;

#define LEITAI	  __DIR__ "leitai"

int is_chat_room() { return 1; }

void init()
{
	add_action("do_pass", "pass");
}

void init_here()
{
}

int valid_leave(object me, string dir)
{
	object ob;
	string dest;

	dest = query("exits/" + dir);
	if (! stringp(dest))
		return ::valid_leave(me, dir);

	ob = find_object(dest);
	if (! objectp(ob) || wizardp(me))
		return ::valid_leave(me, dir);

	if (ob->refuse(me))
		return notify_fail("���ʲô���֣����ڲ�������ȥ��ʱ��\n");

	return ::valid_leave(me, dir);
}

int do_pass(string arg)
{
	object me;
	object ob;
	object ob_leitai;

	me = this_player();

	if (! arg ||
	    ! objectp(ob = present(arg, this_object())))
		return notify_fail("������˭��ȥ��\n");

	if (ob == me)
		return notify_fail("��Ͳ����Լ�����ȥ��\n");

	if (! ob->is_character())
		return notify_fail("���ǲ��Ǵ��Խ���ˮ��\n");

	if (! userp(ob))
		return notify_fail("��ͱ��ͱ��" + ob->name() + "�������˼�û����\n");

	if (! living(ob))
		return notify_fail("�ô����Ū���˼Ұɣ�\n");

	ob_leitai = find_object(LEITAI);
	if (! objectp(ob_leitai))
		ob_leitai = load_object(LEITAI);
	if (! objectp(ob_leitai))
		return notify_fail("��̨�����\n");

	message_vision("$N���ͷ����$n����������ȥ�ɡ���\n"
		       "ֻ��$nĦȭ���ƣ�ӻԾ����̨ȥ��\n",
		       me, ob);
	message("vision", "ֻ��" + ob->name() + "Ծ��̨�����ý�֮����\n",
		ob_leitai);
	ob->move(ob_leitai);
	return 1;
}
