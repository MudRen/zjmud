// illness.c

inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
	int need_lvl;
	int need_neili;
	string cname;

	need_lvl = duration + 60;
	need_neili = duration * 10;
	if (me != ob)
		need_lvl = need_lvl * 3 / 2;
	if (me != ob)
		need_neili = need_neili * 3 / 2;

	cname = to_chinese(this_object()->name());
	if (need_lvl > me->query_skill("force"))
	{
		if (me == ob)
		{
			tell_object(me, "����ڹ��������Ƿȱ���޷�����" + cname +"��\n");
			return -1;
		} else
		{
			tell_object(me, "����ڹ��������Ƿȱ���޷�����" + ob->name() + "����" + cname + "��\n");
			return -1;
		}
	}

	if (me->query("neili") < need_neili)
	{
		tell_object(me, "����������ڲ��㣬�޷�ʩչ������" + cname + "��\n");
		return -1;
	}
	me->add("neili", -need_neili);

	if (me == ob)
	{
		tell_object(me, "��Ϣ�Ժ���������ˣ��о�" + cname + "�������ˡ�\n");
	} else
	{
		tell_object(me, "�㽫�������������뵽" + ob->name() + "������" +
			    ob->name() + "����һ��\n");
		tell_object(ob, "�����" + me->name() +
			    "��������������澭��������������ˣ��о�" + cname + "�������ˡ�\n");
	}

	ob->clear_condition(this_object()->name());

	return 1;
}
