// inspire.c

#include <ansi.h>

int exert(object me, object target)
{
	string force;

	if (! me->query("breakup"))
		return notify_fail("�㻹û����������������������ľ��ϣ�ֻ�д�ͨ�ζ�����֮�����ʹ������\n");

	if (me->is_fighting())
		return notify_fail("����������ս���У����ǵȴ�������˵�ɣ�\n");

	force = me->query_skill_mapped("force");
	if (! stringp(force))
		return notify_fail("�ȼ�����������ڹ���\n");

	if ((int)me->query_skill(force, 1) < 200)
		return notify_fail("���" + to_chinese(force) + "��Ϊ��������\n");

	if ((int)me->query("eff_jing") >= (int)me->query("max_jing"))
		return notify_fail("�����ھ���������ʲô�ü����ģ�\n");

	if ((int)me->query("neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query("eff_jing") < (int)me->query("max_jing") / 3)
		return notify_fail("��ľ�����̫�أ�������������Լ���\n");

	message_vision(HIW "$N" HIW "��ϥ���£���Ŀڤ�񣬻����ĺ������ɡ�"NOR"\n", me);
	me->set_temp("pending/inspiring", 1);
	me->set_short_desc("�����ڵ����˹����ˡ�");
	me->start_busy((:call_other, __FILE__, "inspiring" :),
		       (:call_other, __FILE__, "halt_inspiring" :));
	return 1;
}

// �����
int inspiring(object me)
{
	string force;
	int recover_points;

	force = me->query_skill_mapped("force");
	if (! stringp(force))
	{
		// û�������ڹ��ˣ�
		tell_object(me, "��һʱ���Զ����������������ֻ������ͣ���ˡ�\n");
		me->set_temp("pending/inspiring", 0);
		me->set_short_desc(0);
		message_vision("$N̾�˿�����ҡҡ�λε�վ��������\n", me);
		return 0;
	}

	if (me->query("eff_jing") < me->query("max_jing"))
	{
		// ��Ҫ��������
		if (me->query("neili") < 100)
		{
			tell_object(me, "������������ã������ھ����м�����ת��ܡ�\n");
			me->set_temp("pending/healing", 0);
			me->set_short_desc(0);
			message_vision("$N̾�˿�����ҡҡ�λε�վ��������\n", me);
			return 0;
		}

		recover_points = 5 + (int)me->query_skill("force") / 6;
		me->receive_curing("jing", recover_points);
		me->add("neili", -100);
		switch (random(10))
		{
		case 0:
			tell_object(me, "������" + to_chinese(force) + "�������Ѩ������ת����ܾ���\n");
			break;
		case 1:
			tell_object(me, "�㽫�������뵤������г嶥��͸�๬���پ�����ˬ�졣\n");
			break;
		case 2:
			tell_object(me, "����ת�����������������ɣ���ͷ��������㺹�飬�漴�����������ڶ���\n");
			break;
		}

		return 1;
	}

	// �ָ����
	me->set_temp("pending/exercise", 0);
	me->set_short_desc(0);
	message_vision(HIY "$N" HIY "��������˫Ŀ���������䣬������ˬ��"NOR"\n",me);
	return 0;
}

// ֹͣ����
int halt_inspiring(object me)
{
	tell_object(me, "�㽫�����ջص��΢΢��Ϣ��վ��������\n");
	tell_room(environment(me), me->name() + "�͵���һ������ͻȻվ��������\n", me);
	me->set_temp("pending/inspiring", 0);
	me->set_short_desc(0);
	return 1;
}

