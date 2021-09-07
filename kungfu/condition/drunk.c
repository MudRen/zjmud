// drunk.c

inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
	int need_lvl;

	need_lvl = duration + 50;
	if (me != ob)
		need_lvl = need_lvl * 3 / 2;;

	if (need_lvl > me->query_skill("force"))
	{
		if (me == ob)
		{
			tell_object(me, "����ڹ��������Ƿȱ���޷�������Ƶ�Ӱ�졣\n");
			return -1;
		} else
		{
			tell_object(me, "����ڹ��������Ƿȱ���޷�����" + ob->name() + "������Ƶ�Ӱ�졣\n");
			return -1;
		}
	}

	if (me == ob)
	{
		tell_object(me, "��Ϣ�Ժ������Ѷ��ˣ���û�а����Ƶĸо���\n");
	} else
	{
		tell_object(me, "�㽫�������������뵽" + ob->name() + "������" +
			    ob->name() + "����һ��\n");
		tell_object(ob, "�����" + me->name() +
			    "��������������澭�����������Ѷ��ˣ���û����Ƶĸо���\n");
	}

	ob->clear_condition("drunk");

	return 1;
}

int update_condition(object me, int duration)
{
	int limit;

	limit = (me->query("con") + (int)me->query("max_neili") / 50) * 2;

	if (duration > limit && living(me))
	{
		me->unconcious();
		return 0;
	} else if (!living(me))
	{
		message("vision", me->name() + "���˸�����������Ȼ�������ࡣ\n",
			environment(me), me);
	} else if (duration > limit / 2)
	{
		tell_object(me, "��������л�������������ƮƮ�أ���������ˡ�\n");
		message("vision", me->name() + "ҡͷ���Ե�վ��վ���ȣ���Ȼ�Ǻ����ˡ�\n",
			environment(me), me);
		me->receive_damage("jing", 10);
	} else if (duration > limit/4)
	{
		tell_object(me, "�����һ������ϳ壬��Ƥ��Щ�����ˡ�\n");
		message("vision", me->name() + "�����Ѿ����Ծ����ˡ�\n",
			environment(me), me);
		me->receive_healing("jing", 10);
		me->receive_healing("qi", 15);
	}

	me->apply_condition("drunk", duration - 1);
	if (! duration) return 0;
	return 1;
}
