// recover.c

int exert(object me, object target)
{
	int n, q;

	if (me != target)
		return notify_fail("��ֻ�����ڹ������Լ�����Ϣ��\n");

	if ((int)me->query("neili") < 20)
		return notify_fail("�������������\n");

	q = (int)me->query("eff_qi") - (int)me->query("qi");
	if (q < 10)
		return notify_fail("�������������档\n");
	if (me->query_skill("force")<500) 
          n = q * 100 / me->query_skill("force");
      else n = q / 5 - q * me->query_skill("force")/20000;
	if (me->query("breakup"))
		n = n * 8 / 10;
	if (n < 20)
		n = 20;
	//if (me->query("special_skill/self"))
	//	n = n * 7 / 10;

	if ((int)me->query("neili") < n)
	{
		q = q * (int)me->query("neili") / n;
		n = (int)me->query("neili");
	}

	me->add("neili", -n);
	me->receive_heal("qi", q);
	
	if (me->is_fighting())
	message_vision("$N�������˼���������ɫ�������ö��ˡ�\n", me);
        else write("���������˼���������ɫ�������ö��ˡ�\n");

	if (me->is_fighting() && ! me->query("special_skill/self"))
		me->start_busy(2);
	
	return 1;
}
