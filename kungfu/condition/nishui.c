#include <ansi.h>

int update_condition(object me, int duration)
{
	int dam;
	if (me->query("neili") >= 4000) dam = random(50);
	else if (me->query("neili") > 3000) dam = random(200);
	else if (me->query("neili") > 2000) dam = random(500);
	else if (me->query("neili") > 1000) dam = random(1500);
	else if (me->query("neili") > 500) dam = random(2000);
	else dam = random(3000);

	me->receive_wound("qi", dam);
	me->receive_wound("jing", dam);
	me->apply_condition("nishui", duration-1);
	
	if( duration < 1 )
	tell_object(me, HIW "��Ĩȥ�������ϵ���ͣ�ֻ�е������Ƕ�ô�����£�"NOR"\n" );
	else
	tell_object(me, HIW "��е�һ�����ƣ�"NOR"\n" );
	if( duration < 1 ) 
		return 0;
	return 1;
}

