// ill_zhongshu.c

#include <ansi.h>
#include <condition.h>

inherit ILLNESS;

string name() { return "ill_zhongshu"; }

int min_qi_needed() { return 15; }

int update_condition(object me, int duration)
{
	if( duration < 1 ) return 0;

	message("vision", HIG + me->name() + "ͷ�ؽ��ᣬ���κ���̧��"
			  "��ͷ���������������ˡ�"NOR"\n",
		environment(me), me);

	if( !living(me) && me->query("qi") < 2 ) {
		me->set_temp("die_reason", "����̫�����������");
		me->die();
		return 0;
	}
	else
	tell_object(me, HIB "���������֮��һ���ڣ�ͷ�ؽ��ᣬ���ŷ��ȣ������������ˡ�"NOR"\n" );

	if(me->query("qi")>2)
		me->receive_damage("qi", 2);
	if(me->query("eff_qi")>2)
		me->receive_wound("qi", 2);
	me->apply_condition(name(), duration - 1);

	if( duration < 1 ) return 0;
	return CND_CONTINUE;
}
