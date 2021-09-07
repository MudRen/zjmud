// heal.c

#include <ansi.h>

int exert(object me, object target)
{
	string force;

	if (me->is_fighting())
		return notify_fail("ս�����˹����ˣ�������\n");

	if (me->is_busy())
		return notify_fail("����æ������ͷ��������˵��\n");

	force = me->query_skill_mapped("force");
	if (! stringp(force))
		return notify_fail("�ȼ�����������ڹ���\n");

	if ((int)me->query("eff_qi") >= ((int)me->query("max_qi")+me->query_gain_qi()))
		return notify_fail("��������Ѫ��ӯ������Ҫ���ˡ�\n");

	if ((int)me->query_skill(force, 1) < 20)
		return notify_fail("���" + to_chinese(force) + "��Ϊ��������\n");

	if ((int)me->query("neili") < 50)
		return notify_fail("�������������\n");

	if ((int)me->query("eff_qi") < (int)me->query("max_qi") / 5)
		return notify_fail("���Ѿ����˹��أ�ֻ��һ��������������Σ�գ�\n");

	message_vision(HIW "$N" HIW "ȫ����ɣ���������ʼ�˹����ˡ�"NOR"\n",me);

	me->set_temp("pending/healing", 1);
	me->set_short_desc("�����ڵ����˹����ˡ�");
	me->start_busy((:call_other, __FILE__, "healing" :),
		       (:call_other, __FILE__, "halt_healing" :));

	return 1;
}

// ������
int healing(object me)
{
	string force;
	int recover_points;

	force = me->query_skill_mapped("force");
	if (! stringp(force))
	{
		// û�������ڹ��ˣ�
		tell_object(me, "��һʱ���Զ����������������ֻ������ͣ���ˡ�\n");
		me->set_temp("pending/healing", 0);
		me->set_short_desc(0);
		message_vision("$N̾�˿�����ҡҡ�λε�վ��������\n", me);
		return 0;
	}

	if (me->query("eff_qi") < (me->query("max_qi")+me->query_gain_qi()))
	{
		// ��Ҫ��������
		if (me->query("neili") < 50)
		{
			tell_object(me, "������������ã������ھ����м�����ת���ˡ�\n");
			me->set_temp("pending/healing", 0);
			me->set_short_desc(0);
			message_vision("$N̾�˿�����ҡҡ�λε�վ��������\n", me);
			return 0;
		}

		recover_points = 10 + (int)me->query_skill("force") / 3;
		if (me->query("breakup"))
			recover_points *= 3;
		me->receive_curing("qi", recover_points);
		me->add("neili", -50);
		switch (random(10))
		{
		case 0:
			tell_object(me, "������" + to_chinese(force) + "����"
				    "���Ѩ������ת���ƽ���ʹ��\n");
			break;
		case 1:
			tell_object(me, "�㽫�������뵤������г嶥��͸�๬"
				    "���پ�����ˬ�졣\n");
			break;
		case 2:
			tell_object(me, "�㽫����������֫���࣬���ֻ��յ��"
				    "����Ȭ�����١�\n");
			break;
		}

		return 1;
	}

	// �ָ����
	me->set_temp("pending/exercise", 0);
	me->set_short_desc(0);
	message_vision(HIY "$N" HIY "�˹���ϣ��³�һ����Ѫ����ɫ�������ö��ˡ�"NOR"\n",
		       me);
	return 0;
}

// ֹͣ����
int halt_healing(object me)
{
	tell_object(me, "�㽫�����ջص��΢΢��Ϣ��վ��������\n");
	tell_room(environment(me), me->name() + "�͵���һ������ͻȻվ��������\n", me);
	me->set_temp("pending/healing", 0);
	me->set_short_desc(0);
	if (me->query("neili") > 100)
		me->add("neili", -100);
	else
		me->set("neili", 0);
	return 1;
}
