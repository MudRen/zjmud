// slumber_drug.c

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
	int limit;

	limit = (int)me->query("neili") / 50;

	tell_object(me, "��������л����������пյ����ģ�ֱ��������˯һ����\n");
	message("vision", me->name() + "ҡͷ���Ե�վ��վ���ȣ����������һ����\n",
		environment(me), me);
	if( duration > limit ) {
		if ( living(me) ) me->unconcious();
		return 0;
	} else 
	if (me->query("neili") > 500) {
		tell_object(me, "�㷢���������һ��������ʱ�����˲��١�\n");
		me->add("neili", -100);
		return 0;
	}

	if ( duration > 1 )
	{
		me->apply_condition("slumber_drug", duration - 1);
		return 1;
	}

	return 0;
}
