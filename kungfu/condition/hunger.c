// hunger.c

#include <condition.h>
#include <ansi.h>

int dispel() { return 0; }

int update_condition(object me, int duration)
{
	object *inv;
	int i;
	if (me->query("food") > 0 && me->query("water") > 0)
		return 0;

	if (me->query("zjvip/times") > 0)
		{
			tell_object(me, HIY "����ö��ӹ���ֱ�У��Һö���ʹ�߸��������������ţ�̣���ݺݵس��˼���, ���úù���һ�� ..."NOR"\n");
			me->set("food", me->max_food_capacity());
			me->set("water", me->max_food_capacity());
			return 0;
		}

	if (! interactive(me) || ! environment(me) || environment(me)->is_chat_room())
		return CND_CONTINUE;

	if (duration == 4)
	{
		if (me->query("food") <= 0 && me->query("water") <= 0)
		{
			tell_object(me, HIY "�����ͷ���ۻ����ʵú���ð�̣��Ͻ��ҵ�Եİɡ�"NOR"\n");
		}
		else if (me->query("food") <= 0)
		{
			tell_object(me, HIY "�����ͷ���ۻ�������Ҫ�Ͽ��ҵ�Ե��ˡ�"NOR"\n");
		}
		else if (me->query("water") <= 0)
		{
			tell_object(me, HIY "��ʵú���ð�̣�����Ҫ�Ͽ�ȵ�ʲô�ˡ�"NOR"\n");
		}
	}
	else
	if (duration == 7)
	{
		if (me->query("food") <= 0 && me->query("water") <= 0)
			tell_object(me, HIR "���ּ��ֿʣ������Լ���Ҫ���ˡ�"NOR"\n");
		else
		if (me->query("food") <= 0)
			tell_object(me, HIR "����ÿ����ˡ�"NOR"\n");
		else
		if (me->query("water") <= 0)
			tell_object(me, HIR "��ʵ�Ҫ�����ˡ�"NOR"\n");
	}
	else
	if (duration >= 13)
	{
		if (me->query("age") < 16)
		{
			tell_object(me, HIY "���ۿ���Ҫ�����ˣ�ͻȻ���ϵ���һֻ��Ѽ��һ���׾ƣ���һ�����ĺȣ��о������Ǻö��ˡ�"NOR"\n");
			me->set("food", me->max_food_capacity());
			me->set("water", me->max_food_capacity());
			return 0;
		}

		if (me->query("food") <= 0 && me->query("water") == 0)
			tell_object(me, HIR "���ּ��ֿʣ���ʱ�������ε���ȥ��"NOR"\n");
		else
		if (me->query("food") <= 0)
			tell_object(me, HIR "�������ʱ�������ε���ȥ��"NOR"\n");
		else
		if (me->query("water") <= 0)
			tell_object(me, HIR "��ʵ���ʱ�������ε���ȥ��"NOR"\n");
		if(me->query("qi")>5)
			me->receive_damage("qi", 5);
		if(me->query("eff_qi")>5)
			me->receive_wound("qi", 5);
		return 0;
	}

	if (duration >= 2)
	{
		inv = all_inventory(me);
		for(i=0;i<sizeof(inv);i++)
		{
			if(!inv[i]->is_cutable()&&me->query("food")<=0&&inv[i]->query("food_remaining"))
			{
				"/cmds/std/eat"->main(me,inv[i]->query("id"));
				break;
			}
			if(me->query("water")<=0&&inv[i]->query("liquid/remaining")>0)
			{
				"/cmds/std/drink"->main(me,inv[i]->query("id"));
				break;
			}
		}
	}

	me->apply_condition("hunger", duration + 1);
	return CND_CONTINUE;
}
