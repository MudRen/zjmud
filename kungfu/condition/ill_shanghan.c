// ill_shanghan.c

#include <ansi.h>
#include <condition.h>

inherit ILLNESS;

string name() { return "ill_shanghan"; }

int min_qi_needed() { return 20; }

int update_condition(object me, int duration)
{
	if( duration < 1 ) return 0;

	message("vision", HIG + me->name() + "�䲻�����˸���ս��ͷ"
			  "������ģ������ǵ��˺����ˡ�"NOR"\n",
		environment(me), me);

	if( !living(me) && me->query("qi") < 3 ) {
		me->set_temp("die_reason", "�˺�����������������");
		me->die();
		return 0;
	}
	else
		tell_object(me, HIB "����˸���ս��ͷ������ģ������ǵ��˺����ˣ�"NOR"\n" );

	if(me->query("qi")>3)
		me->receive_damage("qi", 3);
	if(me->query("eff_qi")>3)
		me->receive_wound("qi", 3);
	me->apply_condition(name(), duration - 1);

	if( duration < 1 ) return 0;
	return CND_CONTINUE;
}
