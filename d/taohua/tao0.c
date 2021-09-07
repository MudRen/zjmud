#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{ 
	set("short", "�һ�����");
	set("long",@LONG
����һƬ�һ��ĺ�������һ���޼ʣ�ȫ��ʢ�����һ���΢�������
��Ӣ�ͷס���Χ�����ĵġ�Զ��ż������һ����С������в�������
��������������ȥ�ĺá�
LONG );
	set("outdoors", "taohua");
	set("exits", ([
		"east" :  __FILE__,
		"west" :  __FILE__,
		"south" : __FILE__,
		"north" : __FILE__,
	]));	     
}

int valid_leave(object me, string dir)
{
	int total_steps;

	if (me->query("family/family_name") == "�һ���" ||
	    me->query_skill("qimen-wuxing") >= 150)
	{
		total_steps = 1; 
	} else
	{
    		me->receive_damage("qi", 15);
    		me->receive_wound("qi", 15);
    		message_vision(HIR"ͻȻһ���һ��������㼲"
				  "��$N��"NOR"\n", me);

		total_steps = 30;
	}

	if (dir == "north")
	    	me->add_temp("taohua/steps",1);

	if (dir == "south")
	    	me->add_temp("taohua/steps",-1);

	if (me->query_temp("taohua/steps") == total_steps)
	{
     	    	me->move(__DIR__"tao_in");
	    	me->delete_temp("taohua/steps");
	    	write("�����˰��죬�����߳����һ�����\n");
	   	return -1;
	}  

	if (me->query_temp("taohua/steps") == - total_steps)
	{  
		me->move(__DIR__"tao_out");
	    	me->delete_temp("taohua/steps");
	    	write("�����˰��죬�����߳����һ�����\n");
		return -1;
     	}

	return ::valid_leave(me,dir);
}

