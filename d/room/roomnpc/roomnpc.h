// major function of room's npc

int is_owner(object ob)
{
	if (ob->query("id") == environment()->query("room_owner_id") ||
	    ob->query("couple/id") == environment()->query("room_owner_id"))
		return 1;

	return 0;
}

int is_owner_permit(object ob)
{
	if (ob->query_temp("permit_enter/" + environment()->query("room_owner_id")))
		return 1;

	if (objectp(present(environment()->query("room_owner_id") + " pass", ob)))
		return 1;

	return 0;
}

int owner_is_present()
{
	string id;

	if (present(id = environment()->query("room_owner_id")))
		return 1;

	return 0;
}

int do_invite(string arg)
{
	object ob;
	object me;

	if (! arg || ! objectp(ob = present(arg, environment())))
		return notify_fail("��Ҫ����˭��\n");

	if (! ob->is_character())
		return notify_fail("������������������������·����\n");

	if (! ob->query("can_speak"))
		return notify_fail("����˼����������û�������һ�����ˡ���\n");

	if (ob == me)
		return notify_fail("��Ҫ�������Լ����뷨������ϧû���á�\n");

	if (is_owner(ob))
		return notify_fail("����Ҳ������������ˣ���ʲô������ģ�\n");

	if (! userp(ob))
		return notify_fail("�����㻹�Ǳ������ˡ�\n");

	me = this_player();
	message_vision("$Nָ��" + ob->name() + "��$n������������������"
		       "���ˣ���ɲ�Ҫ�����ˣ���\n$n��æ��ͷ����������"
		       "֪���ˣ�֪���ˣ���λ" + RANK_D->query_respect(ob) +
		       "��С�����в��ܾ����ᣡ��\n", me, this_object());
	ob->set_temp("permit_enter/" + me->query("id"), 1);
	return 1;
}

int do_show(string arg)
{
	object ob;
	object me;
	string msg;

	if (! arg)
		return notify_fail("��Ҫ����ʲô������\n");

	me = this_player();
	if (! objectp(ob = present(arg, me)))
		return notify_fail("������û�����ֶ�����\n");
 
	msg = "$N����һ" + ob->query("unit") + ob->name() + "��\n";
	if (! ob->id(environment()->query("room_owner_id") + " pass"))
		msg += "����$n��û����$n��\n";
	else
		if (is_owner_permit(me))
			msg += "$n������Ц����$N������ʧ����ʧ������\n";
		else
		{
			msg += "$nһ����������Ц����$N������ԭ����" +
			       environment()->query("room_owner") +
			       "�����ѣ�ʧ����ʧ������\n";
			me->set_temp("permit_enter/" +
				     environment()->query("room_ownerid"), 1);
		}
	message_vision(msg, me, this_object());
	return 1;
}
