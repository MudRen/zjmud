// regenerate.c

int exert(object me, object target)
{
	int neili_cost;
	int lvl;
	int heal;

	if (target != me)
		return notify_fail("��ֻ�����ڹ��ָ��Լ��ľ�����\n");
	
	if (! me->query_skill_mapped("force"))
		return notify_fail("������ȼ�����ʹ�õ��ڹ���\n");

	heal = (int)me->query("eff_jing") - (int)me->query("jing");
	if (heal < 10)
		return notify_fail("�����ھ�����ʢ��\n");

	lvl = me->query_skill("force");
	if (lvl <= 0) lvl = 1;
	neili_cost = heal * 60 / lvl;
	if (me->query("breakup"))
		neili_cost = neili_cost * 7 / 10;
	if (neili_cost < 20) neili_cost = 20;
	if (neili_cost > me->query("neili"))
	{
		neili_cost = me->query("neili");
		heal = neili_cost * lvl / 60;
	}
	if (neili_cost < 20) neili_cost = 20;

	if ((int)me->query("neili") < neili_cost)
		return notify_fail("�������������\n");

	me->add("neili", -neili_cost);
	me->receive_heal("jing", heal);
	
	if (me->is_fighting())
	message_vision("$N�������˼����������������ö��ˡ�\n", me);
        else tell_object(me, "���������˼����������������ö��ˡ�\n");
        //else write("���������˼����������������ö��ˡ�\n");

	if (me->is_fighting()) me->start_busy(2);
	
	return 1;
}
