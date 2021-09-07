#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{

	if(environment(me)&&environment(me)->query("owner_special")&&environment(me)->query("sleep_room"))
	        return CND_CONTINUE;
        me->apply_condition("db_exp", duration - 1);
        
        if(random(30)==1)
	{
		tell_room(environment(me), me->name() + "��������ɷ��ﾫ����档\n", ({ me }));
		tell_object(me, HIG"�����鵤�������£���о����κ��¶����°빦����"NOR"\n");
	}

        if( duration < 1 ) 
        {
        	tell_object(me, HIR"����þ�����Щƣ�����ɳ��ٶ�������������"NOR"\n");
        	return 0;
        }
        return CND_CONTINUE;
}

string query_type(object me)
{
	return "db_exp";
}
